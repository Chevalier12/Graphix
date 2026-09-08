/*
  Graphix regressions for GPU-renderer streaming storage, failure cleanup and
  exposed YUV plane identities. Zlib license; see LICENSE.txt.

  Uses public SDL APIs and an offscreen renderer. Missing GPU prerequisites
  are a setup failure, not a passing or skipped test. Examples:
      testgpurender_texture_contracts --driver direct3d12 --case streaming
      testgpurender_texture_contracts --driver vulkan --case properties

  The allocator observes requested sizes and quarantines frees during the
  creation under test. This reports insufficient storage and repeated frees
  deterministically without executing an invalid memory access. It is installed
  before SDL_Init and never replaced while SDL resources are alive.
*/

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_test.h>

#include <stdlib.h>

typedef struct Allocation
{
    void *ptr;
    size_t size;
    int frees;
} Allocation;

static SDL_malloc_func original_malloc;
static SDL_calloc_func original_calloc;
static SDL_realloc_func original_realloc;
static SDL_free_func original_free;
static SDL_ThreadID main_thread;
static Allocation allocations[256];
static int allocation_count, failure_hits;
static size_t failure_size;
static bool tracking, tracking_overflow;

static bool OnTrackedThread(void)
{
    /* Other threads do not read the main-thread-only tracking state. */
    return SDL_GetCurrentThreadID() == main_thread;
}

static Allocation *FindAllocation(void *ptr)
{
    int i;
    if (!ptr) {
        return NULL;
    }
    for (i = 0; i < allocation_count; ++i) {
        if (allocations[i].ptr == ptr) {
            return &allocations[i];
        }
    }
    return NULL;
}

static bool FailAllocation(size_t size)
{
    if (OnTrackedThread() && tracking && failure_size && size == failure_size && !failure_hits) {
        ++failure_hits;
        return true;
    }
    return false;
}

static void RecordAllocation(void *ptr, size_t size)
{
    if (OnTrackedThread() && tracking && ptr) {
        if (allocation_count == SDL_arraysize(allocations)) {
            tracking_overflow = true;
        } else {
            Allocation *record = &allocations[allocation_count++];
            record->ptr = ptr;
            record->size = size;
            record->frees = 0;
        }
    }
}

static void *SDLCALL TrackedMalloc(size_t size)
{
    void *ptr;
    if (FailAllocation(size)) {
        return NULL;
    }
    ptr = original_malloc(size);
    RecordAllocation(ptr, size);
    return ptr;
}

static void *SDLCALL TrackedCalloc(size_t count, size_t size)
{
    void *ptr;
    if (size && count > SDL_SIZE_MAX / size) {
        return NULL;
    }
    if (FailAllocation(count * size)) {
        return NULL;
    }
    ptr = original_calloc(count, size);
    RecordAllocation(ptr, count * size);
    return ptr;
}

static void *SDLCALL TrackedRealloc(void *ptr, size_t size)
{
    Allocation *record = OnTrackedThread() && tracking ? FindAllocation(ptr) : NULL;
    void *resized;
    if (FailAllocation(size)) {
        return NULL;
    }
    resized = original_realloc(ptr, size);
    if (record) {
        if (resized || !size) {
            record->ptr = resized;
            record->size = size;
        }
    } else {
        RecordAllocation(resized, size);
    }
    return resized;
}

static void SDLCALL TrackedFree(void *ptr)
{
    Allocation *record = ptr && OnTrackedThread() && tracking ? FindAllocation(ptr) : NULL;
    if (record) {
        ++record->frees;
        /* Defer reclamation, preserving bytes so a repeated cleanup is safe to observe. */
    } else {
        original_free(ptr);
    }
}

static void Require(bool success, const char *operation)
{
    if (!success) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Test setup/operation failed: %s: %s", operation, SDL_GetError());
        exit(2);
    }
}

static void BeginTracking(size_t fail_size)
{
    SDL_zero(allocations);
    allocation_count = failure_hits = 0;
    failure_size = fail_size;
    tracking_overflow = false;
    tracking = true;
}

static int EndTracking(void)
{
    int i, repeated_frees = 0;
    tracking = false;
    for (i = 0; i < allocation_count; ++i) {
        Allocation *record = &allocations[i];
        if (record->frees > 0) {
            repeated_frees += record->frees - 1;
            original_free(record->ptr);
        }
    }
    Require(!tracking_overflow, "allocation observer capacity");
    return repeated_frees;
}

static SDL_PropertiesID TextureProperties(SDL_PixelFormat format, SDL_TextureAccess access, int w, int h)
{
    SDL_PropertiesID props = SDL_CreateProperties();
    Require(props != 0, "SDL_CreateProperties");
    Require(SDL_SetNumberProperty(props, SDL_PROP_TEXTURE_CREATE_FORMAT_NUMBER, format), "texture format");
    Require(SDL_SetNumberProperty(props, SDL_PROP_TEXTURE_CREATE_ACCESS_NUMBER, access), "texture access");
    Require(SDL_SetNumberProperty(props, SDL_PROP_TEXTURE_CREATE_WIDTH_NUMBER, w), "texture width");
    Require(SDL_SetNumberProperty(props, SDL_PROP_TEXTURE_CREATE_HEIGHT_NUMBER, h), "texture height");
    if (format == SDL_PIXELFORMAT_P010) {
        Require(SDL_SetNumberProperty(props, SDL_PROP_TEXTURE_CREATE_COLORSPACE_NUMBER, SDL_COLORSPACE_BT2020_FULL), "P010 colorspace");
    }
    return props;
}

static bool CheckPlane(SDL_GPUDevice *device, SDL_GPUTexture *plane, int w, int h, int bpp, const Uint8 *expected, int pitch)
{
    SDL_GPUTransferBufferCreateInfo info = {0};
    SDL_GPUTextureRegion source = {0};
    SDL_GPUTextureTransferInfo destination = {0};
    SDL_GPUTransferBuffer *download;
    SDL_GPUCommandBuffer *command;
    SDL_GPUCopyPass *pass;
    const Uint8 *actual;
    int y, row_size = w * bpp;
    bool matches = true;

    Require(plane != NULL, "exposed GPU plane");
    info.usage = SDL_GPU_TRANSFERBUFFERUSAGE_DOWNLOAD;
    info.size = (Uint32)(row_size * h);
    download = SDL_CreateGPUTransferBuffer(device, &info);
    Require(download != NULL, "download buffer");
    command = SDL_AcquireGPUCommandBuffer(device);
    Require(command != NULL, "readback command");
    pass = SDL_BeginGPUCopyPass(command);
    Require(pass != NULL, "readback copy pass");
    source.texture = plane;
    source.w = (Uint32)w;
    source.h = (Uint32)h;
    source.d = 1;
    destination.transfer_buffer = download;
    destination.pixels_per_row = (Uint32)w;
    destination.rows_per_layer = (Uint32)h;
    SDL_DownloadFromGPUTexture(pass, &source, &destination);
    SDL_EndGPUCopyPass(pass);
    Require(SDL_SubmitGPUCommandBuffer(command), "submit readback");
    Require(SDL_WaitForGPUIdle(device), "wait for readback");
    actual = SDL_MapGPUTransferBuffer(device, download, false);
    Require(actual != NULL, "map readback");
    for (y = 0; y < h; ++y) {
        matches = SDL_memcmp(actual + y * row_size, expected + y * pitch, (size_t)row_size) == 0 && matches;
    }
    SDL_UnmapGPUTransferBuffer(device, download);
    SDL_ReleaseGPUTransferBuffer(device, download);
    return matches;
}

static void StreamingCase(SDL_Renderer *renderer, SDL_GPUDevice *device, SDL_PixelFormat format, int w, int h)
{
    const bool p010 = format == SDL_PIXELFORMAT_P010;
    const bool rgba = format == SDL_PIXELFORMAT_RGBA32;
    SDL_PropertiesID props = TextureProperties(format, SDL_TEXTUREACCESS_STREAMING, w, h);
    SDL_Texture *texture;
    Allocation *record;
    SDL_GPUTexture *plane;
    Uint8 *pixels, *expected;
    size_t allocated, required, i;
    int pitch, chroma_pitch, repeated_frees;
    bool matches;

    BeginTracking(0);
    texture = SDL_CreateTextureWithProperties(renderer, props);
    Require(texture != NULL, "streaming texture");
    Require(SDL_LockTexture(texture, NULL, (void **)&pixels, &pitch), "lock streaming texture");
    record = FindAllocation(pixels);
    Require(record != NULL, "observe locked pixel allocation");
    allocated = record->size;
    repeated_frees = EndTracking();
    Require(repeated_frees == 0, "streaming control cleanup");
    chroma_pitch = p010 ? ((pitch + 3) & ~3) : ((pitch + 1) & ~1);
    required = (size_t)pitch * h + (rgba ? 0 : (size_t)chroma_pitch * ((h + 1) / 2));
    SDLTest_AssertCheck(allocated >= required,
                        "%s %dx%d pitch=%d: pixel allocation %zu covers %zu bytes",
                        SDL_GetPixelFormatName(format), w, h, pitch, allocated, required);
    if (allocated < required) {
        /* Do not perform an out-of-bounds write or upload just to make RED crash. */
        SDL_DestroyTexture(texture);
        SDL_DestroyProperties(props);
        return;
    }
    expected = SDL_malloc(required);
    Require(expected != NULL, "expected pixels");
    if (p010) {
        for (i = 0; i < required / sizeof(Uint16); ++i) {
            ((Uint16 *)expected)[i] = (Uint16)(((i * 37 + 64) & 1023) << 6);
        }
    } else {
        for (i = 0; i < required; ++i) {
            expected[i] = (Uint8)(i * 17 + 31);
        }
    }
    SDL_memcpy(pixels, expected, required);
    SDL_UnlockTexture(texture);
    Require(SDL_RenderPresent(renderer), "submit texture upload");
    SDL_DestroyProperties(props);
    props = SDL_GetTextureProperties(texture);
    plane = SDL_GetPointerProperty(props, SDL_PROP_TEXTURE_GPU_TEXTURE_POINTER, NULL);
    matches = CheckPlane(device, plane, w, h, rgba ? 4 : (p010 ? 2 : 1), expected, pitch);
    if (!rgba) {
        plane = SDL_GetPointerProperty(props, SDL_PROP_TEXTURE_GPU_TEXTURE_UV_POINTER, NULL);
        matches = CheckPlane(device, plane, (w + 1) / 2, (h + 1) / 2, p010 ? 4 : 2,
                             expected + pitch * h, chroma_pitch) && matches;
    }
    SDLTest_AssertCheck(matches, "%s %dx%d: every uploaded plane byte matches GPU readback", SDL_GetPixelFormatName(format), w, h);
    SDL_free(expected);
    SDL_DestroyTexture(texture);
}

static void AllocationFailureCase(SDL_Renderer *renderer)
{
    const size_t pixel_size = 113 * 71 * 4;
    SDL_PropertiesID props = TextureProperties(SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, 113, 71);
    SDL_Texture *texture;
    Allocation *record;
    void *pixels;
    int pitch, repeated_frees;

    /* Establish that this allocation size belongs to the public locked pixels. */
    BeginTracking(0);
    texture = SDL_CreateTextureWithProperties(renderer, props);
    Require(texture != NULL, "allocation-failure control creation");
    Require(SDL_LockTexture(texture, NULL, &pixels, &pitch), "allocation-failure control lock");
    record = FindAllocation(pixels);
    Require(record && record->size == pixel_size && pitch == 113 * 4, "failure injection pixel allocation");
    repeated_frees = EndTracking();
    Require(repeated_frees == 0, "allocation-failure control cleanup");
    SDL_memset(pixels, 0, pixel_size);
    SDL_UnlockTexture(texture);
    Require(SDL_RenderPresent(renderer), "submit control upload");
    SDL_DestroyTexture(texture);

    BeginTracking(pixel_size);
    texture = SDL_CreateTextureWithProperties(renderer, props);
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    repeated_frees = EndTracking();
    Require(failure_hits == 1, "pixel allocation failure was injected exactly once");
    SDLTest_AssertCheck(texture == NULL, "pixel allocation failure returns NULL");
    SDLTest_AssertCheck(repeated_frees == 0, "failed creation does not free an allocation twice: %d repeated frees", repeated_frees);
    SDL_DestroyProperties(props);
}

static void PlanePropertyCase(SDL_Renderer *renderer, SDL_GPUDevice *device, SDL_PixelFormat format, bool external)
{
    SDL_GPUTextureCreateInfo info = {0};
    SDL_GPUTexture *planes[3] = {NULL, NULL, NULL};
    SDL_PropertiesID props = TextureProperties(format, SDL_TEXTUREACCESS_STATIC, 4, 4);
    SDL_PropertiesID exposed;
    SDL_Texture *texture;
    const char *inputs[] = {SDL_PROP_TEXTURE_CREATE_GPU_TEXTURE_POINTER, SDL_PROP_TEXTURE_CREATE_GPU_TEXTURE_U_POINTER, SDL_PROP_TEXTURE_CREATE_GPU_TEXTURE_V_POINTER};
    const char *outputs[] = {SDL_PROP_TEXTURE_GPU_TEXTURE_POINTER, SDL_PROP_TEXTURE_GPU_TEXTURE_U_POINTER, SDL_PROP_TEXTURE_GPU_TEXTURE_V_POINTER};
    void *actual[3];
    bool matches;
    int i;

    if (external) {
        info.type = SDL_GPU_TEXTURETYPE_2D;
        info.format = SDL_GPU_TEXTUREFORMAT_R8_UNORM;
        info.usage = SDL_GPU_TEXTUREUSAGE_SAMPLER;
        info.layer_count_or_depth = info.num_levels = 1;
        for (i = 0; i < 3; ++i) {
            info.width = info.height = i == 0 ? 4 : 2;
            planes[i] = SDL_CreateGPUTexture(device, &info);
            Require(planes[i] != NULL, "external YUV plane");
            Require(SDL_SetPointerProperty(props, inputs[i], planes[i]), "external plane property");
        }
    }
    texture = SDL_CreateTextureWithProperties(renderer, props);
    Require(texture != NULL, "YUV texture creation");
    exposed = SDL_GetTextureProperties(texture);
    for (i = 0; i < 3; ++i) {
        actual[i] = SDL_GetPointerProperty(exposed, outputs[i], NULL);
    }
    matches = actual[0] && actual[1] && actual[2] && actual[0] != actual[1] && actual[0] != actual[2] && actual[1] != actual[2];
    if (external) {
        for (i = 0; i < 3; ++i) {
            matches = actual[i] == planes[i] && matches;
        }
    }
    SDLTest_AssertCheck(matches, "%s %s: Y/U/V properties identify their distinct planes (U=%p V=%p)",
                        SDL_GetPixelFormatName(format), external ? "wrapped" : "owned", actual[1], actual[2]);
    SDL_DestroyTexture(texture);
    SDL_DestroyProperties(props);
    for (i = 0; i < 3; ++i) {
        SDL_ReleaseGPUTexture(device, planes[i]);
    }
}

int main(int argc, char **argv)
{
    const SDL_PixelFormat formats[] = {SDL_PIXELFORMAT_P010, SDL_PIXELFORMAT_NV12, SDL_PIXELFORMAT_NV21, SDL_PIXELFORMAT_RGBA32};
    const int sizes[][2] = {{1, 1}, {1, 3}, {3, 1}, {3, 3}, {3, 16}, {4, 16}};
    const char *driver = NULL, *filter = NULL;
    SDL_GPUDevice *device;
    SDL_Renderer *renderer;
    SDL_Texture *target;
    int arg, iteration, iterations = 3, i, j, result;

    main_thread = SDL_GetCurrentThreadID();
    SDL_GetMemoryFunctions(&original_malloc, &original_calloc, &original_realloc, &original_free);
    Require(SDL_SetMemoryFunctions(TrackedMalloc, TrackedCalloc, TrackedRealloc, TrackedFree), "install allocator observer");
    for (arg = 1; arg < argc; ++arg) {
        if (SDL_strcmp(argv[arg], "--driver") == 0 && arg + 1 < argc) {
            driver = argv[++arg];
        } else if (SDL_strcmp(argv[arg], "--case") == 0 && arg + 1 < argc) {
            filter = argv[++arg];
        } else if (SDL_strcmp(argv[arg], "--iterations") == 0 && arg + 1 < argc) {
            iterations = SDL_atoi(argv[++arg]);
        } else {
            SDL_Log("Usage: %s [--driver NAME] [--case streaming|allocation-failure|properties] [--iterations 1..100]", argv[0]);
            return 2;
        }
    }
    if (iterations < 1 || iterations > 100 ||
        (filter && SDL_strcmp(filter, "streaming") && SDL_strcmp(filter, "allocation-failure") && SDL_strcmp(filter, "properties"))) {
        return 2;
    }
    Require(SDL_Init(SDL_INIT_VIDEO), "SDL_Init");
    device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_MSL, false, driver);
    Require(device != NULL, "SDL_CreateGPUDevice");
    renderer = SDL_CreateGPURenderer(device, NULL);
    Require(renderer != NULL, "offscreen GPU renderer");
    target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 1, 1);
    Require(target != NULL && SDL_SetRenderTarget(renderer, target), "offscreen render target");
    SDL_Log("Revision: %s; GPU driver: %s", SDL_GetRevision(), SDL_GetGPUDeviceDriver(device));
    for (iteration = 0; iteration < iterations; ++iteration) {
        SDL_Log("Iteration %d/%d", iteration + 1, iterations);
        if (!filter || SDL_strcmp(filter, "streaming") == 0) {
            for (i = 0; i < SDL_arraysize(formats); ++i) {
                for (j = 0; j < SDL_arraysize(sizes); ++j) {
                    StreamingCase(renderer, device, formats[i], sizes[j][0], sizes[j][1]);
                }
            }
        }
        if (!filter || SDL_strcmp(filter, "allocation-failure") == 0) {
            AllocationFailureCase(renderer);
        }
        if (!filter || SDL_strcmp(filter, "properties") == 0) {
            PlanePropertyCase(renderer, device, SDL_PIXELFORMAT_IYUV, false);
            PlanePropertyCase(renderer, device, SDL_PIXELFORMAT_IYUV, true);
            PlanePropertyCase(renderer, device, SDL_PIXELFORMAT_YV12, false);
            PlanePropertyCase(renderer, device, SDL_PIXELFORMAT_YV12, true);
        }
    }
    Require(SDL_WaitForGPUIdle(device), "final GPU idle");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyGPUDevice(device);
    SDL_Quit();
    result = SDLTest_AssertSummaryToTestResult();
    return result == TEST_RESULT_PASSED ? 0 : 1;
}
