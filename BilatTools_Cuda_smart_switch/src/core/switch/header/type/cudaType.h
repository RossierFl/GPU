#ifndef CUDA_TYPE_PRIORITE_H_
#define CUDA_TYPE_PRIORITE_H_

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

#ifndef CBI_NO_CUDA	 // pour compilation avec cuda

#include "cudaTools.h"
#include "cuda_runtime.h"
//#include "prioriteGPU.h"

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned char
#endif

#ifndef ulong
#define ulong unsigned char
#endif


#else // pour compilation sans cuda

#include "cudaType_CPU.h"
#include "prioriteCPU.h"

#endif


#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
