
#include "main/mtypes.h"
#include "state_tracker/st_glsl_to_tgsi.h"
#include "state_tracker/st_context.h"

#include "pipe/p_defines.h"
#include "pipe/p_context.h"
#include "pipe/p_screen.h"

#include "radeon/radeon_winsys.h"
#include "radeonsi/si_public.h"
#include "radeonsi/si_pipe.h"
#include "offline_si.h"

static struct st_context g_st = { 0 };
static struct si_context g_p = { 0 };
//static struct si_screen g_screen = {};
static struct gl_pipeline_object g_dummy_pipeline_object = { 0 };
static struct radeon_info g_info = { 0 };

struct gl_program* st_new_program(struct gl_context* ctx, GLenum target, GLuint id, bool is_arb_asm);
GLboolean st_program_string_notify(struct gl_context* ctx, GLenum target, struct gl_program* prog);
void si_init_shader_functions(struct si_context* sctx);

static void query_info(struct radeon_winsys* ws,  struct radeon_info* info)
{
   *info = g_info;
}

static struct radeon_winsys_ctx* ctx_create(struct radeon_winsys* ws)
{
   return (struct radeon_winsys_ctx*)4;
}

static struct radeon_cmdbuf* cs_create(
   struct radeon_winsys_ctx* ctx,
   enum ring_type ring_type,
   void (*flush)(void* ctx, unsigned flags, struct pipe_fence_handle** fence),
   void* flush_ctx,
   bool stop_exec_on_failure)
{
   return (struct radeon_cmdbuf*)4;
}


void initialize_si(struct gl_context* ctx, gl_api api)
{
   //ctx->Driver.ProgramStringNotify = st_program_string_notify;

   ctx->_Shader = &g_dummy_pipeline_object;

   ctx->st = &g_st;
   g_st.ctx = ctx;
   g_st.pipe = &g_p.b;
   si_init_shader_functions(&g_p);
   uint32_t debug_flags = 0;// DBG_FS | DBG_VS | DBG_PS | DBG_TES | DBG_GS | DBG_TCS | DBG_CS | DBG_PRECOMPILE;
   //struct radeon_winsys ws = { 0 };
   struct pipe_screen_config ws = { 0 };
   g_info.chip_class = GFX9;//VI;
   g_info.family = CHIP_VEGA10;//CHIP_TONGA;
   //ws.query_info = query_info;
   //ws.ctx_create = ctx_create;
   //ws.cs_create = &cs_create;
   struct si_screen* pscreen = (struct si_screen*)radeonsi_screen_create(0, &ws);
   g_p.screen = pscreen;
   g_p.b.screen = (struct pipe_screen*)pscreen;

}

char dladdr(void)
{
   return 0;
}

int drmPrimeHandleToFD(int fd, uint32_t handle, uint32_t flags, int* prime_fd)
{
   return 0;
}

int drmPrimeFDToHandle(int fd, int prime_fd, uint32_t* handle)
{
   return 0;
}

int drmGetCap(int fd, uint64_t capability, uint64_t* value)
{
   return 0;
}

int drmIoctl(int fd, unsigned long request, void* arg)
{
   return 0;
}
void          drmFreeVersion(drmVersionPtr a)
{

}

drmVersionPtr drmGetVersion(int fd)
{
   return NULL;
}
int drmGetDevice2(int fd, uint32_t flags, drmDevicePtr* device)
{
   return 0;
}

void drmFreeDevice(drmDevicePtr* device)
{

}
int           drmCommandWrite(int fd, unsigned long drmCommandIndex,
   void* data, unsigned long size)
{
   return 0;
}
int           drmCommandWriteRead(int fd, unsigned long drmCommandIndex,
   void* data, unsigned long size)
{
   return 0;
}
