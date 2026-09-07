/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "SDL_internal.h"

#ifdef SDL_PROCESS_WINDOWS

#include "../../core/windows/SDL_windows.h"
#include "../SDL_sysprocess.h"
#include "../../io/SDL_iostream_c.h"

#define READ_END 0
#define WRITE_END 1

struct SDL_ProcessData {
    PROCESS_INFORMATION process_information;
};

static void CleanupStream(void *userdata, void *value)
{
    SDL_Process *process = (SDL_Process *)value;
    const char *property = (const char *)userdata;

    SDL_ClearProperty(process->props, property);
}

static bool SetupStream(SDL_Process *process, HANDLE handle, const char *mode, const char *property)
{
    SDL_IOStream *io = SDL_IOFromHandle(handle, mode, true);
    if (!io) {
        return false;
    }

    SDL_SetPointerPropertyWithCleanup(SDL_GetIOProperties(io), "SDL.internal.process", process, CleanupStream, (void *)property);
    SDL_SetPointerProperty(process->props, property, io);
    return true;
}

static bool SetupRedirect(SDL_PropertiesID props, const char *property, HANDLE *result)
{
    SDL_IOStream *io = (SDL_IOStream *)SDL_GetPointerProperty(props, property, NULL);
    if (!io) {
        SDL_SetError("%s is not set", property);
        return false;
    }

    HANDLE handle = (HANDLE)SDL_GetPointerProperty(SDL_GetIOProperties(io), SDL_PROP_IOSTREAM_WINDOWS_HANDLE_POINTER, INVALID_HANDLE_VALUE);
    if (handle == INVALID_HANDLE_VALUE) {
        SDL_SetError("%s doesn't have SDL_PROP_IOSTREAM_WINDOWS_HANDLE_POINTER available", property);
        return false;
    }

    if (!DuplicateHandle(GetCurrentProcess(), handle,
                         GetCurrentProcess(), result,
                         0, TRUE, DUPLICATE_SAME_ACCESS)) {
        WIN_SetError("DuplicateHandle()");
        return false;
    }

    if (GetFileType(*result) == FILE_TYPE_PIPE) {
        DWORD wait_mode = PIPE_WAIT;
        if (!SetNamedPipeHandleState(*result, &wait_mode, NULL, NULL)) {
            WIN_SetError("SetNamedPipeHandleState()");
            return false;
        }
    }
    return true;
}

static bool is_batch_file_path(const char *path) {
    size_t len_path = SDL_strlen(path);
    if (len_path < 4) {
        return false;
    }
    if (SDL_strcasecmp(path + len_path - 4, ".bat") == 0 || SDL_strcasecmp(path + len_path - 4, ".cmd") == 0) {
        return true;
    }
    return false;
}

/* Graphix #2 / SDL #16217: argv is data, not an unescaped shell command.
 * CMDLINE_STRING deliberately bypasses this strict argument-list path. */
static bool is_cmd_path(const char *path)
{
    const char *name = path;
    for (; *path; path++) {
        if (*path == '\\' || *path == '/' || *path == ':') {
            name = path + 1;
        }
    }
    return SDL_strcasecmp(name, "cmd") == 0 || SDL_strcasecmp(name, "cmd.exe") == 0;
}

static bool validate_program_path(const char *path)
{
    size_t len = SDL_strlen(path);
    if (!len || SDL_strchr(path, '"')) {
        return SDL_SetError("Windows process arguments: invalid executable path");
    }
    if (path[len - 1] == '.' || SDL_isspace((unsigned char)path[len - 1])) {
        return SDL_SetError("Windows process arguments: executable path ends in whitespace or a dot");
    }
    return true;
}

/* Accept separate, documented cmd switches only. Combined switches or an
 * embedded command string would evade the /c and /k argument boundary. */
static bool is_cmd_option(const char *arg)
{
    static const char *const options[] = {
        "/d", "/s", "/q", "/a", "/u", "/?", "/e:on", "/e:off",
        "/f:on", "/f:off", "/v:on", "/v:off"
    };
    size_t i;
    for (i = 0; i < SDL_arraysize(options); i++) {
        if (SDL_strcasecmp(arg, options[i]) == 0) {
            return true;
        }
    }
    return SDL_strlen(arg) == 5 && SDL_strncasecmp(arg, "/t:", 3) == 0 &&
           SDL_isxdigit((unsigned char)arg[3]) && SDL_isxdigit((unsigned char)arg[4]);
}

/* The caller reserves at least twice the input length plus two quotes.
 * Executable names use Windows' argv[0] rules, not CRT argument escaping. */
static char *quote_argument(char *out, const char *arg, bool shell, bool program)
{
    bool quotes = program || !*arg ||
                  SDL_strpbrk(arg, shell ? " \t\v\f\"<>&|()[]{}^=;'+,\x60~" : " \t\r\n\v\f\"") != NULL;
    if (quotes) {
        *out++ = '"';
    }
    if (program) {
        size_t len = SDL_strlen(arg);
        SDL_memcpy(out, arg, len);
        out += len;
    } else {
        while (*arg) {
            if (*arg == '\\') {
                size_t count = 0;
                while (arg[count] == '\\') {
                    count++;
                }
                arg += count;
                if (*arg == '"' || (!*arg && quotes)) {
                    count *= 2;
                }
                while (count--) {
                    *out++ = '\\';
                }
            } else if (*arg == '"') {
                /* Literal quotes are accepted only for non-shell arguments. */
                SDL_assert(!shell);
                *out++ = '\\';
                *out++ = *arg++;
            } else {
                *out++ = *arg++;
            }
        }
    }
    if (quotes) {
        *out++ = '"';
    }
    return out;
}

static bool join_arguments(const char * const *args, LPWSTR *args_out)
{
    bool batch_file = is_batch_file_path(args[0]);
    bool cmd = is_cmd_path(args[0]);
    bool shell = batch_file || cmd;
    size_t command_switch = 0;
    size_t capacity = sizeof(" /d /s /v:off /c \"\"") + 2;
    size_t i;
    char *shell_path = NULL;
    char *result;
    char *out;

    *args_out = NULL;
    if (!validate_program_path(args[0])) {
        return false;
    }
    for (i = 0; args[i]; i++) {
        size_t extra;
        if (shell && SDL_strpbrk(args[i], "%!\r\n\"")) {
            return SDL_SetError("Windows process arguments: batch/cmd arguments cannot contain %%, !, CR, LF or double quotes (argument %u)", (unsigned)i);
        }
        if (cmd && i > 0 && !command_switch) {
            if (SDL_strcasecmp(args[i], "/c") == 0 || SDL_strcasecmp(args[i], "/k") == 0) {
                command_switch = i;
                if (!args[i + 1] || !validate_program_path(args[i + 1])) {
                    return SDL_SetError("Windows process arguments: /c or /k requires a separate, valid executable path");
                }
            } else if (!is_cmd_option(args[i])) {
                return SDL_SetError("Windows process arguments: unsupported cmd option; use separate switches or an explicit command line");
            }
        }
        if (!SDL_size_mul_check_overflow(SDL_strlen(args[i]), 2, &extra) ||
            !SDL_size_add_check_overflow(extra, 3, &extra) ||
            !SDL_size_add_check_overflow(capacity, extra, &capacity)) {
            return SDL_SetError("Windows process arguments: command line is too large");
        }
    }

    if (batch_file) {
        WCHAR system_path[MAX_PATH];
        UINT length = GetSystemDirectoryW(system_path, SDL_arraysize(system_path));
        if (!length) {
            return WIN_SetError("GetSystemDirectoryW");
        }
        if (length > SDL_arraysize(system_path) - SDL_arraysize(L"\\cmd.exe")) {
            return SDL_SetError("Windows process arguments: system directory is too long");
        }
        SDL_wcslcat(system_path, L"\\cmd.exe", SDL_arraysize(system_path));
        shell_path = WIN_StringToUTF8W(system_path);
        if (!shell_path) {
            return false;
        }
        if (!SDL_size_add_check_overflow(capacity, SDL_strlen(shell_path) + 2, &capacity)) {
            SDL_free(shell_path);
            return SDL_SetError("Windows process arguments: command line is too large");
        }
    }

    result = SDL_malloc(capacity);
    if (!result) {
        SDL_free(shell_path);
        return false;
    }
    out = result;
    if (batch_file) {
        /* Use the system interpreter, not COMSPEC or a PATH/current-directory
         * cmd.exe. Disable AutoRun and delayed expansion for this launch. */
        out = quote_argument(out, shell_path, false, true);
        SDL_free(shell_path);
        SDL_memcpy(out, " /d /s /v:off /c \"", sizeof(" /d /s /v:off /c \"") - 1);
        out += sizeof(" /d /s /v:off /c \"") - 1;
    }
    for (i = 0; args[i]; i++) {
        if (i && !(command_switch && i == command_switch + 1)) {
            *out++ = ' ';
        }
        out = quote_argument(out, args[i], shell, i == 0 || (cmd && i == command_switch + 1 && command_switch));
        if (cmd && i == 0) {
            SDL_memcpy(out, " /d /s", sizeof(" /d /s") - 1);
            out += sizeof(" /d /s") - 1;
        }
        if (command_switch && i == command_switch) {
            *out++ = ' ';
            *out++ = '"';
        }
    }
    if (batch_file || command_switch) {
        *out++ = '"';
    }
    *out++ = '\0';
    SDL_assert((size_t)(out - result) <= capacity);
    *args_out = WIN_UTF8ToStringW(result);
    SDL_free(result);
    return *args_out != NULL;
}

static bool join_env(char **env, LPWSTR *env_out)
{
    size_t len;
    char **var;
    char *result;

    len = 0;
    for (var = env; *var; var++) {
        len += SDL_strlen(*var) + 1;
    }
    result = SDL_malloc(len + 1);
    if (!result) {
        return false;
    }

    len = 0;
    for (var = env; *var; var++) {
        size_t l = SDL_strlen(*var);
        SDL_memcpy(result + len, *var, l);
        result[len + l] = '\0';
        len += l + 1;
    }
    result[len] = '\0';

    *env_out = (LPWSTR)SDL_iconv_string("UTF-16LE", "UTF-8", (const char *)result, len);
    SDL_free(result);
    if (!*env_out) {
        return false;
    }
    return true;
}

bool SDL_SYS_CreateProcessWithProperties(SDL_Process *process, SDL_PropertiesID props)
{
    const char * const *args = SDL_GetPointerProperty(props, SDL_PROP_PROCESS_CREATE_ARGS_POINTER, NULL);
    const char *cmdline = SDL_GetStringProperty(props, SDL_PROP_PROCESS_CREATE_CMDLINE_STRING, NULL);
    SDL_Environment *env = SDL_GetPointerProperty(props, SDL_PROP_PROCESS_CREATE_ENVIRONMENT_POINTER, SDL_GetEnvironment());
    char **envp = NULL;
    const char *working_directory = SDL_GetStringProperty(props, SDL_PROP_PROCESS_CREATE_WORKING_DIRECTORY_STRING, NULL);
    SDL_ProcessIO stdin_option = (SDL_ProcessIO)SDL_GetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDIN_NUMBER, SDL_PROCESS_STDIO_NULL);
    SDL_ProcessIO stdout_option = (SDL_ProcessIO)SDL_GetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDOUT_NUMBER, SDL_PROCESS_STDIO_INHERITED);
    SDL_ProcessIO stderr_option = (SDL_ProcessIO)SDL_GetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDERR_NUMBER, SDL_PROCESS_STDIO_INHERITED);
    bool redirect_stderr = SDL_GetBooleanProperty(props, SDL_PROP_PROCESS_CREATE_STDERR_TO_STDOUT_BOOLEAN, false) &&
                           !SDL_HasProperty(props, SDL_PROP_PROCESS_CREATE_STDERR_NUMBER);
    LPWSTR createprocess_cmdline = NULL;
    LPWSTR createprocess_env = NULL;
    LPWSTR createprocess_cwd = NULL;
    STARTUPINFOW startup_info;
    DWORD creation_flags;
    SECURITY_ATTRIBUTES security_attributes;
    HANDLE stdin_pipe[2] = { INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE };
    HANDLE stdout_pipe[2] = { INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE };
    HANDLE stderr_pipe[2] = { INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE };
    HANDLE handle;
    DWORD pipe_mode = PIPE_NOWAIT;
    bool result = false;

    // Keep the malloc() before exec() so that an OOM won't run a process at all
    envp = SDL_GetEnvironmentVariables(env);
    if (!envp) {
        return false;
    }

    SDL_ProcessData *data = SDL_calloc(1, sizeof(*data));
    if (!data) {
        SDL_free(envp);
        return false;
    }
    process->internal = data;
    data->process_information.hProcess = INVALID_HANDLE_VALUE;
    data->process_information.hThread = INVALID_HANDLE_VALUE;

    creation_flags = CREATE_UNICODE_ENVIRONMENT;

    SDL_zero(startup_info);
    startup_info.cb = sizeof(startup_info);
    startup_info.dwFlags |= STARTF_USESTDHANDLES;
    startup_info.hStdInput = INVALID_HANDLE_VALUE;
    startup_info.hStdOutput = INVALID_HANDLE_VALUE;
    startup_info.hStdError = INVALID_HANDLE_VALUE;

    SDL_zero(security_attributes);
    security_attributes.nLength = sizeof(SECURITY_ATTRIBUTES);
    security_attributes.bInheritHandle = TRUE;
    security_attributes.lpSecurityDescriptor = NULL;

    if (cmdline) {
        createprocess_cmdline = WIN_UTF8ToString(cmdline);
        if (!createprocess_cmdline) {
            goto done;
        }
    } else if (!join_arguments(args, &createprocess_cmdline)) {
        goto done;
    }

    if (!join_env(envp, &createprocess_env)) {
        goto done;
    }

    if (working_directory) {
        createprocess_cwd = WIN_UTF8ToStringW(working_directory);
        if (!createprocess_cwd) {
            goto done;
        }
    }

    // Background processes don't have access to the terminal
    // This isn't necessary on Windows, but we keep the same behavior as the POSIX implementation.
    if (process->background) {
        if (stdin_option == SDL_PROCESS_STDIO_INHERITED) {
            stdin_option = SDL_PROCESS_STDIO_NULL;
        }
        if (stdout_option == SDL_PROCESS_STDIO_INHERITED) {
            stdout_option = SDL_PROCESS_STDIO_NULL;
        }
        if (stderr_option == SDL_PROCESS_STDIO_INHERITED) {
            stderr_option = SDL_PROCESS_STDIO_NULL;
        }
        creation_flags |= CREATE_NO_WINDOW;
    }

    switch (stdin_option) {
    case SDL_PROCESS_STDIO_REDIRECT:
        if (!SetupRedirect(props, SDL_PROP_PROCESS_CREATE_STDIN_POINTER, &startup_info.hStdInput)) {
            goto done;
        }
        break;
    case SDL_PROCESS_STDIO_APP:
        if (!CreatePipe(&stdin_pipe[READ_END], &stdin_pipe[WRITE_END], &security_attributes, 0)) {
            stdin_pipe[READ_END] = INVALID_HANDLE_VALUE;
            stdin_pipe[WRITE_END] = INVALID_HANDLE_VALUE;
            goto done;
        }
        if (!SetNamedPipeHandleState(stdin_pipe[WRITE_END], &pipe_mode, NULL, NULL)) {
            WIN_SetError("SetNamedPipeHandleState()");
            goto done;
        }
        if (!SetHandleInformation(stdin_pipe[WRITE_END], HANDLE_FLAG_INHERIT, 0) ) {
            WIN_SetError("SetHandleInformation()");
            goto done;
        }
        startup_info.hStdInput = stdin_pipe[READ_END];
        break;
    case SDL_PROCESS_STDIO_NULL:
        startup_info.hStdInput = CreateFile(TEXT("\\\\.\\NUL"), (GENERIC_READ | GENERIC_WRITE), 0, &security_attributes, OPEN_EXISTING, 0, NULL);
        break;
    case SDL_PROCESS_STDIO_INHERITED:
    default:
        handle = GetStdHandle(STD_INPUT_HANDLE);
        if (!handle) {
            startup_info.hStdInput = NULL;
        } else if (!DuplicateHandle(GetCurrentProcess(), handle,
                             GetCurrentProcess(), &startup_info.hStdInput,
                             0, TRUE, DUPLICATE_SAME_ACCESS)) {
            startup_info.hStdInput = INVALID_HANDLE_VALUE;
            WIN_SetError("DuplicateHandle()");
            goto done;
        }
        break;
    }

    switch (stdout_option) {
    case SDL_PROCESS_STDIO_REDIRECT:
        if (!SetupRedirect(props, SDL_PROP_PROCESS_CREATE_STDOUT_POINTER, &startup_info.hStdOutput)) {
            goto done;
        }
        break;
    case SDL_PROCESS_STDIO_APP:
        if (!CreatePipe(&stdout_pipe[READ_END], &stdout_pipe[WRITE_END], &security_attributes, 0)) {
            stdout_pipe[READ_END] = INVALID_HANDLE_VALUE;
            stdout_pipe[WRITE_END] = INVALID_HANDLE_VALUE;
            goto done;
        }
        if (!SetNamedPipeHandleState(stdout_pipe[READ_END], &pipe_mode, NULL, NULL)) {
            WIN_SetError("SetNamedPipeHandleState()");
            goto done;
        }
        if (!SetHandleInformation(stdout_pipe[READ_END], HANDLE_FLAG_INHERIT, 0) ) {
            WIN_SetError("SetHandleInformation()");
            goto done;
        }
        startup_info.hStdOutput = stdout_pipe[WRITE_END];
        break;
    case SDL_PROCESS_STDIO_NULL:
        startup_info.hStdOutput = CreateFile(TEXT("\\\\.\\NUL"), (GENERIC_READ | GENERIC_WRITE), 0, &security_attributes, OPEN_EXISTING, 0, NULL);
        break;
    case SDL_PROCESS_STDIO_INHERITED:
    default:
        handle = GetStdHandle(STD_OUTPUT_HANDLE);
        if (!handle) {
            startup_info.hStdOutput = NULL;
        } else if (!DuplicateHandle(GetCurrentProcess(), handle,
                             GetCurrentProcess(), &startup_info.hStdOutput,
                             0, TRUE, DUPLICATE_SAME_ACCESS)) {
            startup_info.hStdOutput = INVALID_HANDLE_VALUE;
            WIN_SetError("DuplicateHandle()");
            goto done;
        }
        break;
    }

    if (redirect_stderr) {
        handle = startup_info.hStdOutput;
        if (!handle) {
            startup_info.hStdError = NULL;
        } else if (!DuplicateHandle(GetCurrentProcess(), handle,
                             GetCurrentProcess(), &startup_info.hStdError,
                             0, TRUE, DUPLICATE_SAME_ACCESS)) {
            startup_info.hStdError = INVALID_HANDLE_VALUE;
            WIN_SetError("DuplicateHandle()");
            goto done;
        }
    } else {
        switch (stderr_option) {
        case SDL_PROCESS_STDIO_REDIRECT:
            if (!SetupRedirect(props, SDL_PROP_PROCESS_CREATE_STDERR_POINTER, &startup_info.hStdError)) {
                goto done;
            }
            break;
        case SDL_PROCESS_STDIO_APP:
            if (!CreatePipe(&stderr_pipe[READ_END], &stderr_pipe[WRITE_END], &security_attributes, 0)) {
                stderr_pipe[READ_END] = INVALID_HANDLE_VALUE;
                stderr_pipe[WRITE_END] = INVALID_HANDLE_VALUE;
                goto done;
            }
            if (!SetNamedPipeHandleState(stderr_pipe[READ_END], &pipe_mode, NULL, NULL)) {
                WIN_SetError("SetNamedPipeHandleState()");
                goto done;
            }
            if (!SetHandleInformation(stderr_pipe[READ_END], HANDLE_FLAG_INHERIT, 0) ) {
                WIN_SetError("SetHandleInformation()");
                goto done;
            }
            startup_info.hStdError = stderr_pipe[WRITE_END];
            break;
        case SDL_PROCESS_STDIO_NULL:
            startup_info.hStdError = CreateFile(TEXT("\\\\.\\NUL"), (GENERIC_READ | GENERIC_WRITE), 0, &security_attributes, OPEN_EXISTING, 0, NULL);
            break;
        case SDL_PROCESS_STDIO_INHERITED:
        default:
            handle = GetStdHandle(STD_ERROR_HANDLE);
            if (!handle) {
                startup_info.hStdError = NULL;
            } else if (!DuplicateHandle(GetCurrentProcess(), handle,
                                 GetCurrentProcess(), &startup_info.hStdError,
                                 0, TRUE, DUPLICATE_SAME_ACCESS)) {
                startup_info.hStdError = INVALID_HANDLE_VALUE;
                WIN_SetError("DuplicateHandle()");
                goto done;
            }
            break;
        }
    }

    if (!CreateProcessW(NULL, createprocess_cmdline, NULL, NULL, TRUE, creation_flags, createprocess_env, createprocess_cwd, &startup_info, &data->process_information)) {
        WIN_SetError("CreateProcess");
        goto done;
    }

    SDL_SetNumberProperty(process->props, SDL_PROP_PROCESS_PID_NUMBER, data->process_information.dwProcessId);

    if (stdin_option == SDL_PROCESS_STDIO_APP) {
        if (!SetupStream(process, stdin_pipe[WRITE_END], "wb", SDL_PROP_PROCESS_STDIN_POINTER)) {
            CloseHandle(stdin_pipe[WRITE_END]);
            stdin_pipe[WRITE_END] = INVALID_HANDLE_VALUE;
        }
    }
    if (stdout_option == SDL_PROCESS_STDIO_APP) {
        if (!SetupStream(process, stdout_pipe[READ_END], "rb", SDL_PROP_PROCESS_STDOUT_POINTER)) {
            CloseHandle(stdout_pipe[READ_END]);
            stdout_pipe[READ_END] = INVALID_HANDLE_VALUE;
        }
    }
    if (stderr_option == SDL_PROCESS_STDIO_APP) {
        if (!SetupStream(process, stderr_pipe[READ_END], "rb", SDL_PROP_PROCESS_STDERR_POINTER)) {
            CloseHandle(stderr_pipe[READ_END]);
            stderr_pipe[READ_END] = INVALID_HANDLE_VALUE;
        }
    }

    result = true;

done:
    if (startup_info.hStdInput != INVALID_HANDLE_VALUE &&
        startup_info.hStdInput != stdin_pipe[READ_END]) {
        CloseHandle(startup_info.hStdInput);
    }
    if (startup_info.hStdOutput != INVALID_HANDLE_VALUE &&
        startup_info.hStdOutput != stdout_pipe[WRITE_END]) {
        CloseHandle(startup_info.hStdOutput);
    }
    if (startup_info.hStdError != INVALID_HANDLE_VALUE &&
        startup_info.hStdError != stderr_pipe[WRITE_END]) {
        CloseHandle(startup_info.hStdError);
    }
    if (stdin_pipe[READ_END] != INVALID_HANDLE_VALUE) {
        CloseHandle(stdin_pipe[READ_END]);
    }
    if (stdout_pipe[WRITE_END] != INVALID_HANDLE_VALUE) {
        CloseHandle(stdout_pipe[WRITE_END]);
    }
    if (stderr_pipe[WRITE_END] != INVALID_HANDLE_VALUE) {
        CloseHandle(stderr_pipe[WRITE_END]);
    }
    SDL_free(createprocess_cmdline);
    SDL_free(createprocess_env);
    SDL_free(createprocess_cwd);
    SDL_free(envp);

    if (!result) {
        if (stdin_pipe[WRITE_END] != INVALID_HANDLE_VALUE) {
            CloseHandle(stdin_pipe[WRITE_END]);
        }
        if (stdout_pipe[READ_END] != INVALID_HANDLE_VALUE) {
            CloseHandle(stdout_pipe[READ_END]);
        }
        if (stderr_pipe[READ_END] != INVALID_HANDLE_VALUE) {
            CloseHandle(stderr_pipe[READ_END]);
        }
    }
    return result;
}

static BOOL CALLBACK terminate_app(HWND hwnd, LPARAM lparam)
{
    DWORD current_proc_id = 0, *term_info = (DWORD *) lparam;
    GetWindowThreadProcessId(hwnd, &current_proc_id);
    if (current_proc_id == term_info[0] && PostMessage(hwnd, WM_CLOSE, 0, 0)) {
        term_info[1]++;
    }
    return TRUE;
}

bool SDL_SYS_KillProcess(SDL_Process *process, bool force)
{
    if (!force) {
        // term_info[0] is the process ID, term_info[1] is number of successful tries
        DWORD term_info[2];
        term_info[0] = process->internal->process_information.dwProcessId;
        term_info[1] = 0;
        EnumWindows(terminate_app, (LPARAM) &term_info);
        if (term_info[1] || PostThreadMessage(process->internal->process_information.dwThreadId, WM_CLOSE, 0, 0)) {
            return true;
        }
        if (GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, term_info[0])) {
            return true;
        }
    }
    if (!TerminateProcess(process->internal->process_information.hProcess, 1)) {
        return WIN_SetError("TerminateProcess failed");
    }
    return true;
}

bool SDL_SYS_WaitProcess(SDL_Process *process, bool block, int *exitcode)
{
    DWORD result;

    result = WaitForSingleObject(process->internal->process_information.hProcess, block ? INFINITE : 0);

    if (result == WAIT_OBJECT_0) {
        DWORD rc;
        if (!GetExitCodeProcess(process->internal->process_information.hProcess, &rc)) {
            return WIN_SetError("GetExitCodeProcess");
        }
        if (exitcode) {
            *exitcode = (int)rc;
        }
        return true;
    } else if (result == WAIT_FAILED) {
        return WIN_SetError("WaitForSingleObject(hProcess) returned WAIT_FAILED");
    } else {
        SDL_ClearError();
        return false;
    }
}

void SDL_SYS_DestroyProcess(SDL_Process *process)
{
    SDL_ProcessData *data = process->internal;
    SDL_IOStream *io;

    io = (SDL_IOStream *)SDL_GetPointerProperty(process->props, SDL_PROP_PROCESS_STDIN_POINTER, NULL);
    if (io) {
        SDL_CloseIO(io);
    }
    io = (SDL_IOStream *)SDL_GetPointerProperty(process->props, SDL_PROP_PROCESS_STDERR_POINTER, NULL);
    if (io) {
        SDL_CloseIO(io);
    }
    io = (SDL_IOStream *)SDL_GetPointerProperty(process->props, SDL_PROP_PROCESS_STDOUT_POINTER, NULL);
    if (io) {
        SDL_CloseIO(io);
    }
    if (data) {
        if (data->process_information.hThread != INVALID_HANDLE_VALUE) {
            CloseHandle(data->process_information.hThread);
        }
        if (data->process_information.hProcess != INVALID_HANDLE_VALUE) {
            CloseHandle(data->process_information.hProcess);
        }
    }
    SDL_free(data);
}

#endif // SDL_PROCESS_WINDOWS
