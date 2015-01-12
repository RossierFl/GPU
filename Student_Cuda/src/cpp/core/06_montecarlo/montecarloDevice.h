#ifndef MONTECARLODEVICE_H_
#define MONTECARLODEVICE_H_
#include "cudaTools.h"

#include <curand_kernel.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
class MontecarloDevice
    {
    public :
	void runMontecarlo(curandState* ptrDevRandom,float* ptrDevGM,float  xMin,float xMax,int m,long n,size_t sizeTabSM,dim3 dg,dim3 db);
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
