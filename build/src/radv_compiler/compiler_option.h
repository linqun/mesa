#pragma once

#ifdef __cplusplus
extern "C"{
#endif

#define MAX_LAYOUT_COUNT 100
#define MAX_VERTEX_ATTRIB_COUNT 32

// =====================================================================================================================
// Copy from radv_pipeline_key
struct PipelineKey {
    uint32_t instance_rate_inputs;
    uint32_t instance_rate_divisors[MAX_VERTEX_ATTRIB_COUNT];
    unsigned tess_input_vertices;
    uint32_t col_format;
    uint8_t  log2_ps_iter_samples;
    uint8_t  log2_num_samples;
    uint32_t multisample : 1;
    uint32_t has_multiview_view_index : 1;
};

// =====================================================================================================================
struct ShaderSource
{
    uint32_t  dataSize;   // Size of the shader binary data
    uint8_t*  pData;      // Shader binary data
};

// =====================================================================================================================
struct StandaloneOptions
{
    const char* pGlslName[MESA_SHADER_COMPUTE + 1];   // GLSL source file name
    const char* pSpvasName[MESA_SHADER_COMPUTE + 1];  // SPIRV assemble file name
    const char* pSpvName[MESA_SHADER_COMPUTE + 1];    // SPIRV binary file name
    const char* pPipeName;                            // PIPE info file name
    const char* pLayoutList[MAX_LAYOUT_COUNT];        // layout lists
    int layoutCount;
    int spvasCount;
    int spvCount;

    void* pPipelineInfoFile;                          // Handle of pipeline info file
    struct ShaderSource sources[MESA_SHADER_COMPUTE + 1];
    struct radv_pipeline_layout pipelineLayout;
    struct PipelineKey pipelineKey;
    VkPipelineShaderStageCreateInfo stages[MESA_SHADER_COMPUTE + 1];
    VkPipelineShaderStageCreateInfo* pStages[MESA_SHADER_COMPUTE + 1];
};

// Initialize compiler options
bool Init();

// Print the usage of the compiler
void Usage();

// Parse pipe info file
bool ParsePipeFile();

// Parse layout
struct radv_pipeline_layout* ParseLayout();

// Compile shader source, include GLSL source, SPIRV binary and SPIRV assemble file
void CompileSource();

extern struct StandaloneOptions g_options;

#ifdef __cplusplus
}
#endif
