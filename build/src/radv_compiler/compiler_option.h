#pragma once

#ifdef __cplusplus
extern "C"{
#endif

#define MAX_LAYOUT_COUNT 100
#define MAX_VERTEX_ATTRIB_COUNT 32
struct PipelineKey {
    uint32_t instance_rate_inputs;
    uint32_t instance_rate_divisors[MAX_VERTEX_ATTRIB_COUNT];
    unsigned tess_input_vertices;
    uint32_t col_format;
    uint8_t log2_ps_iter_samples;
    uint8_t log2_num_samples;
    uint32_t multisample : 1;
    uint32_t has_multiview_view_index : 1;
};

struct ShaderSource
{
    uint32_t              dataSize;   // Size of the shader binary data
    uint8_t*              pData;      // Shader binary data
};

struct StandaloneOptions
{
    const char* pGlslName[MESA_SHADER_COMPUTE + 1];
    const char* pSpvasName[MESA_SHADER_COMPUTE + 1];
    const char* pSpvName[MESA_SHADER_COMPUTE + 1];
    const char* pPipeName;
    const char* pLayoutList[MAX_LAYOUT_COUNT];
    int layoutCount;
    int spvasCount;
    int spvCount;
    void* pPipelineInfoFile;
    struct ShaderSource sources[MESA_SHADER_COMPUTE + 1];
    struct radv_pipeline_layout pipelineLayout;
    struct PipelineKey pipelineKey;
    VkPipelineShaderStageCreateInfo stages[MESA_SHADER_COMPUTE + 1];
    VkPipelineShaderStageCreateInfo* pStages[MESA_SHADER_COMPUTE + 1];
};

extern struct StandaloneOptions g_options;
bool Init();
void Usage();
bool ParsePipeFile();
struct radv_pipeline_layout* ParseLayout();
void CompileSource();

#ifdef __cplusplus
}
#endif
