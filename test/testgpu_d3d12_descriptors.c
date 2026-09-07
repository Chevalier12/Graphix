/*
  Graphix regression: descriptor heap capacity through the public SDL GPU API.
  This software is provided under the zlib license; see LICENSE.txt.

  Requires Windows, D3D12 and the Graphics Tools debug layer. The Windows SDK
  shader compiler builds the small test shaders in memory; no shader toolchain
  download or native runtime change is needed. Enable CTest registration with
  -DSDLTEST_D3D12=ON, or run a specific boundary explicitly:
      testgpu_d3d12_descriptors --case graphics-samplers --draws 683
*/

#define COBJMACROS
/* Match the backend's use of the vendored DirectX headers on MinGW. */
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#include <windows.h>
#include <initguid.h>
#include <d3d12.h>
#include <d3d12sdklayers.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_test.h>

static const char vertex_source[] =
    "struct Output { float4 pos:SV_Position; float4 tint:TEXCOORD0; };\n"
    "#if VERTEX_SAMPLERS\n"
    "Texture2D<float4> t : register(t0,space0);\n"
    "SamplerState s : register(s0,space0);\n"
    "#endif\n"
    "Output main(uint id : SV_VertexID) {"
    " float2 p[3] = {float2(-1,-1), float2(-1,3), float2(3,-1)};"
    " Output o; o.pos = float4(p[id],0,1); o.tint = 1;\n"
    "#if VERTEX_SAMPLERS\n"
    " o.tint = t.SampleLevel(s,float2(0.5,0.5),0);\n"
    "#endif\n"
    " return o; }";

static const char shader_source[] =
    "#if COMPUTE\n"
    "#define RESOURCE_SPACE space0\n"
    "#if OUTPUT_TEXTURE\n"
    "RWTexture2D<float4> output : register(u0,space1);\n"
    "#else\n"
    "RWStructuredBuffer<float4> output : register(u0,space1);\n"
    "#endif\n"
    "cbuffer Params : register(b0,space2) { uint index; };\n"
    "#else\n"
    "#define RESOURCE_SPACE space2\n"
    "#endif\n"
    "#if SAMPLERS\n"
    "Texture2D<float4> t0 : register(t0,RESOURCE_SPACE);\n"
    "SamplerState s0 : register(s0,RESOURCE_SPACE);\n"
    "#if SAMPLERS == 3\n"
    "Texture2D<float4> t1 : register(t1,RESOURCE_SPACE);\n"
    "Texture2D<float4> t2 : register(t2,RESOURCE_SPACE);\n"
    "SamplerState s1 : register(s1,RESOURCE_SPACE);\n"
    "SamplerState s2 : register(s2,RESOURCE_SPACE);\n"
    "#endif\n"
    "#else\n"
    "StructuredBuffer<float4> b0 : register(t0,RESOURCE_SPACE);\n"
    "StructuredBuffer<float4> b1 : register(t1,RESOURCE_SPACE);\n"
    "StructuredBuffer<float4> b2 : register(t2,RESOURCE_SPACE);\n"
    "#endif\n"
    "float4 color() {\n"
    "#if SAMPLERS\n"
    " float4 c = t0.SampleLevel(s0,float2(0.5,0.5),0);\n"
    "#if SAMPLERS == 3\n"
    " c = (c + t1.SampleLevel(s1,float2(0.5,0.5),0) +"
    " t2.SampleLevel(s2,float2(0.5,0.5),0))/3;\n"
    "#endif\n"
    " return c;\n"
    "#else\n"
    " return (b0[0]+b1[0]+b2[0])/3;\n"
    "#endif\n"
    "}\n"
    "#if COMPUTE\n"
    "[numthreads(1,1,1)] void main() {\n"
    "#if OUTPUT_TEXTURE\n"
    " output[uint2(index%256,index/256)] = color();\n"
    "#else\n"
    " output[index] = color();\n"
    "#endif\n"
    "}\n"
    "#else\n"
    "struct Input { float4 pos:SV_Position; float4 tint:TEXCOORD0; };\n"
    "float4 main(Input input) : SV_Target0 { return color()*input.tint; }\n"
    "#endif\n";

typedef struct TestCase
{
    const char *name;
    bool compute;
    Uint32 samplers;
    bool vertex_sampler;
    Uint32 draws;
    bool output_texture;
} TestCase;

static const TestCase cases[] = {
    {"graphics-samplers", false, 3, false, 1367, false},
    {"graphics-retained", false, 1, true, 4097, false},
    {"graphics-views", false, 0, false, 21846, false},
    {"compute-samplers", true, 3, false, 1367, false},
    {"compute-retained", true, 1, false, 4097, false},
    {"compute-views", true, 0, false, 21846, false},
    {"compute-write-texture", true, 1, false, 4097, true}
};

typedef struct TestContext
{
    SDL_GPUDevice *gpu;
    ID3D12Device *native;
    ID3D12InfoQueue *messages;
    ID3D12InfoQueue1 *callback_queue;
    DWORD callback_cookie;
    SDL_AtomicInt current_draw;
    SDL_AtomicInt validation_errors;
    SDL_GPUTexture *textures[5];
    SDL_GPUBuffer *buffers[4];
    SDL_GPUBuffer *output;
    SDL_GPUTexture *output_texture;
    SDL_GPUTexture *target;
    SDL_GPUSampler *sampler;
    SDL_GPUGraphicsPipeline *pipeline;
    SDL_GPUComputePipeline *compute_pipeline;
    SDL_GPUTransferBuffer *download;
    const TestCase *test;
} TestContext;

static void WINAPI OnValidationMessage(D3D12_MESSAGE_CATEGORY category, D3D12_MESSAGE_SEVERITY severity,
                                       D3D12_MESSAGE_ID id, LPCSTR description, void *userdata)
{
    TestContext *ctx = (TestContext *)userdata;
    (void)category;
    if (severity <= D3D12_MESSAGE_SEVERITY_ERROR) {
        SDL_AddAtomicInt(&ctx->validation_errors, 1);
        /* Log synchronously: invalid descriptor handles can terminate inside
           the driver before the API call returns to CheckMessages. */
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "draw %d: D3D12 #%d: %s",
                     SDL_GetAtomicInt(&ctx->current_draw), id, description);
    }
}

static bool CheckMessages(TestContext *ctx, Uint32 draw)
{
    bool valid = true;
    UINT64 i, count = ID3D12InfoQueue_GetNumStoredMessages(ctx->messages);
    for (i = 0; i < count; ++i) {
        SIZE_T size = 0;
        D3D12_MESSAGE *message;
        if (FAILED(ID3D12InfoQueue_GetMessage(ctx->messages, i, NULL, &size))) {
            return false;
        }
        message = (D3D12_MESSAGE *)SDL_malloc(size);
        if (!message) {
            return false;
        }
        if (FAILED(ID3D12InfoQueue_GetMessage(ctx->messages, i, message, &size))) {
            SDL_free(message);
            return false;
        }
        if (message->Severity <= D3D12_MESSAGE_SEVERITY_ERROR) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "draw %u: D3D12 #%d: %s", draw, message->ID, message->pDescription);
            valid = false;
        }
        SDL_free(message);
    }
    ID3D12InfoQueue_ClearStoredMessages(ctx->messages);
    return valid && SDL_GetAtomicInt(&ctx->validation_errors) == 0;
}

static bool ObserveDevice(TestContext *ctx)
{
    IDXGIFactory6 *factory = NULL;
    IDXGIAdapter1 *adapter = NULL;
    HRESULT result;

    /* SDL's D3D12 backend selects the first high-performance adapter. D3D12
       devices are process-local singletons per adapter, so this obtains its
       existing device without adding a private SDL hook or a replacement GPU. */
    result = CreateDXGIFactory1(&IID_IDXGIFactory6, (void **)&factory);
    if (FAILED(result)) {
        return false;
    }
    result = IDXGIFactory6_EnumAdapterByGpuPreference(factory, 0, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
                                                     &IID_IDXGIAdapter1, (void **)&adapter);
    IDXGIFactory6_Release(factory);
    if (FAILED(result)) {
        return false;
    }
    result = D3D12CreateDevice((IUnknown *)adapter, D3D_FEATURE_LEVEL_11_0, &IID_ID3D12Device, (void **)&ctx->native);
    IDXGIAdapter1_Release(adapter);
    if (FAILED(result)) {
        return false;
    }
    result = ID3D12Device_QueryInterface(ctx->native, &IID_ID3D12InfoQueue, (void **)&ctx->messages);
    if (FAILED(result)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "D3D12 debug layer is required; install Windows Graphics Tools.");
        return false;
    }
    /* Fail the test rather than opening a debugger on validation errors. */
    ID3D12InfoQueue_SetBreakOnSeverity(ctx->messages, D3D12_MESSAGE_SEVERITY_CORRUPTION, FALSE);
    ID3D12InfoQueue_SetBreakOnSeverity(ctx->messages, D3D12_MESSAGE_SEVERITY_ERROR, FALSE);
    result = ID3D12Device_QueryInterface(ctx->native, &IID_ID3D12InfoQueue1, (void **)&ctx->callback_queue);
    if (FAILED(result)) {
        return false;
    }
    result = ID3D12InfoQueue1_RegisterMessageCallback(ctx->callback_queue, OnValidationMessage,
                                                    D3D12_MESSAGE_CALLBACK_IGNORE_FILTERS, ctx, &ctx->callback_cookie);
    if (FAILED(result)) {
        ID3D12InfoQueue1_Release(ctx->callback_queue);
        ctx->callback_queue = NULL;
        return false;
    }
    return CheckMessages(ctx, 0);
}

static ID3DBlob *CompileShader(const TestCase *test, bool vertex)
{
    ID3DBlob *code = NULL, *errors = NULL;
    const char *source = vertex ? vertex_source : shader_source;
    D3D_SHADER_MACRO macros[] = {
        {"VERTEX_SAMPLERS", test->vertex_sampler ? "1" : "0"},
        {"SAMPLERS", test->samplers == 3 ? "3" : test->samplers == 1 ? "1" : "0"},
        {"COMPUTE", test->compute ? "1" : "0"},
        {"OUTPUT_TEXTURE", test->output_texture ? "1" : "0"},
        {NULL, NULL}
    };
    HRESULT result = D3DCompile(source, SDL_strlen(source), NULL, macros, NULL, "main",
                               vertex ? "vs_5_1" : test->compute ? "cs_5_1" : "ps_5_1",
                               D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &code, &errors);
    if (errors) {
        SDL_Log("Shader compiler: %s", (const char *)ID3D10Blob_GetBufferPointer(errors));
        ID3D10Blob_Release(errors);
    }
    if (FAILED(result)) {
        return NULL;
    }
    return code;
}

static SDL_GPUShader *CreateShader(TestContext *ctx, bool vertex)
{
    ID3DBlob *code = CompileShader(ctx->test, vertex);
    SDL_GPUShaderCreateInfo info;
    SDL_GPUShader *shader;
    if (!code) {
        return NULL;
    }
    SDL_zero(info);
    info.code = (const Uint8 *)ID3D10Blob_GetBufferPointer(code);
    info.code_size = ID3D10Blob_GetBufferSize(code);
    info.entrypoint = "main";
    info.format = SDL_GPU_SHADERFORMAT_DXBC;
    info.stage = vertex ? SDL_GPU_SHADERSTAGE_VERTEX : SDL_GPU_SHADERSTAGE_FRAGMENT;
    info.num_samplers = vertex ? (Uint32)ctx->test->vertex_sampler : ctx->test->samplers;
    info.num_storage_buffers = !vertex && !ctx->test->samplers ? 3 : 0;
    shader = SDL_CreateGPUShader(ctx->gpu, &info);
    ID3D10Blob_Release(code);
    return shader;
}

static bool CreateResources(TestContext *ctx)
{
    const SDL_FColor colors[5] = {{1,0,0,1}, {0,1,0,1}, {0,0,1,1}, {0,0,0,1}, {1,1,1,1}};
    SDL_GPUTextureCreateInfo texture_info;
    SDL_GPUSamplerCreateInfo sampler_info;
    SDL_GPUTransferBufferCreateInfo transfer_info;
    SDL_GPUGraphicsPipelineCreateInfo pipeline_info;
    SDL_GPUColorTargetDescription target_description;
    SDL_GPUShader *vertex, *fragment;
    SDL_GPUCommandBuffer *command;
    Uint32 i;

    SDL_zero(texture_info);
    texture_info.type = SDL_GPU_TEXTURETYPE_2D;
    texture_info.format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM;
    texture_info.usage = SDL_GPU_TEXTUREUSAGE_SAMPLER | SDL_GPU_TEXTUREUSAGE_COLOR_TARGET;
    texture_info.width = texture_info.height = texture_info.layer_count_or_depth = texture_info.num_levels = 1;
    for (i = 0; i < SDL_arraysize(ctx->textures); ++i) {
        ctx->textures[i] = SDL_CreateGPUTexture(ctx->gpu, &texture_info);
        if (!ctx->textures[i]) {
            return false;
        }
    }
    ctx->target = SDL_CreateGPUTexture(ctx->gpu, &texture_info);
    SDL_zero(sampler_info);
    ctx->sampler = SDL_CreateGPUSampler(ctx->gpu, &sampler_info);
    SDL_zero(transfer_info);
    transfer_info.usage = SDL_GPU_TRANSFERBUFFERUSAGE_DOWNLOAD;
    transfer_info.size = ((ctx->test->draws + 255) / 256) * 256 * (Uint32)sizeof(SDL_FColor);
    ctx->download = SDL_CreateGPUTransferBuffer(ctx->gpu, &transfer_info);
    if (!ctx->target || !ctx->sampler || !ctx->download) {
        return false;
    }

    if (ctx->test->compute) {
        SDL_GPUComputePipelineCreateInfo info;
        SDL_GPUBufferCreateInfo buffer_info;
        ID3DBlob *code = CompileShader(ctx->test, false);
        if (!code) {
            return false;
        }
        SDL_zero(info);
        info.code = (const Uint8 *)ID3D10Blob_GetBufferPointer(code);
        info.code_size = ID3D10Blob_GetBufferSize(code);
        info.entrypoint = "main";
        info.format = SDL_GPU_SHADERFORMAT_DXBC;
        info.num_samplers = ctx->test->samplers;
        info.num_readonly_storage_buffers = ctx->test->samplers ? 0 : 3;
        info.num_readwrite_storage_buffers = ctx->test->output_texture ? 0 : 1;
        info.num_readwrite_storage_textures = ctx->test->output_texture ? 1 : 0;
        info.num_uniform_buffers = 1;
        info.threadcount_x = info.threadcount_y = info.threadcount_z = 1;
        ctx->compute_pipeline = SDL_CreateGPUComputePipeline(ctx->gpu, &info);
        ID3D10Blob_Release(code);
        if (ctx->test->output_texture) {
            texture_info.format = SDL_GPU_TEXTUREFORMAT_R32G32B32A32_FLOAT;
            texture_info.usage = SDL_GPU_TEXTUREUSAGE_COMPUTE_STORAGE_WRITE;
            texture_info.width = 256;
            texture_info.height = (ctx->test->draws + 255) / 256;
            ctx->output_texture = SDL_CreateGPUTexture(ctx->gpu, &texture_info);
        } else {
            SDL_zero(buffer_info);
            buffer_info.usage = SDL_GPU_BUFFERUSAGE_COMPUTE_STORAGE_WRITE;
            buffer_info.size = transfer_info.size;
            ctx->output = SDL_CreateGPUBuffer(ctx->gpu, &buffer_info);
        }
        if (!ctx->compute_pipeline || (!ctx->output && !ctx->output_texture)) {
            return false;
        }
    } else {
        vertex = CreateShader(ctx, true);
        fragment = CreateShader(ctx, false);
        if (!vertex || !fragment) {
            SDL_ReleaseGPUShader(ctx->gpu, vertex);
            SDL_ReleaseGPUShader(ctx->gpu, fragment);
            return false;
        }
        SDL_zero(target_description);
        target_description.format = texture_info.format;
        SDL_zero(pipeline_info);
        pipeline_info.vertex_shader = vertex;
        pipeline_info.fragment_shader = fragment;
        pipeline_info.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
        pipeline_info.rasterizer_state.enable_depth_clip = true;
        pipeline_info.target_info.num_color_targets = 1;
        pipeline_info.target_info.color_target_descriptions = &target_description;
        ctx->pipeline = SDL_CreateGPUGraphicsPipeline(ctx->gpu, &pipeline_info);
        SDL_ReleaseGPUShader(ctx->gpu, vertex);
        SDL_ReleaseGPUShader(ctx->gpu, fragment);
        if (!ctx->pipeline) {
            return false;
        }
    }

    if (!ctx->test->samplers) {
        SDL_GPUBufferCreateInfo info;
        SDL_GPUTransferBuffer *upload;
        SDL_GPUTransferBufferLocation source;
        SDL_GPUBufferRegion region;
        SDL_GPUCopyPass *copy;
        void *mapped;
        SDL_zero(info);
        info.usage = SDL_GPU_BUFFERUSAGE_GRAPHICS_STORAGE_READ | SDL_GPU_BUFFERUSAGE_COMPUTE_STORAGE_READ;
        info.size = sizeof(SDL_FColor);
        for (i = 0; i < SDL_arraysize(ctx->buffers); ++i) {
            ctx->buffers[i] = SDL_CreateGPUBuffer(ctx->gpu, &info);
            if (!ctx->buffers[i]) {
                return false;
            }
        }
        transfer_info.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD;
        transfer_info.size = sizeof(colors);
        upload = SDL_CreateGPUTransferBuffer(ctx->gpu, &transfer_info);
        if (!upload) {
            return false;
        }
        mapped = SDL_MapGPUTransferBuffer(ctx->gpu, upload, false);
        if (!mapped) {
            SDL_ReleaseGPUTransferBuffer(ctx->gpu, upload);
            return false;
        }
        SDL_memcpy(mapped, colors, sizeof(colors));
        SDL_UnmapGPUTransferBuffer(ctx->gpu, upload);
        command = SDL_AcquireGPUCommandBuffer(ctx->gpu);
        copy = command ? SDL_BeginGPUCopyPass(command) : NULL;
        if (!copy) {
            if (command) {
                SDL_CancelGPUCommandBuffer(command);
            }
            SDL_ReleaseGPUTransferBuffer(ctx->gpu, upload);
            return false;
        }
        for (i = 0; i < SDL_arraysize(ctx->buffers); ++i) {
            source.transfer_buffer = upload;
            source.offset = i * (Uint32)sizeof(SDL_FColor);
            region.buffer = ctx->buffers[i];
            region.offset = 0;
            region.size = sizeof(SDL_FColor);
            SDL_UploadToGPUBuffer(copy, &source, &region, false);
        }
        SDL_EndGPUCopyPass(copy);
        if (!SDL_SubmitGPUCommandBuffer(command)) {
            SDL_ReleaseGPUTransferBuffer(ctx->gpu, upload);
            return false;
        }
        SDL_ReleaseGPUTransferBuffer(ctx->gpu, upload);
    }

    command = SDL_AcquireGPUCommandBuffer(ctx->gpu);
    if (!command) {
        return false;
    }
    for (i = 0; i < SDL_arraysize(ctx->textures); ++i) {
        SDL_GPUColorTargetInfo color;
        SDL_GPURenderPass *pass;
        SDL_zero(color);
        color.texture = ctx->textures[i];
        color.clear_color = colors[i];
        color.load_op = SDL_GPU_LOADOP_CLEAR;
        color.store_op = SDL_GPU_STOREOP_STORE;
        pass = SDL_BeginGPURenderPass(command, &color, 1, NULL);
        if (!pass) {
            SDL_CancelGPUCommandBuffer(command);
            return false;
        }
        SDL_EndGPURenderPass(pass);
    }
    return SDL_SubmitGPUCommandBuffer(command) && SDL_WaitForGPUIdle(ctx->gpu) && CheckMessages(ctx, 0);
}

static SDL_FColor ExpectedColor(const TestCase *test, Uint32 index)
{
    SDL_FColor color;
    float component = test->samplers == 1 ? 1.0f : 1.0f / 3.0f;
    color.r = (index & 1) ? 0.0f : component;
    color.g = color.b = test->samplers == 1 ? 0.0f : component;
    color.a = 1.0f;
    return color;
}

static bool RunDraws(TestContext *ctx, Uint32 draws)
{
    SDL_GPUCommandBuffer *command = SDL_AcquireGPUCommandBuffer(ctx->gpu);
    SDL_GPUColorTargetInfo color;
    SDL_GPURenderPass *pass = NULL;
    SDL_GPUComputePass *compute_pass = NULL;
    SDL_GPUCopyPass *copy;
    SDL_GPUTextureRegion region;
    SDL_GPUTextureTransferInfo destination;
    SDL_GPUTextureSamplerBinding bindings[3];
    SDL_GPUBuffer *buffers[3];
    Uint32 i;
    void *mapped;
    bool valid = true;
    Uint64 start;

    if (!command) {
        return false;
    }
    if (ctx->test->compute) {
        SDL_GPUStorageBufferReadWriteBinding output_binding;
        SDL_GPUStorageTextureReadWriteBinding texture_binding;
        SDL_zero(output_binding);
        SDL_zero(texture_binding);
        output_binding.buffer = ctx->output;
        texture_binding.texture = ctx->output_texture;
        compute_pass = ctx->test->output_texture ?
            SDL_BeginGPUComputePass(command, &texture_binding, 1, NULL, 0) :
            SDL_BeginGPUComputePass(command, NULL, 0, &output_binding, 1);
        if (!compute_pass) {
            SDL_CancelGPUCommandBuffer(command);
            return false;
        }
        SDL_BindGPUComputePipeline(compute_pass, ctx->compute_pipeline);
    } else {
        SDL_zero(color);
        color.texture = ctx->target;
        color.load_op = SDL_GPU_LOADOP_CLEAR;
        color.store_op = SDL_GPU_STOREOP_STORE;
        pass = SDL_BeginGPURenderPass(command, &color, 1, NULL);
        if (!pass) {
            SDL_CancelGPUCommandBuffer(command);
            return false;
        }
        SDL_BindGPUGraphicsPipeline(pass, ctx->pipeline);
        if (ctx->test->vertex_sampler) {
            SDL_GPUTextureSamplerBinding vertex_binding;
            vertex_binding.texture = ctx->textures[4];
            vertex_binding.sampler = ctx->sampler;
            /* Deliberately never rebound by the application during the pass. */
            SDL_BindGPUVertexSamplers(pass, 0, &vertex_binding, 1);
        }
    }
    for (i = 0; i < 3; ++i) {
        bindings[i].texture = ctx->textures[i];
        bindings[i].sampler = ctx->sampler;
        buffers[i] = ctx->buffers[i];
    }
    start = SDL_GetTicksNS();
    for (i = 0; i < draws; ++i) {
        /* Change an actual resource, not a private heap index. In the three-
           sampler case the original 683rd draw needs entries 2046..2048. */
        bindings[0].texture = ctx->textures[(i & 1) ? 3 : 0];
        buffers[0] = ctx->buffers[(i & 1) ? 3 : 0];
        SDL_SetAtomicInt(&ctx->current_draw, (int)i + 1);
        if (compute_pass) {
            Uint32 params[4] = {i, 0, 0, 0};
            if (ctx->test->samplers) {
                SDL_BindGPUComputeSamplers(compute_pass, 0, bindings, ctx->test->samplers);
            } else {
                SDL_BindGPUComputeStorageBuffers(compute_pass, 0, buffers, 3);
            }
            /* Each dispatch writes a different element: no unsynchronized
               overlapping writes within a compute pass. */
            SDL_PushGPUComputeUniformData(command, 0, params, sizeof(params));
            SDL_DispatchGPUCompute(compute_pass, 1, 1, 1);
        } else {
            if (ctx->test->samplers) {
                SDL_BindGPUFragmentSamplers(pass, 0, bindings, ctx->test->samplers);
            } else {
                SDL_BindGPUFragmentStorageBuffers(pass, 0, buffers, 3);
            }
            SDL_DrawGPUPrimitives(pass, 3, 1, 0, 0);
        }
        if (!CheckMessages(ctx, i + 1)) {
            valid = false;
            break;
        }
    }
    SDL_Log("%s: recorded %u operations in %.3f ms (debug layer and message checks enabled)",
            ctx->test->name, i, (double)(SDL_GetTicksNS() - start) / 1000000.0);
    if (compute_pass) {
        SDL_EndGPUComputePass(compute_pass);
    } else {
        SDL_EndGPURenderPass(pass);
    }
    if (!valid) {
        SDL_CancelGPUCommandBuffer(command);
        return false;
    }

    copy = SDL_BeginGPUCopyPass(command);
    if (!copy) {
        SDL_CancelGPUCommandBuffer(command);
        return false;
    }
    if (ctx->test->compute && !ctx->test->output_texture) {
        SDL_GPUBufferRegion source;
        SDL_GPUTransferBufferLocation target;
        source.buffer = ctx->output;
        source.offset = 0;
        source.size = draws * (Uint32)sizeof(SDL_FColor);
        target.transfer_buffer = ctx->download;
        target.offset = 0;
        SDL_DownloadFromGPUBuffer(copy, &source, &target);
    } else {
        SDL_zero(region);
        region.texture = ctx->test->output_texture ? ctx->output_texture : ctx->target;
        region.w = region.h = region.d = 1;
        if (ctx->test->output_texture) {
            region.w = 256;
            region.h = (draws + 255) / 256;
        }
        SDL_zero(destination);
        destination.transfer_buffer = ctx->download;
        SDL_DownloadFromGPUTexture(copy, &region, &destination);
    }
    SDL_EndGPUCopyPass(copy);
    if (!SDL_SubmitGPUCommandBuffer(command) || !SDL_WaitForGPUIdle(ctx->gpu) || !CheckMessages(ctx, draws)) {
        return false;
    }
    mapped = SDL_MapGPUTransferBuffer(ctx->gpu, ctx->download, false);
    if (!mapped) {
        return false;
    }
    if (ctx->test->compute) {
        const SDL_FColor *pixels = (const SDL_FColor *)mapped;
        for (i = 0; i < draws; ++i) {
            SDL_FColor expected = ExpectedColor(ctx->test, i);
            valid = SDL_fabsf(pixels[i].r - expected.r) <= 0.00001f &&
                    SDL_fabsf(pixels[i].g - expected.g) <= 0.00001f &&
                    SDL_fabsf(pixels[i].b - expected.b) <= 0.00001f && pixels[i].a == 1.0f;
            if (!valid) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "dispatch %u: output=(%f,%f,%f,%f), expected=(%f,%f,%f,%f)",
                             i + 1, pixels[i].r, pixels[i].g, pixels[i].b, pixels[i].a,
                             expected.r, expected.g, expected.b, expected.a);
                break;
            }
        }
        SDL_Log("%s: checked %u/%u output elements", ctx->test->name, i, draws);
    } else {
        const Uint8 *pixel = (const Uint8 *)mapped;
        SDL_FColor expected = ExpectedColor(ctx->test, draws - 1);
        SDL_Log("%u draws: pixel=(%u,%u,%u,%u)", draws, pixel[0], pixel[1], pixel[2], pixel[3]);
        valid = SDL_abs((int)pixel[0] - (int)SDL_roundf(expected.r * 255)) <= 1 &&
                SDL_abs((int)pixel[1] - (int)SDL_roundf(expected.g * 255)) <= 1 &&
                SDL_abs((int)pixel[2] - (int)SDL_roundf(expected.b * 255)) <= 1 && pixel[3] == 255;
    }
    SDL_UnmapGPUTransferBuffer(ctx->gpu, ctx->download);
    return valid;
}

static bool RunCase(const TestCase *test, Uint32 iterations)
{
    TestContext ctx;
    Uint32 i;
    bool passed = false;
    SDL_zero(ctx);
    ctx.test = test;
    SDL_Log("Case %s: %u operations", test->name, test->draws);
    ctx.gpu = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_DXBC, true, "direct3d12");
    if (ctx.gpu && ObserveDevice(&ctx) && CreateResources(&ctx)) {
        passed = true;
        for (i = 0; i < iterations && passed; ++i) {
            /* Reuse the device, resources, and returned command buffers/heaps. */
            passed = RunDraws(&ctx, test->draws);
            SDLTest_AssertCheck(passed, "%s iteration %u: descriptor batches fit and GPU output matches after %u operations",
                                test->name, i + 1, test->draws);
        }
    } else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Test setup failed: %s", SDL_GetError());
    }
    if (ctx.gpu) {
        SDL_ReleaseGPUTransferBuffer(ctx.gpu, ctx.download);
        SDL_ReleaseGPUGraphicsPipeline(ctx.gpu, ctx.pipeline);
        SDL_ReleaseGPUComputePipeline(ctx.gpu, ctx.compute_pipeline);
        SDL_ReleaseGPUSampler(ctx.gpu, ctx.sampler);
        SDL_ReleaseGPUTexture(ctx.gpu, ctx.target);
        for (i = 0; i < SDL_arraysize(ctx.textures); ++i) {
            SDL_ReleaseGPUTexture(ctx.gpu, ctx.textures[i]);
        }
        for (i = 0; i < SDL_arraysize(ctx.buffers); ++i) {
            SDL_ReleaseGPUBuffer(ctx.gpu, ctx.buffers[i]);
        }
        SDL_ReleaseGPUBuffer(ctx.gpu, ctx.output);
        SDL_ReleaseGPUTexture(ctx.gpu, ctx.output_texture);
        SDL_DestroyGPUDevice(ctx.gpu);
    }
    if (ctx.messages) {
        passed = CheckMessages(&ctx, test->draws) && passed;
    }
    if (ctx.callback_queue) {
        ID3D12InfoQueue1_UnregisterMessageCallback(ctx.callback_queue, ctx.callback_cookie);
        ID3D12InfoQueue1_Release(ctx.callback_queue);
    }
    if (ctx.messages) {
        ID3D12InfoQueue_Release(ctx.messages);
    }
    if (ctx.native) {
        ID3D12Device_Release(ctx.native);
    }
    return passed;
}

int main(int argc, char **argv)
{
    const char *filter = NULL;
    Uint32 override_draws = 0, iterations = 3, executed = 0, i;
    int arg;
    bool passed = true;
    for (arg = 1; arg < argc; ++arg) {
        if (SDL_strcmp(argv[arg], "--case") == 0 && arg + 1 < argc) {
            filter = argv[++arg];
        } else if (SDL_strcmp(argv[arg], "--iterations") == 0 && arg + 1 < argc) {
            int value = SDL_atoi(argv[++arg]);
            if (value < 1 || value > 100) {
                return 2;
            }
            iterations = (Uint32)value;
        } else if (SDL_strcmp(argv[arg], "--draws") == 0 && arg + 1 < argc) {
            int value = SDL_atoi(argv[++arg]);
            if (value < 1 || value > 100000) {
                return 2;
            }
            override_draws = (Uint32)value;
        } else {
            SDL_Log("Usage: %s [--case NAME] [--draws 1..100000] [--iterations 1..100]", argv[0]);
            return 2;
        }
    }
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init: %s", SDL_GetError());
        return 2;
    }
    SDL_Log("SDL revision: %s", SDL_GetRevision());
    SDL_SetLogPriority(SDL_LOG_CATEGORY_GPU, SDL_LOG_PRIORITY_INFO);
    for (i = 0; i < SDL_arraysize(cases); ++i) {
        TestCase test = cases[i];
        if (filter && SDL_strcmp(filter, test.name) != 0) {
            continue;
        }
        if (override_draws) {
            test.draws = override_draws;
        }
        passed = RunCase(&test, iterations) && passed;
        ++executed;
    }
    SDL_Quit();
    return passed && executed > 0 ? 0 : 1;
}
