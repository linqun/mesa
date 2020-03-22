
#ifndef OFFLINE_SI_H
#define OFFLINE_SI_H

#include "xf86drm_fake.h"

#ifdef __cplusplus
extern "C" {
#endif
     

   void initialize_si(struct gl_context* ctx, gl_api api);
   char dladdr(void);
#ifdef __cplusplus
}
#endif

#endif
