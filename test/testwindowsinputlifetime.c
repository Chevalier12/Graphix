/* Graphix regression: Windows hotplug must join before generic input teardown.
 * Distributed under the zlib license; see LICENSE.txt.
 *
 * The PE import names are the stable test seam. No private SDL symbol, offset,
 * timing delay or physical device is required. Only this process's SDL imports
 * are replaced. The allocator quarantines the old list so RED can report an
 * invalid free without passing it to the system heap (or reading freed memory).
 */
#define WIN32_LEAN_AND_MEAN
#define SDL_MAIN_HANDLED
#include <windows.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static SDL_malloc_func real_malloc;
static SDL_calloc_func real_calloc;
static SDL_realloc_func real_realloc;
static SDL_free_func real_free;
static HANDLE moved, joining, release_allocator;
static DWORD main_thread;
static LONG worker_thread, raw_thread;
static void *volatile old_list, *volatile new_list;
static bool armed, keyboard, raw, keep_joystick;
static int matching_growths;
static LONG current_frees;
static const Uint32 first_id = 0x47525801;

static DWORD ReadThreadID(LONG *id)
{
    return (DWORD)InterlockedCompareExchange(id, 0, 0);
}

static void Fail(const char *message)
{
    fprintf(stderr, "FAIL: %s\n", message);
    fflush(stderr);
    /* RED cannot resume into already-destroyed SDL state. No invalid heap call. */
    TerminateProcess(GetCurrentProcess(), 1);
    abort();
}

static void Wait(HANDLE event)
{
    if (WaitForSingleObject(event, 10000) != WAIT_OBJECT_0) {
        fprintf(stderr, "watchdog thread=%lu event=%s\n", GetCurrentThreadId(),
                event == moved ? "producer paused" : event == joining ? "join entered" :
                event == release_allocator ? "producer release" : "helper finished");
        Fail("barrier watchdog expired (not a passing interleaving)");
    }
}

static void WINAPI ThreadNameException(DWORD code, DWORD flags, DWORD count, const ULONG_PTR *arguments)
{
    /* SDL_SYS_SetupThread's source-owned legacy debugger naming protocol.
     * Do not rely on optional OS thread descriptions being installed. */
    typedef struct {
        DWORD type;
        const char *name;
        DWORD id;
        DWORD flags;
    } ThreadNameInfo;
    if (code == 0x406D1388 && count == sizeof(ThreadNameInfo) / sizeof(ULONG_PTR)) {
        const ThreadNameInfo *info = (const ThreadNameInfo *)arguments;
        if (strcmp(info->name, "DeviceHotplugThread") == 0) {
            InterlockedExchange(&worker_thread, (LONG)GetCurrentThreadId());
        } else if (strcmp(info->name, "SDLRawInput") == 0) {
            InterlockedExchange(&raw_thread, (LONG)GetCurrentThreadId());
        }
    }
    RaiseException(code, flags, count, arguments);
}

static UINT WINAPI Devices(PRAWINPUTDEVICELIST list, PUINT count, UINT size)
{
    if (GetCurrentThreadId() != ReadThreadID(&worker_thread)) {
        return GetRawInputDeviceList(list, count, size);
    }
    if (size != sizeof(*list)) {
        Fail("unexpected raw device list ABI");
    }
    if (!list) {
        *count = 2;
        return 0;
    }
    if (*count < 2) {
        Fail("raw device list capacity");
    }
    for (UINT i = 0; i < 2; ++i) {
        list[i].hDevice = (HANDLE)(uintptr_t)(first_id + i);
        list[i].dwType = keyboard ? RIM_TYPEKEYBOARD : RIM_TYPEMOUSE;
    }
    *count = 2;
    return 2;
}

static UINT WINAPI DeviceInfo(HANDLE device, UINT command, LPVOID output, PUINT size)
{
    if ((uintptr_t)device != first_id && (uintptr_t)device != first_id + 1) {
        return GetRawInputDeviceInfoA(device, command, output, size);
    }
    if (command == RIDI_DEVICEINFO) {
        RID_DEVICE_INFO *info = (RID_DEVICE_INFO *)output;
        memset(info, 0, sizeof(*info));
        info->cbSize = sizeof(*info);
        info->dwType = keyboard ? RIM_TYPEKEYBOARD : RIM_TYPEMOUSE;
        if (keyboard) {
            info->keyboard.dwNumberOfKeysTotal = 104;
        }
        *size = sizeof(*info);
        return sizeof(*info);
    }
    if (command == RIDI_DEVICENAME) {
        const char name[] = "GRAPHIX_LIFETIME_TEST";
        if (*size < sizeof(name)) {
            Fail("raw device name capacity");
        }
        memcpy(output, name, sizeof(name));
        *size = sizeof(name);
        return sizeof(name) - 1;
    }
    Fail("unexpected device info query");
    return (UINT)-1;
}

static DWORD WINAPI Join(HANDLE handle, DWORD timeout, BOOL alertable)
{
    if (GetCurrentThreadId() == main_thread && old_list &&
        GetThreadId(handle) == ReadThreadID(&worker_thread)) {
        if (timeout != INFINITE) {
            Fail("hotplug join must not time out");
        }
        SetEvent(joining);
    }
    return WaitForSingleObjectEx(handle, timeout, alertable);
}

static DWORD WINAPI RawWait(HANDLE handle, DWORD timeout)
{
    if (raw && GetCurrentThreadId() == main_thread &&
        GetThreadId(handle) == ReadThreadID(&raw_thread)) {
        if (timeout != INFINITE) {
            Fail("raw input shutdown used a timed wait instead of joining");
        }
        SetEvent(joining);
    }
    return WaitForSingleObject(handle, timeout);
}

static DWORD WINAPI RawQueueStatus(UINT flags)
{
    if (raw && GetCurrentThreadId() == ReadThreadID(&raw_thread) && armed) {
        armed = false;
        SetEvent(moved);
        Wait(release_allocator);
    }
    return GetQueueStatus(flags);
}

static void *SDLCALL Reallocate(void *pointer, size_t size)
{
    if (!raw && GetCurrentThreadId() == ReadThreadID(&worker_thread) && armed && pointer &&
        size == 2 * sizeof(Uint32) && *(Uint32 *)pointer == first_id) {
        /* AddDeviceID also grows a two-ID scratch list. The first one is
         * before GetDeviceName, the second is SDL's generic device list.
         * Only the generic list is still live when SDL_Quit frees input. */
        if (++matching_growths == 2) {
            armed = false;
            InterlockedExchangePointer(&old_list, pointer);
            InterlockedExchangePointer(&new_list, real_malloc(size));
            if (!new_list) {
                Fail("moving allocation failed");
            }
            memcpy(new_list, pointer, sizeof(Uint32));
            SetEvent(moved);
            Wait(release_allocator);
            return new_list;
        }
    }
    return real_realloc(pointer, size);
}

static void SDLCALL Free(void *pointer)
{
    void *retired = InterlockedCompareExchangePointer(&old_list, NULL, NULL);
    void *current = InterlockedCompareExchangePointer(&new_list, NULL, NULL);
    if (pointer && pointer == retired) {
        Fail("generic input freed the old list before hotplug joined");
    }
    if (pointer && pointer == current) {
        if (WaitForSingleObject(joining, 0) != WAIT_OBJECT_0) {
            Fail("current list freed without joining hotplug");
        }
        InterlockedIncrement(&current_frees);
        /* Retain it until Quit returns, so a repeated free cannot corrupt the
         * heap or be confused with reuse of the same address. */
        return;
    }
    real_free(pointer);
}

static DWORD WINAPI ReleaseAllocator(void *unused)
{
    (void)unused;
    Wait(joining);
    SetEvent(release_allocator);
    return 0;
}

static void ReplaceImport(HMODULE module, const char *name, uintptr_t replacement)
{
    BYTE *base = (BYTE *)module;
    IMAGE_DOS_HEADER *dos = (IMAGE_DOS_HEADER *)base;
    IMAGE_NT_HEADERS *nt = (IMAGE_NT_HEADERS *)(base + dos->e_lfanew);
    IMAGE_IMPORT_DESCRIPTOR *imports = (IMAGE_IMPORT_DESCRIPTOR *)(base +
        nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
    for (; imports->Name; ++imports) {
        IMAGE_THUNK_DATA *names = (IMAGE_THUNK_DATA *)(base + imports->OriginalFirstThunk);
        IMAGE_THUNK_DATA *addresses = (IMAGE_THUNK_DATA *)(base + imports->FirstThunk);
        if (!imports->OriginalFirstThunk) {
            continue;
        }
        for (; names->u1.AddressOfData; ++names, ++addresses) {
            if (!IMAGE_SNAP_BY_ORDINAL(names->u1.Ordinal)) {
                IMAGE_IMPORT_BY_NAME *entry = (IMAGE_IMPORT_BY_NAME *)(base + names->u1.AddressOfData);
                if (strcmp((const char *)entry->Name, name) == 0) {
                    DWORD protection;
                    if (!VirtualProtect(&addresses->u1.Function, sizeof(uintptr_t), PAGE_READWRITE, &protection)) {
                        Fail("cannot protect import slot");
                    }
                    addresses->u1.Function = replacement;
                    if (!VirtualProtect(&addresses->u1.Function, sizeof(uintptr_t), protection, &protection)) {
                        Fail("cannot restore import protection");
                    }
                    return;
                }
            }
        }
    }
    Fail(name);
}

int main(int argc, char **argv)
{
    HMODULE module = GetModuleHandleA("SDL3.dll");
    setvbuf(stdout, NULL, _IONBF, 0);
    if (argc != 3 || !module) {
        Fail("usage: testwindowsinputlifetime mouse|keyboard|raw quit|video");
    }
    keyboard = strcmp(argv[1], "keyboard") == 0;
    raw = strcmp(argv[1], "raw") == 0;
    keep_joystick = strcmp(argv[2], "video") == 0;
    main_thread = GetCurrentThreadId();
    moved = CreateEvent(NULL, TRUE, FALSE, NULL);
    joining = CreateEvent(NULL, TRUE, FALSE, NULL);
    release_allocator = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!moved || !joining || !release_allocator) {
        Fail("CreateEvent");
    }
    ReplaceImport(module, "GetRawInputDeviceList", (uintptr_t)Devices);
    ReplaceImport(module, "RaiseException", (uintptr_t)ThreadNameException);
    ReplaceImport(module, "GetRawInputDeviceInfoA", (uintptr_t)DeviceInfo);
    ReplaceImport(module, "WaitForSingleObjectEx", (uintptr_t)Join);
    ReplaceImport(module, "WaitForSingleObject", (uintptr_t)RawWait);
    ReplaceImport(module, "GetQueueStatus", (uintptr_t)RawQueueStatus);
    SDL_GetMemoryFunctions(&real_malloc, &real_calloc, &real_realloc, &real_free);
    if (!SDL_SetMemoryFunctions(real_malloc, real_calloc, Reallocate, Free)) {
        Fail("SDL_SetMemoryFunctions");
    }
    SDL_SetMainReady();
    for (int iteration = 0; iteration < 3; ++iteration) {
        HANDLE helper;
        ResetEvent(moved);
        ResetEvent(joining);
        ResetEvent(release_allocator);
        current_frees = 0;
        matching_growths = 0;
        InterlockedExchange(&worker_thread, 0);
        InterlockedExchange(&raw_thread, 0);
        armed = true;
        printf("BEGIN %s %s iteration %d\n", argv[1], argv[2], iteration + 1);
        SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "windows");
        SDL_SetHint(SDL_HINT_WINDOWS_GAMEINPUT, "0");
        SDL_SetHint("SDL_WINDOWS_DETECT_DEVICE_HOTPLUG", raw ? "0" : "1");
        SDL_SetHint(SDL_HINT_WINDOWS_RAW_KEYBOARD, raw ? "1" : "0");
        if (!SDL_Init(SDL_INIT_VIDEO | ((!keep_joystick || iteration == 0) ? SDL_INIT_JOYSTICK : 0))) {
            Fail(SDL_GetError());
        }
        Wait(moved);
        helper = CreateThread(NULL, 0, ReleaseAllocator, NULL, 0, NULL);
        if (!helper) {
            Fail("CreateThread");
        }
        if (keep_joystick) {
            SDL_QuitSubSystem(SDL_INIT_VIDEO);
            if (!(SDL_WasInit(SDL_INIT_JOYSTICK) & SDL_INIT_JOYSTICK)) {
                Fail("video quit destroyed joystick reference");
            }
        } else {
            SDL_Quit();
        }
        Wait(helper);
        CloseHandle(helper);
        if (!raw && current_frees != 1) {
            Fail("teardown did not free the published list exactly once");
        }
        real_free(old_list);
        real_free(new_list);
        InterlockedExchangePointer(&old_list, NULL);
        InterlockedExchangePointer(&new_list, NULL);
        if (keep_joystick && iteration == 2) {
            SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
            SDL_Quit();
        }
        printf("PASS %s %s iteration %d: %s\n", argv[1], argv[2], iteration + 1,
               raw ? "raw input joined" : "joined, published, freed once");
    }
    SDL_SetMemoryFunctions(real_malloc, real_calloc, real_realloc, real_free);
    CloseHandle(moved);
    CloseHandle(joining);
    CloseHandle(release_allocator);
    return 0;
}
