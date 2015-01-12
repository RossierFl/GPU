//PRIVATE
#ifndef ENV_IMAGE_CUDA_JNI_H
#define ENV_IMAGE_CUDA_JNI_H

#include "dllHelper.h"

#ifdef CBI_IMAGE_CUDA_JNI_DLL // defined if API is compiled as a DLL

    #ifdef CBI_IMAGE_CUDA_JNI_EXPORT // defined if we are building the API DLL (instead of using it)
	#define CBI_IMAGE_CUDA_JNI HELPER_DLL_EXPORT
    #else
	#define CBI_IMAGE_CUDA_JNI HELPER_DLL_IMPORT
    #endif
    #define CBI_IMAGE_CUDA_JNI_LOCAL HELPER_DLL_LOCAL
#else // using static lib
    #define CBI_IMAGE_CUDA_JNI
    #define CBI_IMAGE_CUDA_JNI_LOCAL
#endif

#endif
