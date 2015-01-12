#ifndef ENV_CBI_MULTI_COURBES_H
#define ENV_CBI_MULTI_COURBES_H

#include "dllHelper.h"

#ifdef CBI_MULTI_COURBES_DLL // defined if API is compiled as a DLL
  #ifdef CBI_MULTI_COURBES_DLL_EXPORT // defined if we are building the API DLL (instead of using it)
    #define CBI_MULTI_COURBES HELPER_DLL_EXPORT
  #else
    #define CBI_MULTI_COURBES HELPER_DLL_IMPORT
  #endif
  #define CBI_MULTI_COURBES_LOCAL HELPER_DLL_LOCAL
#else // GL_TOOLS_USE_DLL is not defined: this means API is a static lib.
  #define CBI_MULTI_COURBES
  #define CBI_MULTI_COURBES_LOCAL
#endif


#endif
