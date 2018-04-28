#include "util/u_math.h"
#include "shader_enums.h"
#include "radv_descriptor_set.h"
#define SPVGEN_STATIC_LIB  1
#include "spvgen.h"
#include "vfx.h"
#include "sid.h"
#include "compiler_option.h"

struct StandaloneOptions g_options = {0};

struct DescriptorLayoutOption
{
    int setId;
    int bindId;
    int type;
    int arraySize;
    int sizeInDwords;
    int offsetInDwords;
    int stageMask;
    bool immutable;
    bool dynamic;
};

typedef std::map<uint32_t, DescriptorLayoutOption> PipelineLayoutMap;
const uint32_t PushConstantKey = 0xffff0000;

void MergePipelineLayout(gl_shader_stage stage, const Llpc::PipelineShaderInfo* pShaderInfo, std::map<uint32_t, DescriptorLayoutOption>& pipeLayoutMap);
void BuildPipelineLayout(PipelineLayoutMap& pipeLayoutMap, const Llpc::PipelineShaderInfo* pShaderInfo[]);
// =====================================================================================================================
// Gets the name string of shader stage.
const char* GetShaderStageName(
    gl_shader_stage shaderStage)  // Shader stage
{
    const char* pName = NULL;
    assert(shaderStage < MESA_SHADER_COMPUTE + 1);

    static const char* ShaderStageNames[] =
    {
        "vertex",
        "tessellation control",
        "tessellation evaluation",
        "geometry",
        "fragment",
        "compute",
    };

    pName = ShaderStageNames[shaderStage];
    return pName;
}

bool CompileGlsl(gl_shader_stage stage, const char* pFileName)
{
    FILE* fp = fopen(pFileName, "r");
    if (fp == NULL)
    {
       printf("Fail to open file %s\n", pFileName);
       return false;
    }
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
   
    char * glslsource = (char*)malloc(size);
    memset(glslsource, 0, size);
    int realsize = fread(glslsource, 1, size, fp);
    int sourceStringCount[6] = {0};
    sourceStringCount[stage] = 1;
    const char* const* sourceList[6] = { NULL};
    sourceList[stage] = &glslsource;
    void* pProgram = NULL;
    const char * pLog = NULL;
    int ret = spvCompileAndLinkProgram(sourceStringCount, sourceList, &pProgram, &pLog);
    if (ret)
    {
        const uint32_t* pData = NULL;
        size = spvGetSpirvBinaryFromProgram(pProgram, (EShLanguage)stage, &pData);
        g_options.sources[stage].dataSize = size;
      
        g_options.sources[stage].pData = (uint8_t*)malloc(size);
      
        memcpy(g_options.sources[stage].pData, pData, size);
        fclose(fp);
    }
    else
    {
        printf("Fail to compile shader: \n%s\n", pLog);
    }

    return ret;
}

bool AsmSpv(gl_shader_stage stage, const char* pFileName)
{
    FILE* fp = fopen(pFileName, "r");
    if (fp == NULL)
    {
       printf("Fail to open file %s\n", pFileName);
       return false;
    }
    fseek(fp, 0, SEEK_END);
    size_t textSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
   
    char* pSpvText = new char[textSize + 1];
    memset(pSpvText, 0, textSize + 1);
    size_t realSize = fread(pSpvText, 1, textSize, fp);
    int32_t binSize = realSize * 4 + 1024; // Estimated SPIR-V binary size
    g_options.sources[stage].pData = (uint8_t*)malloc(binSize);
    uint32_t* pSpvBin = (uint32_t*)g_options.sources[stage].pData;
    const char* pLog = nullptr;
    binSize = spvAssembleSpirv(pSpvText, binSize, pSpvBin, &pLog);
    if (binSize < 0)
    {
        printf("Fails to assemble SPIR-V: \n %s\n", pLog);
        return false;
    }
    else
    {
        g_options.sources[stage].dataSize = binSize;
    }
    fclose(fp);
    delete[] pSpvText;
    return true;
}

bool LoadSpv(gl_shader_stage stage, const char* pFileName)
{
   FILE* fp = fopen(pFileName, "rb");
   if (fp == NULL)
   {
      printf("Fail to open file %s\n", pFileName);
      return false;
   }
   fseek(fp, 0, SEEK_END);
   int size = ftell(fp);
   const int MinSpvSize = 16;
   fseek(fp, 0, SEEK_SET);
   if (size < MinSpvSize)
   {
      fclose(fp);
      return false;
   }
   g_options.sources[stage].dataSize = size;
   g_options.sources[stage].pData = (uint8_t*)malloc(size);
   fread(g_options.sources[stage].pData, 1, size, fp);
   fclose(fp);
   return true;
}

bool Init()
{
    return InitSpvGen();
}

bool ParsePipeFile()
{
    const char* pLog = NULL;
    bool result = true;
    bool vfxResult = vfxParseFile(g_options.pPipeName,
                                  0,
                                  nullptr,
                                  VfxDocTypePipeline,
                                  &g_options.pPipelineInfoFile,
                                  &pLog);
    if (vfxResult)
    {
        VfxPipelineStatePtr pPipelineState = nullptr;
        vfxGetPipelineDoc(g_options.pPipelineInfoFile, &pPipelineState);

        if (pPipelineState->version != Llpc::Version)
        {
            printf("Version incompatible, SPVGEN::Version = %d,  Compiler::Version = %d\n",
                pPipelineState->version, Llpc::Version);
            result = false;
        }
        else
        {
            if (pPipelineState->stages[MESA_SHADER_COMPUTE].dataSize == 0)
            {
                // Graphic pipeline
                for (uint32_t target = 0; target < MaxColorTargets; ++target)
                {
                    if ((target == 0) ||
                        (pPipelineState->gfxPipelineInfo.cbState.target[target].format != VK_FORMAT_UNDEFINED))
                    {
                        g_options.pipelineKey.col_format = V_028714_SPI_SHADER_32_ABGR << (4 * target);
                    }
                }

                g_options.pipelineKey.tess_input_vertices = pPipelineState->gfxPipelineInfo.iaState.patchControlPoints;
                g_options.pipelineKey.has_multiview_view_index = pPipelineState->gfxPipelineInfo.iaState.enableMultiView;
                g_options.pipelineKey.log2_num_samples = util_next_power_of_two(pPipelineState->gfxPipelineInfo.rsState.numSamples);
                g_options.pipelineKey.log2_ps_iter_samples = pPipelineState->gfxPipelineInfo.rsState.perSampleShading ?
                                                             g_options.pipelineKey.log2_num_samples : 0;
                uint32_t binding_input_rate = 0;
                uint32_t instance_rate_divisors[MAX_VERTEX_ATTRIB_COUNT];
                const VkPipelineVertexInputStateCreateInfo* pVertexInput = pPipelineState->gfxPipelineInfo.pVertexInput;
                if (pVertexInput)
                {
                    for (unsigned i = 0; i < pVertexInput->vertexBindingDescriptionCount; ++i)
                    {
                       if (pVertexInput->pVertexBindingDescriptions[i].inputRate == VK_VERTEX_INPUT_RATE_INSTANCE)
                       {
                          unsigned binding = pVertexInput->pVertexBindingDescriptions[i].binding;
                          binding_input_rate |= 1u << binding;
                          instance_rate_divisors[binding] = 1;
                       }
                    }
                 
                    for (unsigned i = 0; i < pVertexInput->vertexAttributeDescriptionCount; ++i)
                    {
                       unsigned binding;
                       binding = pVertexInput->pVertexAttributeDescriptions[i].binding;
                       if (binding_input_rate & (1u << binding))
                       {
                          unsigned location = pVertexInput->pVertexAttributeDescriptions[i].location;
                          g_options.pipelineKey.instance_rate_inputs |= 1u << location;
                          g_options.pipelineKey.instance_rate_divisors[location] = instance_rate_divisors[binding];
                       }
                    }    for (unsigned i = 0; i < pVertexInput->vertexBindingDescriptionCount; ++i)
                    {
                       if (pVertexInput->pVertexBindingDescriptions[i].inputRate == VK_VERTEX_INPUT_RATE_INSTANCE)
                       {
                          unsigned binding = pVertexInput->pVertexBindingDescriptions[i].binding;
                          binding_input_rate |= 1u << binding;
                          instance_rate_divisors[binding] = 1;
                       }
                    }
                 
                    for (unsigned i = 0; i < pVertexInput->vertexAttributeDescriptionCount; ++i)
                    {
                       unsigned binding;
                       binding = pVertexInput->pVertexAttributeDescriptions[i].binding;
                       if (binding_input_rate & (1u << binding))
                       {
                          unsigned location = pVertexInput->pVertexAttributeDescriptions[i].location;
                          g_options.pipelineKey.instance_rate_inputs |= 1u << location;
                          g_options.pipelineKey.instance_rate_divisors[location] = instance_rate_divisors[binding];
                       }
                    }
                }
            }
            else
            {
                // Compute pipeline
            }

            const Llpc::PipelineShaderInfo* pShaderInfo[] =
            {
               &pPipelineState->gfxPipelineInfo.vs,
               &pPipelineState->gfxPipelineInfo.tcs,
               &pPipelineState->gfxPipelineInfo.tes,
               &pPipelineState->gfxPipelineInfo.gs,
               &pPipelineState->gfxPipelineInfo.fs,
               &pPipelineState->compPipelineInfo.cs
            };

            PipelineLayoutMap pipeLayoutMap;
            for (uint32_t stage = 0; stage <= MESA_SHADER_COMPUTE; ++stage)
            {
                if (pPipelineState->stages[stage].dataSize > 0)
                {
                    g_options.sources[stage].dataSize = pPipelineState->stages[stage].dataSize;
                    g_options.sources[stage].pData = pPipelineState->stages[stage].pData;
                    g_options.stages[stage].pName = pShaderInfo[stage]->pEntryTarget;
                    g_options.stages[stage].pSpecializationInfo = pShaderInfo[stage]->pSpecializationInfo;
                    g_options.stages[stage].stage = VkShaderStageFlagBits(1 << stage);
                    g_options.pStages[stage] = &g_options.stages[stage];

                    MergePipelineLayout(gl_shader_stage(stage), pShaderInfo[stage], pipeLayoutMap);
                    // Disassemble SPIRV code
                    uint32_t binSize =  pPipelineState->stages[stage].dataSize;
                    uint32_t textSize = binSize * 10 + 1024;
                    char* pSpvText = new char[textSize];
                    assert(pSpvText != nullptr);
                    memset(pSpvText, 0, textSize);
                    printf("\nSPIR-V disassembly for %s\n", GetShaderStageName(gl_shader_stage(stage)));
                    spvDisassembleSpirv(binSize, pPipelineState->stages[stage].pData, textSize, pSpvText);
                    printf(pSpvText);
                    printf("\n");
                    delete[] pSpvText;
                }
            }

            BuildPipelineLayout(pipeLayoutMap, pShaderInfo);
        }
    }
    else
    {
        printf("Failed to parse input file: %s\n%s\n", g_options.pPipeName, pLog);
        result = false;
    }
    return result;
}

void GetResourceNodeInfo(Llpc::ResourceMappingNodeType resType, bool isRoot, int& vkType, int& nodeSize)
{
    switch(resType)
    {
    case Llpc::ResourceMappingNodeType::DescriptorResource:
        vkType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
        nodeSize = 32;
        break;
    case Llpc::ResourceMappingNodeType::DescriptorSampler:
        vkType = VK_DESCRIPTOR_TYPE_SAMPLER;
        nodeSize = 16;
        break;
    case Llpc::ResourceMappingNodeType::DescriptorCombinedTexture:
        vkType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        nodeSize = 48;
        break;
    case Llpc::ResourceMappingNodeType::DescriptorTexelBuffer:
        vkType = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
        nodeSize = 16;
        break;
    case Llpc::ResourceMappingNodeType::DescriptorBuffer:
        vkType = isRoot ? VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC : VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        nodeSize = 16;
        break;
    case Llpc::ResourceMappingNodeType::DescriptorBufferCompact:
        vkType = isRoot ? VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC : VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        nodeSize = 8;
        break;
    default:
        assert(0);
        break;
    }
}

void InsertBindingLayout(gl_shader_stage stage, const Llpc::ResourceMappingNode* pNode, PipelineLayoutMap& pipeLayoutMap, bool isRoot)
{
    uint32_t key = 0;
    PipelineLayoutMap::iterator it;
    int nodeSize = 0;
    DescriptorLayoutOption bindingLayout = {};
    switch(pNode->type)
    {
    case Llpc::ResourceMappingNodeType::DescriptorResource:
    case Llpc::ResourceMappingNodeType::DescriptorSampler:
    case Llpc::ResourceMappingNodeType::DescriptorCombinedTexture:
    case Llpc::ResourceMappingNodeType::DescriptorTexelBuffer:
    case Llpc::ResourceMappingNodeType::DescriptorBuffer:
    case Llpc::ResourceMappingNodeType::DescriptorBufferCompact:
        GetResourceNodeInfo(pNode->type, isRoot, bindingLayout.type, nodeSize);
        key = (pNode->srdRange.set << 16) + pNode->srdRange.binding;
        it = pipeLayoutMap.find(key);
        if (it != pipeLayoutMap.end())
        {
            it->second.stageMask |= (1 << stage);
        }
        else
        {
            bindingLayout.setId =  pNode->srdRange.set;
            bindingLayout.bindId = pNode->srdRange.binding;
            bindingLayout.arraySize = pNode->sizeInDwords * 4 / nodeSize;
            bindingLayout.sizeInDwords = pNode->sizeInDwords;
            bindingLayout.offsetInDwords = pNode->offsetInDwords;
            bindingLayout.stageMask = (1 << stage);
            bindingLayout.dynamic = isRoot;
            pipeLayoutMap[key] = bindingLayout;
        }
        break;
        break;
    case Llpc::ResourceMappingNodeType::DescriptorTableVaPtr:
        for (uint32_t i = 0; i < pNode->tablePtr.nodeCount; ++i)
        {
           InsertBindingLayout(stage, &pNode->tablePtr.pNext[i], pipeLayoutMap, false);
        }
        break;
    case Llpc::ResourceMappingNodeType::PushConst:
        key = PushConstantKey;
        it = pipeLayoutMap.find(key);
        if (it != pipeLayoutMap.end())
        {
            it->second.stageMask |= (1 << stage);
            it->second.sizeInDwords = max(it->second.sizeInDwords, pNode->sizeInDwords);
        }
        else
        {
            bindingLayout.setId = PushConstantKey >> 16;
            bindingLayout.bindId = PushConstantKey & 0xffff;
            bindingLayout.sizeInDwords = pNode->sizeInDwords;
            bindingLayout.stageMask = (1 << stage);
            pipeLayoutMap[PushConstantKey] = bindingLayout;
        }
        break;
    case Llpc::ResourceMappingNodeType::DescriptorFmask:
    case Llpc::ResourceMappingNodeType::IndirectUserDataVaPtr:
        break;
    case Llpc::ResourceMappingNodeType::Unknown:
    default:
        assert(0);
        break;
    }
}

void BuildPipelineLayout(PipelineLayoutMap& pipeLayoutMap, const Llpc::PipelineShaderInfo* pShaderInfo[])
{
    if (pipeLayoutMap.empty())
    {
        return;
    }
    uint32_t maxSet = 0;
    uint32_t maxBinding[MAX_SETS] = { };
    uint32_t immutableSize[MAX_SETS] = { };
    uint32_t shaderStages[MAX_SETS] = { };
    uint32_t dynamicShaderStages[MAX_SETS] = {};
    uint32_t immutableOffset[MAX_SETS] = { };
    auto* pLayout = &g_options.pipelineLayout;
    for (auto iter : pipeLayoutMap)
    {
        if (iter.first == PushConstantKey)
        {
            pLayout->push_constant_size = iter.second.sizeInDwords * 4;
        }
        else
        {
            uint32_t set = iter.first >> 16;
            uint32_t binding = iter.first & 0xffff;
            maxSet = max(maxSet, set + 1);
            maxBinding[set] = max(maxBinding[set], binding + 1);
            if (iter.second.immutable)
            {
               immutableSize[set] += iter.second.sizeInDwords * 4;
            }
            shaderStages[set] |= iter.second.stageMask;
            if (iter.second.dynamic)
            {
               dynamicShaderStages[set] |= iter.second.stageMask;
            }
        }
    }

    pLayout->num_sets = maxSet;
    for (uint32_t i = 0; i < pLayout->num_sets; ++i)
    {
        int layoutSize = sizeof (struct radv_descriptor_set_layout) +
                         sizeof(struct radv_descriptor_set_binding_layout) * maxBinding[i] +
                         immutableSize[i];

        pLayout->set[i].layout = (struct radv_descriptor_set_layout *)malloc(layoutSize);
        pLayout->set[i].size = layoutSize;
        memset(g_options.pipelineLayout.set[i].layout, 0, layoutSize);

        pLayout->set[i].layout->binding_count = maxBinding[i];
        pLayout->set[i].layout->shader_stages = shaderStages[i];
        pLayout->set[i].layout->size = layoutSize;
        pLayout->set[i].layout->dynamic_shader_stages = dynamicShaderStages[i];
        pLayout->set[i].layout->has_immutable_samplers = immutableSize[i] != 0;
        immutableOffset[i] = sizeof(struct radv_descriptor_set_binding_layout) * maxBinding[i];
    }

    uint32_t dynamicOffset = 0;
    for (auto iter : pipeLayoutMap)
    {
        if (iter.first == PushConstantKey)
        {
             continue;
        }

        uint32_t set = iter.first >> 16;
        uint32_t binding = iter.first & 0xffff;
        auto pBinding = &pLayout->set[set].layout->binding[binding];
        pBinding->type = (VkDescriptorType)iter.second.type;
        pBinding->array_size = iter.second.arraySize;
        pBinding->offset = iter.second.offsetInDwords * 4;
        pBinding->buffer_offset = pBinding->offset;
        pBinding->size = iter.second.sizeInDwords * 4 / iter.second.arraySize;
        if (pBinding->size == 48)
        {
            pBinding->size = 64;
        }
        if (iter.second.dynamic)
        {
           pBinding->dynamic_offset_offset = dynamicOffset;
           pBinding->dynamic_offset_count = iter.second.arraySize;
           dynamicOffset += iter.second.arraySize;
        }

        if (iter.second.immutable)
        {
           pBinding->immutable_samplers_offset = immutableOffset[set];
           pBinding->immutable_samplers_equal = false;
           immutableOffset[set] += pBinding->size;
        }
    }
}

void MergePipelineLayout(gl_shader_stage stage, const Llpc::PipelineShaderInfo* pShaderInfo, std::map<uint32_t, DescriptorLayoutOption>& pipeLayoutMap)
{
    for (uint32_t i = 0; i < pShaderInfo->userDataNodeCount; ++i)
    {
        InsertBindingLayout(stage, &pShaderInfo->pUserDataNodes[i], pipeLayoutMap, true);
    }

    for (uint32_t i = 0; i < pShaderInfo->descriptorRangeValueCount; ++i)
    {
        uint32_t key = (pShaderInfo->pDescriptorRangeValues[i].set << 16) + pShaderInfo->pDescriptorRangeValues[i].binding;
        PipelineLayoutMap::iterator it = pipeLayoutMap.find(key);
        if (it != pipeLayoutMap.end())
        {
            it->second.immutable = true;
        }
    }

}

struct radv_pipeline_layout*
ParseLayout()
{
    if (g_options.layoutCount == 0)
    {
        return &g_options.pipelineLayout;
    }
    int maxSet = -1;
    int maxBind[MAX_SETS] = {0};
    struct DescriptorLayoutOption * pLayoutOptions = (struct DescriptorLayoutOption *)malloc(sizeof(struct DescriptorLayoutOption) * g_options.layoutCount);
    memset(pLayoutOptions, -1, sizeof(struct DescriptorLayoutOption) * g_options.layoutCount);
    for (int i = 0; i < g_options.layoutCount; ++i)
    {
        const char* pLayout = g_options.pLayoutList[i];
        if (strncmp(pLayout, "set[", 4) != 0)
        {
            printf("Invalid Layout: %s\n", pLayout);
            continue;
        }
        char* pBind = NULL; 
        pLayoutOptions[i].setId = strtoul(pLayout + 4, &pBind, 10);
        if (strncmp(pBind, "].bind[", 7) != 0)
        {
            printf("Invalid Layout: %s\n", pLayout);
            continue;
        }
        char* pParam = NULL;
        pLayoutOptions[i].bindId = strtoul(pBind + 7, &pParam, 10);
        if (strncmp(pParam, "].type=", 7) == 0)
        {
            pLayoutOptions[i].type = strtoul(pParam + 7, NULL, 10);
        }
        else if (strncmp(pParam, "].size=", 7) == 0)
        {
            pLayoutOptions[i].arraySize = strtoul(pParam + 7, NULL, 10);
        }
        else if (strncmp(pParam, "].stage=", 7) == 0)
        {
            pLayoutOptions[i].stageMask = strtoul(pParam + 8, NULL, 16);
        }
        if (pLayoutOptions[i].setId > maxSet)
        {
            maxSet = pLayoutOptions[i].setId;
        }
        if (pLayoutOptions[i].bindId + 1 > maxBind[pLayoutOptions[i].setId])
        {
            maxBind[pLayoutOptions[i].setId] = pLayoutOptions[i].bindId + 1;
        }
    }

    g_options.pipelineLayout.num_sets = maxSet + 1;
    for (int i = 0; i < g_options.pipelineLayout.num_sets; ++i)
    {
        int layoutSize = sizeof (struct radv_descriptor_set_layout) +
                         sizeof(struct radv_descriptor_set_binding_layout) * maxBind[i];

        g_options.pipelineLayout.set[i].layout = (struct radv_descriptor_set_layout *)malloc(layoutSize);
        memset(g_options.pipelineLayout.set[i].layout, 0, layoutSize);
        g_options.pipelineLayout.set[i].layout->binding_count = maxBind[i];
        g_options.pipelineLayout.set[i].layout->shader_stages = -1;
    }

    for (int i = 0; i < g_options.layoutCount; ++i)
    {
        if (pLayoutOptions[i].setId >= 0 && pLayoutOptions[i].bindId >= 0)
        {
            struct radv_descriptor_set_layout* pSetLayout = g_options.pipelineLayout.set[pLayoutOptions[i].setId].layout;
            struct radv_descriptor_set_binding_layout* pBindLayout = &pSetLayout->binding[pLayoutOptions[i].bindId];
            if (pLayoutOptions[i].type >= 0)
            {
                pBindLayout->type = (VkDescriptorType)pLayoutOptions[i].type;
            }
            if (pLayoutOptions[i].arraySize >= 0)
            {
                pBindLayout->array_size = pLayoutOptions[i].arraySize;
            }
            if (pLayoutOptions[i].stageMask >= 0)
            {
                pSetLayout->shader_stages = pLayoutOptions[i].stageMask;
            }
        }
    }

    for (int i = 0; i < g_options.pipelineLayout.num_sets; ++i)
    {
        int size = 0;
        struct radv_descriptor_set_layout* pSetLayout = g_options.pipelineLayout.set[i].layout;
        for (int j = 0; j < pSetLayout->binding_count; ++j)
        {
             struct radv_descriptor_set_binding_layout* pBindLayout = &pSetLayout->binding[i];
             pBindLayout->offset = size * 64;
             pBindLayout->buffer_offset = size * 64;
             size += pBindLayout->array_size;
             pBindLayout->size = 64;
        }
        pSetLayout->size = size;
    }
    return &g_options.pipelineLayout;
}

void CompileSource()
{
    g_options.pipelineKey.tess_input_vertices = 3;
    g_options.pipelineKey.col_format = V_028714_SPI_SHADER_32_ABGR;
    g_options.pipelineKey.instance_rate_inputs = 0xffffffff;
 
    for (int stage = 0; stage< MESA_SHADER_COMPUTE + 1; ++stage)
    {
        if (g_options.pGlslName[stage])
        {
            CompileGlsl((gl_shader_stage)stage, g_options.pGlslName[stage]);
        }
        else if (g_options.pSpvasName[stage])
        {
            AsmSpv((gl_shader_stage)stage, g_options.pSpvasName[stage]);
        }
        else if (g_options.pSpvName[stage])
        {
            LoadSpv((gl_shader_stage)stage, g_options.pSpvName[stage]);
        }
      
        if (g_options.sources[stage].dataSize > 0)
        {
            g_options.stages[stage].pName = "main";
            g_options.stages[stage].pSpecializationInfo = NULL;
            g_options.stages[stage].stage = VkShaderStageFlagBits(1 << stage);
            g_options.pStages[stage] = &g_options.stages[stage];
         
            // Disassemble SPIRV code
            uint32_t binSize =  g_options.sources[stage].dataSize;
            uint32_t textSize = binSize * 10 + 1024;
            char* pSpvText = new char[textSize];
            assert(pSpvText != nullptr);
            memset(pSpvText, 0, textSize);
            printf("\nSPIR-V disassembly for %s\n", GetShaderStageName(gl_shader_stage(stage)));
            spvDisassembleSpirv(binSize, g_options.sources[stage].pData, textSize, pSpvText);
            printf(pSpvText);
            printf("\n");
            delete[] pSpvText;
        }
    }
}

void Usage()
{
    printf(
    "RADV Compiler Usage:\n"
    "    compiler.exe [-layout layoutoptions][-gfxip ip][file list]\n"
    "Layout options:\n"
    "    set[N].bind[M].type=0~10            set binding's descriptor type\n"
    "    set[N].bind[M].size=1~              set binding's array size\n"
    "Input file can be SPIRV binary or GLSL source file or PIPE file\n"
    "Example:\n"
    "    compiler.exe 1.vert 1.frag -layout set[0].bind[0].type=1 -layout set[0].bind[0].size=1\n");
}
