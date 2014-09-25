/**
 * Bilat_Canvas_JNI
 *
 * version : 001
 *
 * Cédric Bilat		cedric.bilat@he-arc.ch
 * Stähli Joaquim	joaquim.stahli@he-arc.ch
 */

#ifndef ENV_CANVAS_JNI_H
#define ENV_CANVAS_JNI_H

#include "dllHelper.h"

#ifdef CBI_CANVAS_JNI_DLL
  #ifdef CBI_CANVAS_JNI_EXPORT
    #define CBI_CANVAS_JNI HELPER_DLL_EXPORT
  #else
    #define CBI_CANVAS_JNI HELPER_DLL_IMPORT
  #endif
  #define CBI_CANVAS_JNI_LOCAL HELPER_DLL_LOCAL
#else
  #define CBI_CANVAS_JNI
  #define CBI_CANVAS_JNI_LOCAL
#endif


#endif //ENV_CANVAS_JNI_H
