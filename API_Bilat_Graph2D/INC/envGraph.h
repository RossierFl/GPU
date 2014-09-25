#ifndef ENVI_CBI_GRAPH_H
#define ENVI_CBI_GRAPH_H

#include "dllHelper.h"

#ifdef CBI_GRAPH_DLL // defined if API is compiled as a DLL
  #ifdef CBI_GRAPH_DLL_EXPORT // defined if we are building the API DLL (instead of using it)
    #define CBI_GRAPH HELPER_DLL_EXPORT
  #else
    #define CBI_GRAPH HELPER_DLL_IMPORT
  #endif
  #define CBI_GRAPH_LOCAL HELPER_DLL_LOCAL
#else // GL_TOOLS_USE_DLL is not defined: this means API is a static lib.
  #define CBI_GRAPH
  #define CBI_GRAPH_LOCAL
#endif


#endif
