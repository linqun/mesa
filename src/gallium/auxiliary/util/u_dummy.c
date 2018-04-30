#include "radv_private.h"
#include "radv_shader.h"
#include "ac_nir_to_llvm.h"

#ifndef  DBG_TEX
/* Debug flags. */
/* logging */
#define DBG_TEX			(1 << 0)
/* gap - reuse */
#define DBG_COMPUTE		(1 << 2)
#define DBG_VM			(1 << 3)
/* gap - reuse */
/* shader logging */
#define DBG_FS			(1 << 5)
#define DBG_VS			(1 << 6)
#define DBG_GS			(1 << 7)
#define DBG_PS			(1 << 8)
#define DBG_CS			(1 << 9)
#define DBG_TCS			(1 << 10)
#define DBG_TES			(1 << 11)
#define DBG_NO_IR		(1 << 12)
#define DBG_NO_TGSI		(1 << 13)
#define DBG_NO_ASM		(1 << 14)
#define DBG_PREOPT_IR		(1 << 15)
#define DBG_CHECK_IR		(1 << 16)
#define DBG_NO_OPT_VARIANT	(1 << 17)
#define DBG_FS_CORRECT_DERIVS_AFTER_KILL (1 << 18)
/* gaps */
#define DBG_TEST_DMA		(1 << 20)
/* Bits 21-31 are reserved for the r600g driver. */
/* features */
#define DBG_NO_ASYNC_DMA	(1ull << 32)
#define DBG_NO_HYPERZ		(1ull << 33)
#define DBG_NO_DISCARD_RANGE	(1ull << 34)
#define DBG_NO_2D_TILING	(1ull << 35)
#define DBG_NO_TILING		(1ull << 36)
#define DBG_SWITCH_ON_EOP	(1ull << 37)
#define DBG_FORCE_DMA		(1ull << 38)
#define DBG_PRECOMPILE		(1ull << 39)
#define DBG_INFO		(1ull << 40)
#define DBG_NO_WC		(1ull << 41)
#define DBG_CHECK_VM		(1ull << 42)
#define DBG_NO_DCC		(1ull << 43)
#define DBG_NO_DCC_CLEAR	(1ull << 44)
#define DBG_NO_RB_PLUS		(1ull << 45)
#define DBG_SI_SCHED		(1ull << 46)
#define DBG_MONOLITHIC_SHADERS	(1ull << 47)
#define DBG_NO_CE		(1ull << 48)
#define DBG_UNSAFE_MATH		(1ull << 49)
#define DBG_NO_DCC_FB		(1ull << 50)
#define DBG_TEST_VMFAULT_CP	(1ull << 51)
#define DBG_TEST_VMFAULT_SDMA	(1ull << 52)
#define DBG_TEST_VMFAULT_SHADER	(1ull << 53)
#endif

void _mesa_log(const char *fmtString, ...){ }

FILE * _mesa_get_log_file(void){ return NULL; }

const char * os_get_option(const char *name){ return ""; }

void * debug_malloc(
    const char *file,
    unsigned line,
    const char *function,
    size_t size)
{
    return malloc(size);
}

void * debug_calloc(
    const char *file,
    unsigned line,
    const char *function,
    size_t count,
    size_t size )
{
    return calloc(count, size);
}

void debug_free(
    const char *file,
    unsigned line,
   const char *function,
    void *ptr)
{
    free(ptr);
}

void * debug_realloc(
    const char *file,
    unsigned line,
    const char *function,
    void *old_ptr,
    size_t old_size,
    size_t new_size )
{
    return realloc(old_ptr, new_size);
}


uint64_t debug_get_flags_option(
    const char *name,
    const struct debug_named_value *flags,
    uint64_t dfault)
{
    if (strcmp(name, "R600_DEBUG") == 0)
    {
        return (uint64_t)(DBG_FS | DBG_VS | DBG_PS | DBG_TES | DBG_GS | DBG_TCS | DBG_CS| DBG_PRECOMPILE);
    }
    else
    {
        return dfault;
    }
}

int64_t os_time_get_nano(void)
{
    static int64_t ss = 0;
    return ss++;
}

int64_t os_time_get_absolute_timeout(uint64_t timeout){ return 0; }

VkResult __vk_errorf(VkResult error, const char *file, int line, const char *format, ...) { return VK_SUCCESS;}

void __radv_finishme(const char *file, int line, const char *format, ...) { }

unsigned radv_cayman_get_maxdist(int log_samples) { return 0;}

uint32_t radv_translate_buffer_dataformat(
    const struct vk_format_description *desc,
    int first_non_void)
{
    return 0;
}

uint32_t radv_translate_buffer_numformat(
    const struct vk_format_description *desc,
    int first_non_void)
{
    return 0;
}

uint32_t radv_translate_colorformat(VkFormat format)
{
    return 0;
}

uint32_t radv_translate_color_numformat(
    VkFormat format,
    const struct vk_format_description *desc,
    int first_non_void)
{
    return 0;
}

uint32_t radv_colorformat_endian_swap(uint32_t colorformat) { return 0; }

unsigned radv_translate_colorswap(VkFormat format, bool do_endian_swap) { return 0;}

const struct vk_format_description *vk_format_description(VkFormat format) { return NULL;}

uint32_t __sync_fetch_and_sub(uint32_t* p, uint32_t a) { *p -= a; return *p;}

uint32_t __builtin_popcount(uint32_t a)
{
    uint32_t c = 0;
    for (int i = 0; i < 32; ++i)
    {
        if (a & (1 << i))
        {
            ++c;
        }
    }
    return c;
}

struct radv_userdata_info *radv_lookup_user_sgpr(
    struct radv_pipeline *pipeline,
    gl_shader_stage stage,
    int idx)
{
   return &pipeline->shaders[stage]->info.user_sgprs_locs.shader_data[idx];
}

void os_log_message(const char *message) { }

void radv_hash_shaders(
    unsigned char *hash,
    const VkPipelineShaderStageCreateInfo **stages,
    const struct radv_pipeline_layout *layout,
    const struct radv_pipeline_key *key,
    uint32_t flags)
{
}

bool radv_create_shader_variants_from_pipeline_cache(
    struct radv_device *device,
    struct radv_pipeline_cache *cache,
    const unsigned char *sha1,
    struct radv_shader_variant **variants)
{
    return false;
}

void radv_pipeline_cache_insert_shaders(
    struct radv_device *device,
    struct radv_pipeline_cache *cache,
    const unsigned char *sha1,
    struct radv_shader_variant **variants,
    const void *const *codes,
    const unsigned *code_sizes)
{
}
