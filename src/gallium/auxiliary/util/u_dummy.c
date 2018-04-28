#include "radv_private.h"
#include "radv_shader.h"
#include "ac_nir_to_llvm.h"
#include "util/u_debug.h"
#include "util/u_format.h"
#include "cso_cache/cso_hash.h"
//#include "radeon\r600_pipe_common.h"

void _debug_vprintf(const char *format, va_list ap)
{
    vprintf(format, ap);
}

const struct util_format_description *
util_format_description(enum pipe_format format)
{
    return NULL;
}

boolean
debug_get_bool_option(const char *name, boolean dfault)
{
    return  dfault;
}

long
debug_get_num_option(const char *name, long dfault)
{
    return dfault;
}

int64_t
os_time_get_nano(void)
{
    static int64_t ss = 0;
    return ss++;
}


struct cso_hash *cso_hash_create(void)
{
    return NULL;
}
void             cso_hash_delete(struct cso_hash *hash)
{
    return ;
}


//int              cso_hash_size(struct cso_hash *hash)


/**
 * Adds a data with the given key to the hash. If entry with the given
 * key is already in the hash, this current entry is instered before it
 * in the collision list.
 * Function returns iterator pointing to the inserted item in the hash.
 */
struct cso_hash_iter cso_hash_insert(struct cso_hash *hash, unsigned key,
                                     void *data)
{
    return (struct cso_hash_iter){0};
}
/**
 * Removes the item pointed to by the current iterator from the hash.
 * Note that the data itself is not erased and if it was a malloc'ed pointer
 * it will have to be freed after calling this function by the callee.
 * Function returns iterator pointing to the item after the removed one in
 * the hash.
 */
struct cso_hash_iter cso_hash_erase(struct cso_hash *hash, struct cso_hash_iter iter)
{
    return (struct cso_hash_iter){0};
}

void  *cso_hash_take(struct cso_hash *hash, unsigned key)
{
    return NULL;
}


struct cso_hash_iter cso_hash_first_node(struct cso_hash *hash)
{
return (struct cso_hash_iter){0};
}

/**
 * Return an iterator pointing to the first entry in the collision list.
 */
struct cso_hash_iter cso_hash_find(struct cso_hash *hash, unsigned key)
{
return (struct cso_hash_iter){0};
}

/**
 * Returns true if a value with the given key exists in the hash
 */
boolean   cso_hash_contains(struct cso_hash *hash, unsigned key)
{
    return false;
}

#if 0
int       cso_hash_iter_is_null(struct cso_hash_iter iter)
{
    return 1;
}
unsigned  cso_hash_iter_key(struct cso_hash_iter iter)
{
    return 0;
}
void     *cso_hash_iter_data(struct cso_hash_iter iter)
{
return NULL;
}
#endif

struct cso_hash_iter cso_hash_iter_next(struct cso_hash_iter iter)
{
return (struct cso_hash_iter){0};
}
struct cso_hash_iter cso_hash_iter_prev(struct cso_hash_iter iter)
{
return (struct cso_hash_iter){0};
}



void cso_delete_fragment_shader(struct cso_context *ctx, void *handle ) {}

void cso_delete_vertex_shader(struct cso_context *ctx, void *handle ) {}


void cso_delete_geometry_shader(struct cso_context *ctx, void *handle) {}

void cso_delete_tessctrl_shader(struct cso_context *ctx, void *handle) {}


void cso_delete_tesseval_shader(struct cso_context *ctx, void *handle) {}

void cso_delete_compute_shader(struct cso_context *ctx, void *handle) {}

/**
 * Convenience routine to iterate over the collision list while doing a memory
 * comparison to see which entry in the list is a direct copy of our template
 * and returns that entry.
 */
void *cso_hash_find_data_from_template( struct cso_hash *hash,
				        unsigned hash_key,
				        void *templ,
				        int size )
{
    return NULL;
}

void
util_copy_rect(ubyte * dst, enum pipe_format format,
               unsigned dst_stride, unsigned dst_x, unsigned dst_y,
               unsigned width, unsigned height, const ubyte * src,
               int src_stride, unsigned src_x, unsigned src_y)
{
    return;
}

boolean util_format_s3tc_enabled = false;

void
_pipe_debug_message(
   struct pipe_debug_callback *cb,
   unsigned *id,
   enum pipe_debug_type type,
   const char *fmt, ...)
{
    return;
}

void debug_describe_reference(char* buf, const struct pipe_reference*ptr)
{
}
void debug_describe_resource(char* buf, const struct pipe_resource *ptr)
{
}
void debug_describe_surface(char* buf, const struct pipe_surface *ptr)
{
}
void debug_describe_sampler_view(char* buf, const struct pipe_sampler_view *ptr)
{
}
void debug_describe_image_view(char* buf, const struct pipe_image_view *ptr)
{
}
void debug_describe_so_target(char* buf,
                              const struct pipe_stream_output_target *ptr)
                              {
                              }

//void radeon_elf_read(const char *elf_data, unsigned elf_size,
//		     struct radeon_shader_binary *binary)
//{
//}

/**
 * @returns A pointer to the start of the configuration information for
 * the function starting at \p symbol_offset of the binary.
 */
//const unsigned char *radeon_shader_binary_config_start(
//	const struct radeon_shader_binary *binary,
//	uint64_t symbol_offset)
//    {
        //static struct radeon_shader_binary dummy = {0};
//        return  (const unsigned char*)binary;
//    }
bool si_replace_shader(unsigned num, struct radeon_shader_binary *binary)
{
    return false;
}


void si_pm4_cmd_begin(struct si_pm4_state *state, unsigned opcode)
{
}
void si_pm4_cmd_add(struct si_pm4_state *state, uint32_t dw)
{
}
void si_pm4_cmd_end(struct si_pm4_state *state, bool predicate)
{
}

void si_pm4_set_reg(struct si_pm4_state *state, unsigned reg, uint32_t val)
{
}
void si_pm4_add_bo(struct si_pm4_state *state,
		   struct r600_resource *bo,
		   enum radeon_bo_usage usage,
		   enum radeon_bo_priority priority)
{
}
void si_pm4_upload_indirect_buffer(struct si_context *sctx,
				   struct si_pm4_state *state)
{
}

void si_pm4_free_state_simple(struct si_pm4_state *state)
{
}
void si_pm4_free_state(struct si_context *sctx,
		       struct si_pm4_state *state,
		       unsigned idx)
{
}

void si_pm4_emit(struct si_context *sctx, struct si_pm4_state *state){}
void si_pm4_emit_dirty(struct si_context *sctx){}
void si_pm4_reset_emitted(struct si_context *sctx){}

void si_set_ring_buffer(struct pipe_context *ctx, uint shader, uint slot,
			struct pipe_resource *buffer,
			unsigned stride, unsigned num_records,
			bool add_tid, bool swizzle,
			unsigned element_size, unsigned index_stride, uint64_t offset){}
void si_shader_change_notify(struct si_context *sctx){};

void si_init_atom(struct si_context *sctx, struct r600_atom *atom,
		  struct r600_atom **list_elem,
		  void (*emit_func)(struct si_context *ctx, struct r600_atom *state)){};

void si_context_gfx_flush(void *context, unsigned flags,
			  struct pipe_fence_handle **fence){}

void
util_unreference_framebuffer_state(struct pipe_framebuffer_state *fb){}
struct blitter_context *util_blitter_create(struct pipe_context *pipe) { return NULL;}
void util_blitter_destroy(struct blitter_context *blitter) {}
//void r600_draw_rectangle(struct blitter_context *blitter,
//			 int x1, int y1, int x2, int y2, float depth,
//			 enum blitter_attrib_type type,
//			 const union pipe_color_union *attrib) {}
//bool r600_common_screen_init(struct r600_common_screen *rscreen,
//			     struct radeon_winsys *ws) { return true;}
//void r600_destroy_common_screen(struct r600_common_screen *rscreen) {}
//bool r600_common_context_init(struct r600_common_context *rctx,
//			      struct r600_common_screen *rscreen) { return true;}
//                  void r600_common_context_cleanup(struct r600_common_context *rctx) { return true;}
//struct pipe_resource *r600_resource_create_common(struct pipe_screen *screen,
//						  const struct pipe_resource *templ)
//                          {
//    return NULL;
//                          }
struct pipe_resource * r600_aligned_buffer_create(struct pipe_screen *screen,
						  unsigned flags,
						  unsigned usage,
						  unsigned size,
						  unsigned alignment)
{
   return NULL;
}
void r600_replace_buffer_storage(struct pipe_context *ctx,
				 struct pipe_resource *dst,
				 struct pipe_resource *src)
{
}
void r600_query_init_backend_mask(struct r600_common_context *ctx) {}
struct pipe_resource *r600_buffer_create(struct pipe_screen *screen,
					 const struct pipe_resource *templ,
					 unsigned alignment) { return NULL; }

struct pipe_resource *
r600_buffer_from_user_memory(struct pipe_screen *screen,
			     const struct pipe_resource *templ,
			     void *user_memory) { return NULL;}
void
r600_invalidate_resource(struct pipe_context *ctx,
			 struct pipe_resource *resource)
                         {
                         }
void si_init_all_descriptors(struct si_context *sctx) {}
void si_release_all_descriptors(struct si_context *sctx) {}
boolean si_is_format_supported(struct pipe_screen *screen,
                               enum pipe_format format,
                               enum pipe_texture_target target,
                               unsigned sample_count,
                               unsigned usage) { return true;}
void si_init_state_functions(struct si_context *sctx) {}
void si_init_blit_functions(struct si_context *sctx) {}
void si_init_cp_dma_functions(struct si_context *sctx) {}
void si_init_debug_functions(struct si_context *sctx) {}
void si_begin_new_cs(struct si_context *ctx) {}
void si_init_compute_functions(struct si_context *sctx) {}
void si_init_perfcounters(struct si_screen *screen) {}
void si_init_screen_state_functions(struct si_screen *sscreen) {}
struct pipe_video_codec *si_uvd_create_decoder(struct pipe_context *context,
					       const struct pipe_video_codec *templ) { return NULL;}

struct pipe_video_buffer *si_video_buffer_create(struct pipe_context *pipe,
						 const struct pipe_video_buffer *tmpl)  { return NULL;}

struct pipe_video_buffer *vl_video_buffer_create(struct pipe_context *pipe,
						 const struct pipe_video_buffer *tmpl)  { return NULL;}
                         struct pipe_video_codec *
vl_create_decoder(struct pipe_context *pipe,
                  const struct pipe_video_codec *templat) { return NULL;}
void cik_init_sdma_functions(struct si_context *sctx) {}
void si_init_dma_functions(struct si_context *sctx) {}
#include "main/compiler.h"
#include "main/mtypes.h"
#include "stdio.h"

#ifdef __cplusplus
extern "C" {
#endif
#if 0
struct gl_program *
_mesa_init_gl_program(struct gl_program *prog, GLenum target, GLuint id)
{
    return NULL;
}

void
_mesa_delete_program(struct gl_context *ctx, struct gl_program *prog)
{
}

void
st_release_vp_variants( struct st_context *st,
                        struct st_vertex_program *stvp )
{}
void
st_release_fp_variants( struct st_context *st,
                        struct st_fragment_program *stfp )
{
}

void
st_release_cp_variants(struct st_context *st,
                        struct st_compute_program *stcp)
{
}

void
st_release_basic_variants(struct st_context *st, GLenum target,
                          struct st_basic_variant **variants,
                          struct pipe_shader_state *tgsi)
{
}

void
st_destroy_program_variants(struct st_context *st)
{
}

bool
st_translate_vertex_program(struct st_context *st,
                            struct st_vertex_program *stvp)
{
    return true;
}

bool
st_translate_fragment_program(struct st_context *st,
                              struct st_fragment_program *stfp)
{
    return true;
}

bool
st_translate_geometry_program(struct st_context *st,
                              struct st_geometry_program *stgp)
{
    return true;
}
bool
st_translate_tessctrl_program(struct st_context *st,
                              struct st_tessctrl_program *sttcp)
{
    return true;
}
bool
st_translate_tesseval_program(struct st_context *st,
                              struct st_tesseval_program *sttep)
{
    return true;
}
bool
st_translate_compute_program(struct st_context *st,
                             struct st_compute_program *stcp)
{
    return true;
}
void
st_print_current_vertex_program(void)
{
}
void
st_precompile_shader_variant(struct st_context *st,
                             struct gl_program *prog)
{
}
#endif

void
_mesa_log(const char *fmtString, ...)
{
}
FILE *
_mesa_get_log_file(void)
{
return NULL;
}

void
_mesa_generate_parameters_list_for_uniforms(struct gl_shader_program
					    *shader_program,
					    struct gl_shader *sh,
					    struct gl_program_parameter_list
					    *params)
{
}

void
_mesa_associate_uniform_storage(struct gl_context *ctx,
				struct gl_shader_program *shader_program,
				struct gl_program_parameter_list *params)
{
}

#include "program/prog_parameter.h"
struct gl_program_parameter_list *
_mesa_new_parameter_list(void)
{
    struct gl_program_parameter_list* p = malloc(sizeof(struct gl_program_parameter_list));
    memset(p, 0, sizeof(struct gl_program_parameter_list));
    return p;
}
void
_mesa_reserve_parameter_storage(struct gl_program_parameter_list *paramList,
                                unsigned reserve_slots)
{
}
typedef union gl_constant_value gl_constant_value;
GLint
_mesa_add_typed_unnamed_constant(struct gl_program_parameter_list *paramList,
                           const gl_constant_value values[4], GLuint size,
                           GLenum datatype, GLuint *swizzleOut)
{
    return 0;
}

#include "program/prog_statevars.h"
GLint
_mesa_add_state_reference(struct gl_program_parameter_list *paramList,
                          const gl_state_index stateTokens[STATE_LENGTH])
{
    return 0;
}

void
_mesa_update_shader_textures_used(struct gl_shader_program *shProg,
				  struct gl_program *prog)
{
}

void
_mesa_copy_linked_program_data(gl_shader_stage type,
                               const struct gl_shader_program *src,
                               struct gl_program *dst)
                               {
                               }
mesa_format
_mesa_get_shader_image_format(GLenum format)
{
    return MESA_FORMAT_NONE;
}

const char *
os_get_option(const char *name)
{
    return "";
}
//void
//_mesa_reference_program_(struct gl_context *ctx,
//                         struct gl_program **ptr,
//                         struct gl_program *prog)
//                         {
 //                        }
enum pipe_format
st_mesa_format_to_pipe_format(struct st_context *st, mesa_format mesaFormat)
{
    return PIPE_FORMAT_NONE;
}
 //GLuint
//_mesa_num_inst_src_regs(enum prog_opcode opcode)
//{
//     return 0;
//}

//GLuint
//_mesa_num_inst_dst_regs(enum prog_opcode opcode)
//{
//    return 0;
//}

void
_mesa_problem( const struct gl_context *ctx, const char *fmtString, ... )
{
}
void
_mesa_HashWalk(const struct _mesa_HashTable *table,
               void (*callback)(GLuint key, void *data, void *userData),
               void *userData)
{
}
void *_mesa_HashLookup(struct _mesa_HashTable *table, GLuint key) { return NULL;}

void *_mesa_HashLookupLocked(struct _mesa_HashTable *table, GLuint key) { return NULL;}
struct gl_program_cache *
_mesa_new_program_cache(void) {return NULL;}
void
_mesa_delete_program_cache(struct gl_context *ctx, struct gl_program_cache *pc) {}
void
_mesa_delete_shader_cache(struct gl_context *ctx,
			  struct gl_program_cache *cache) {}
              void
_mesa_free_parameter_list(struct gl_program_parameter_list *paramList){}
void
_mesa_error( struct gl_context *ctx, GLenum error, const char *fmtString, ... ) {}
void
_mesa_load_state_parameters(struct gl_context *ctx,
                            struct gl_program_parameter_list *paramList) {}
bool
st_load_tgsi_from_disk_cache(struct gl_context *ctx,
                             struct gl_shader_program *prog)
{
   return false;
}
void
st_store_tgsi_in_disk_cache(struct st_context *st, struct gl_program *prog,
                            struct pipe_shader_state *out_state,
                            unsigned num_tokens) {}
//char *
//_mesa_program_state_string(const gl_state_index state[STATE_LENGTH]) { return "";}
const struct tgsi_token *
st_get_bitmap_shader(const struct tgsi_token *tokens,
                     unsigned sampler_index,
                     bool use_texcoord, bool swizzle_xxxx)
                     {
                     return NULL;
                     }
extern const struct tgsi_token *
st_get_drawpix_shader(const struct tgsi_token *tokens, bool use_texcoord,
                      bool scale_and_bias, unsigned scale_const,
                      unsigned bias_const, bool pixel_maps,
                      unsigned drawpix_sampler, unsigned pixelmap_sampler,
                      unsigned texcoord_const) { return NULL;}

                      void
st_init_atifs_prog(struct gl_context *ctx, struct gl_program *prog) {}
enum pipe_error
st_translate_atifs_program(
    struct ureg_program *ureg,
    struct ati_fragment_shader *atifs,
    struct gl_program *program,
    GLuint numInputs,
    const GLuint inputMapping[],
    const ubyte inputSemanticName[],
    const ubyte inputSemanticIndex[],
    const GLuint interpMode[],
    GLuint numOutputs,
    const GLuint outputMapping[],
    const ubyte outputSemanticName[],
    const ubyte outputSemanticIndex[]) { return PIPE_OK;}
const struct tgsi_token *
st_fixup_atifs(const struct tgsi_token *tokens,
               const struct st_fp_variant_key *key) { return NULL;}
void draw_delete_vertex_shader(struct draw_context *draw,
                               struct draw_vertex_shader *dvs){}
void* _glapi_get_context() { return _glapi_Context; }
 void *_glapi_Context = NULL;

 void _debug_assert_fail(const char *expr, 
                        const char *file, 
                        unsigned line, 
                        const char *function){}
#include "u_debug.h"
#include "u_debug_refcnt.h"
void *
debug_malloc(const char *file, unsigned line, const char *function,
             size_t size)
             {
    return malloc(size);
             }

void *
debug_calloc(const char *file, unsigned line, const char *function,
             size_t count, size_t size )
             {
    return calloc(count, size);
             }

void
debug_free(const char *file, unsigned line, const char *function,
           void *ptr)
           {
    free(ptr);
           }

void *
debug_realloc(const char *file, unsigned line, const char *function,
              void *old_ptr, size_t old_size, size_t new_size )
              {
              return realloc(old_ptr, new_size);
              }

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

uint64_t
debug_get_flags_option(const char *name, 
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

void debug_reference_slowpath(const struct pipe_reference* p, debug_reference_descriptor get_desc, int change)
{
    return;
}
int debug_refcnt_state = -1;
int  ST_DEBUG = -1;

   uint32_t key_dummy_hash_function(const void *key) { return 0;}
   bool key_dummy_equals_function(const void *a, const void *b) { return false;}


//struct pipe_resource *dummy_resource_create(struct pipe_screen *screen,
//						  const struct pipe_resource *templ)
//{
//    static struct r600_resource dummy = {0};
//    return &dummy.b.b;
//}

const char *
debug_get_option(const char *name, const char *dfault)
{
    return dfault;
}
struct u_suballocator *
u_suballocator_create(struct pipe_context *pipe, unsigned size, unsigned bind,
                      enum pipe_resource_usage usage,
		      boolean zero_buffer_memory){ return (struct u_suballocator *)4;}

void
u_suballocator_destroy(struct u_suballocator *allocator) {}

void
u_suballocator_alloc(struct u_suballocator *allocator, unsigned size,
                     unsigned alignment, unsigned *out_offset,
                     struct pipe_resource **outbuf) {}
void r600_test_dma(struct r600_common_screen *rscreen) {}
void si_set_rw_buffer(struct si_context *sctx,
		      uint slot, const struct pipe_constant_buffer *input) {}


void r600_update_vs_writes_viewport_index(struct r600_common_context *rctx,
					  struct tgsi_shader_info *info){}
                      void util_blitter_draw_rectangle(struct blitter_context *blitter,
                                 int x1, int y1, int x2, int y2, float depth,
                                 enum blitter_attrib_type type,
                                 const union pipe_color_union *attrib){}

void
util_copy_box(ubyte * dst,
              enum pipe_format format,
              unsigned dst_stride, unsigned dst_slice_stride,
              unsigned dst_x, unsigned dst_y, unsigned dst_z,
              unsigned width, unsigned height, unsigned depth,
              const ubyte * src,
              int src_stride, unsigned src_slice_stride,
              unsigned src_x, unsigned src_y, unsigned src_z) {}
             // void r600_buffer_subdata(struct pipe_context *ctx,
		//	 struct pipe_resource *buffer,
		//	 unsigned usage, unsigned offset,
		//	 unsigned size, const void *data) {}
//struct pipe_resource *r600_buffer_create(struct pipe_screen *screen,
					 //const struct pipe_resource *templ,
//					 unsigned alignment) { return NULL;}
boolean rvid_is_format_supported(struct pipe_screen *screen,
                                 enum pipe_format format,
                                 enum pipe_video_profile profile,
                                 enum pipe_video_entrypoint entrypoint) { return false;}
                                 int rvid_get_video_param(struct pipe_screen *screen,
                         enum pipe_video_profile profile,
                         enum pipe_video_entrypoint entrypoint,
                         enum pipe_video_cap param) { return 0;}
boolean
vl_video_buffer_is_format_supported(struct pipe_screen *screen,
                                    enum pipe_format format,
                                    enum pipe_video_profile profile,
                                    enum pipe_video_entrypoint entrypoint) { return false;}
unsigned
vl_video_buffer_max_size(struct pipe_screen *screen) { return 0;}
int
vl_level_supported(struct pipe_screen *screen, enum pipe_video_profile profile) { return 0;}
bool
vl_profile_supported(struct pipe_screen *screen, enum pipe_video_profile profile,
                     enum pipe_video_entrypoint entrypoint) { return false;}
int64_t
os_time_get_absolute_timeout(uint64_t timeout) { return 0;}
//struct pipe_resource *
//r600_buffer_from_user_memory(struct pipe_screen *screen,
//			     const struct pipe_resource *templ,
//			     void *user_memory) { return NULL;}
//void
//r600_invalidate_resource(struct pipe_context *ctx,
			 //struct pipe_resource *resource) {}
void r600_gpu_load_kill_thread(struct r600_common_screen *rscreen){}
void r600_perfcounters_destroy(struct r600_common_screen *rscreen){}
void r600_init_screen_query_functions(struct r600_common_screen *rscreen){}
void r600_query_init(struct r600_common_context *rctx){}
void r600_suspend_queries(struct r600_common_context *ctx){}
void r600_resume_queries(struct r600_common_context *ctx){}
void r600_streamout_buffers_dirty(struct r600_common_context *rctx) {}
void r600_emit_streamout_end(struct r600_common_context *rctx) {}
void r600_streamout_init(struct r600_common_context *rctx) {}
struct pipe_resource *r600_texture_create(struct pipe_screen *screen,
					const struct pipe_resource *templ) { return NULL;}
void r600_init_screen_texture_functions(struct r600_common_screen *rscreen){}
void r600_init_context_texture_functions(struct r600_common_context *rctx){}
void r600_init_viewport_functions(struct r600_common_context *rctx) {}
void cayman_init_msaa(struct pipe_context *ctx) {}
void 
util_draw_vertex_buffer(struct pipe_context *pipe, struct cso_context *cso,
                        struct pipe_resource *vbuf, uint vbuf_slot,
                        uint offset, uint prim_type, uint num_attribs,
                        uint num_verts) {}
void
util_format_s3tc_init(void) {}
struct u_upload_mgr *
u_upload_create(struct pipe_context *pipe, unsigned default_size,
                unsigned bind, enum pipe_resource_usage usage) { return (struct u_upload_mgr *)4;}

/**
 * Destroy the upload manager.
 */
void u_upload_destroy( struct u_upload_mgr *upload ) {}
void u_upload_alloc(struct u_upload_mgr *upload,
                    unsigned min_out_offset,
                    unsigned size,
                    unsigned alignment,
                    unsigned *out_offset,
                    struct pipe_resource **outbuf,
                    void **ptr) {}

VkResult __vk_errorf(VkResult error, const char *file, int line, const char *format, ...) { return VK_SUCCESS;}
void __radv_finishme(const char *file, int line, const char *format, ...) {}
unsigned radv_cayman_get_maxdist(int log_samples) { return 0;}

uint32_t radv_translate_buffer_dataformat(const struct vk_format_description *desc,
					  int first_non_void) { return 0;}
uint32_t radv_translate_buffer_numformat(const struct vk_format_description *desc,
					 int first_non_void) { return 0;}
uint32_t radv_translate_colorformat(VkFormat format) { return 0;}
uint32_t radv_translate_color_numformat(VkFormat format,
					const struct vk_format_description *desc,
					int first_non_void) { return 0;}
uint32_t radv_colorformat_endian_swap(uint32_t colorformat) { return 0;}
unsigned radv_translate_colorswap(VkFormat format, bool do_endian_swap) { return 0;}
const struct vk_format_description *vk_format_description(VkFormat format) { return NULL;}

void si_init_ia_multi_vgt_param_table(struct si_context *sctx) {};
void si_pm4_clear_state(struct si_pm4_state *state)
{
}

int asprintf(char** outbuf, const char* fmt, ...)
{
   return 0;
}
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
#ifdef __cplusplus
}
#endif

#include "sid.h"

uint32_t
radv_shader_stage_to_user_data_0(gl_shader_stage stage, bool has_gs, bool has_tess)
{
	switch (stage) {
	case MESA_SHADER_FRAGMENT:
		return R_00B030_SPI_SHADER_USER_DATA_PS_0;
	case MESA_SHADER_VERTEX:
		if (has_tess)
			return R_00B530_SPI_SHADER_USER_DATA_LS_0;
		else
			return has_gs ? R_00B330_SPI_SHADER_USER_DATA_ES_0 : R_00B130_SPI_SHADER_USER_DATA_VS_0;
	case MESA_SHADER_GEOMETRY:
		return R_00B230_SPI_SHADER_USER_DATA_GS_0;
	case MESA_SHADER_COMPUTE:
		return R_00B900_COMPUTE_USER_DATA_0;
	case MESA_SHADER_TESS_CTRL:
		return R_00B430_SPI_SHADER_USER_DATA_HS_0;
	case MESA_SHADER_TESS_EVAL:
		if (has_gs)
			return R_00B330_SPI_SHADER_USER_DATA_ES_0;
		else
			return R_00B130_SPI_SHADER_USER_DATA_VS_0;
	default:
		unreachable("unknown shader");
	}
}

struct radv_userdata_info *radv_lookup_user_sgpr(struct radv_pipeline *pipeline,
						 gl_shader_stage stage,
						 int idx)
{
	return &pipeline->shaders[stage]->info.user_sgprs_locs.shader_data[idx];
}

#include "u_threaded_context.h"

struct pipe_context *
threaded_context_create(struct pipe_context *pipe,
                        struct slab_parent_pool *parent_transfer_pool,
                        tc_replace_buffer_storage_func replace_buffer,
                        struct threaded_context **out)
{
   return NULL;
}
void threaded_resource_init(struct pipe_resource *res) {}
void threaded_resource_deinit(struct pipe_resource *res) {}
struct pipe_context *threaded_context_unwrap_sync(struct pipe_context *pipe) { return NULL;}

void si_copy_buffer(struct si_context *sctx,
		    struct pipe_resource *dst, struct pipe_resource *src,
		    uint64_t dst_offset, uint64_t src_offset, unsigned size,
		    unsigned user_flags) {}
void util_test_constant_buffer(struct pipe_context *ctx,
                               struct pipe_resource *constbuf) {}
void si_set_active_descriptors_for_shader(struct si_context *sctx,
					  struct si_shader_selector *sel) {}

#include "pipebuffer/pb_slab.h"
bool
pb_slabs_init(struct pb_slabs *slabs,
              unsigned min_order, unsigned max_order,
              unsigned num_heaps,
              void *priv,
              slab_can_reclaim_fn *can_reclaim,
              slab_alloc_fn *slab_alloc,
              slab_free_fn *slab_free)
{ return true; }

void
pb_slabs_deinit(struct pb_slabs *slabs)
{

}

bool si_bindless_descriptor_can_reclaim_slab(void *priv,
					     struct pb_slab_entry *entry)
{
   return true;
}
struct pb_slab *si_bindless_descriptor_slab_alloc(void *priv, unsigned heap,
						  unsigned entry_size,
						  unsigned group_index)
{
   return NULL;
}
void si_bindless_descriptor_slab_free(void *priv, struct pb_slab *pslab)
{
   return;
}
void
os_log_message(const char *message) { }

void
radv_hash_shaders(unsigned char *hash,
		  const VkPipelineShaderStageCreateInfo **stages,
		  const struct radv_pipeline_layout *layout,
		  const struct radv_pipeline_key *key,
		  uint32_t flags)
{}
bool
radv_create_shader_variants_from_pipeline_cache(struct radv_device *device,
					        struct radv_pipeline_cache *cache,
					        const unsigned char *sha1,
					        struct radv_shader_variant **variants)
{ return false;}

void
radv_pipeline_cache_insert_shaders(struct radv_device *device,
				   struct radv_pipeline_cache *cache,
				   const unsigned char *sha1,
				   struct radv_shader_variant **variants,
				   const void *const *codes,
				   const unsigned *code_sizes)
{
}
