#include <getopt.h>
#include <vulkan/vulkan.h>
#include "radv_private.h"
#include "radv_shader.h"
#include "compiler_option.h"

const struct radv_dynamic_state default_dynamic_state;
void radv_create_shaders(struct radv_pipeline *pipeline,
                         struct radv_device *device,
                         struct radv_pipeline_cache *cache,
                         struct radv_pipeline_key key,
                         const VkPipelineShaderStageCreateInfo **pStages);
struct radv_instance g_instance = { 0 };
struct radv_pipeline g_pipeline = { 0 };
struct radv_device g_device = { 0 };

int main(int argc, char* const* argv)
{
    uint32_t stageMask = 0;
    Init();

    // Initialize instance and device
    g_instance.physicalDeviceCount = 1;
    g_instance.physicalDevices[0].rad_info.family = CHIP_TONGA;
    g_instance.physicalDevices[0].rad_info.chip_class = VI;

    g_device.instance = &g_instance;
    g_device.physical_device = &g_instance.physicalDevices[0];
    g_device.instance->debug_flags |= RADV_DEBUG_DUMP_SHADERS;

    g_pipeline.device = &g_device;

    // Parse command options
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-layout") == 0)
        {
            g_options.pLayoutList[g_options.layoutCount++] = argv[i + 1];
            ++i;
        }
        else if (strcmp(argv[i], "-gfxip") == 0)
        {
            uint32_t ip = atoi(argv[i + 1]);
            switch (ip)
            {
            case 6:
                g_instance.physicalDevices[0].rad_info.family = CHIP_TAHITI;
                g_instance.physicalDevices[0].rad_info.chip_class = SI;
                break;
            case 7:
                g_instance.physicalDevices[0].rad_info.family = CHIP_BONAIRE;
                g_instance.physicalDevices[0].rad_info.chip_class = CIK;
                break;
            case 8:
                g_instance.physicalDevices[0].rad_info.family = CHIP_FIJI;
                g_instance.physicalDevices[0].rad_info.chip_class = VI;
                break;
            case 9:
                g_instance.physicalDevices[0].rad_info.family = CHIP_VEGA10;
                g_instance.physicalDevices[0].rad_info.chip_class = GFX9;
                break;
             default:
                assert(0);
                break;
            }
            ++i;
        }
        else if (argv[i][0] == '-')
        {
           // Unknown options
           Usage();
           return 0;
        }
        else
        {
            // source files
            const char* pFileExt = strrchr(argv[i], '.');
            if (pFileExt == NULL)
            {
               printf("Unsupported file extensions!");
               return;
            }
            else if (strcmp(pFileExt, ".vert") == 0)
            {
               g_options.pGlslName[MESA_SHADER_VERTEX] = argv[i];
            }
            else if (strcmp(pFileExt, ".tesc") == 0)
            {
               g_options.pGlslName[MESA_SHADER_TESS_CTRL] = argv[i];
            }
            else if (strcmp(pFileExt, ".tese") == 0)
            {
               g_options.pGlslName[MESA_SHADER_TESS_EVAL] = argv[i];
            }
            else if (strcmp(pFileExt, ".geom") == 0)
            {
               g_options.pGlslName[MESA_SHADER_GEOMETRY] = argv[i];
            }
            else if (strcmp(pFileExt, ".frag") == 0)
            {
               g_options.pGlslName[MESA_SHADER_FRAGMENT] = argv[i];
            }
            else if (strcmp(pFileExt, ".comp") == 0)
            {
               g_options.pGlslName[MESA_SHADER_COMPUTE] = argv[i];
            }
            else if (strcmp(pFileExt, ".spv") == 0)
            {
               g_options.pSpvName[g_options.spvCount++] = argv[i];
            }
            else if (strcmp(pFileExt, ".spvas") == 0)
            {
               g_options.pSpvasName[g_options.spvasCount++] = argv[i];
            }
            else if (strcmp(pFileExt, ".pipe") == 0)
            {
               g_options.pPipeName = argv[i];
            }
            else
            {
               printf("Unsupported file extensions!");
               return;
            }
        }
    }

    if (g_options.pPipeName != NULL)
    {
        ParsePipeFile();
    }
    else
    {
        CompileSource();
        ParseLayout();
    }

    for (int i = 0; i< MESA_SHADER_COMPUTE + 1; ++i)
    {
        if (g_options.sources[i].dataSize)
        {
            struct radv_shader_module* pModule = NULL;
            pModule = (struct radv_shader_module*) malloc(sizeof(struct radv_shader_module) +
                                                 g_options.sources[i].dataSize);
            pModule->nir = NULL;
            pModule->size = g_options.sources[i].dataSize;
            memcpy(pModule->data, g_options.sources[i].pData, pModule->size);
            g_options.stages[i].module = radv_shader_module_to_handle(pModule);
        }
    }

    struct radv_pipeline_key pipelineKey = { 0 };
    pipelineKey.instance_rate_inputs      = g_options.pipelineKey.instance_rate_inputs;
    pipelineKey.tess_input_vertices       = g_options.pipelineKey.tess_input_vertices;
    pipelineKey.col_format                = g_options.pipelineKey.col_format;
    pipelineKey.log2_ps_iter_samples      = g_options.pipelineKey.log2_ps_iter_samples;
    pipelineKey.log2_num_samples          = g_options.pipelineKey.log2_num_samples;
    pipelineKey.multisample               = g_options.pipelineKey.multisample;
    pipelineKey.has_multiview_view_index  = g_options.pipelineKey.has_multiview_view_index;
    memcpy(pipelineKey.instance_rate_divisors,
           g_options.pipelineKey.instance_rate_divisors,
           sizeof(g_options.pipelineKey.instance_rate_divisors));
    g_pipeline.layout = &g_options.pipelineLayout;
    radv_create_shaders(&g_pipeline, &g_device, NULL, pipelineKey, g_options.pStages);
}
