#ifndef CUDAUTILS_H_
#define CUDAUTILS_H_

#include <iostream>
#include "Indice1D.h"
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

// http://docs.nvidia.com/cuda/cuda-c-programming-guide/#atomiccas
// can't be in class, because conflict with atomicAdd(float)
__device__ static double atomicAdd(double* address, double val)
    {
    unsigned long long int* address_as_ull =
	    (unsigned long long int*)address;
    unsigned long long int old = *address_as_ull, assumed;

    do
	{
	assumed = old;
	old = atomicCAS(address_as_ull, assumed,
		__double_as_longlong(val +
			__longlong_as_double(assumed)));

	// Note: uses integer comparison to avoid hang in case of NaN (since NaN != NaN)
	} while (assumed != old);

    return __longlong_as_double(old);
    }

/**
 * Dans un header only pour preparer la version cuda
 */
class CUDAUtils
    {
	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

	public:

	__device__ CUDAUtils(){}

	__device__ ~CUDAUtils(void){}

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

	public:

	__device__ static void initialize(int* tabSM, int length)
	    {
	const int NBTHREAD_BLOCK = Indice1D::nbThreadBlock();
	const int TID_LOCAL = Indice1D::tidLocal();
	int s = TID_LOCAL;
	while(s<length)
	    {
	    tabSM[s] = 0.0;
	    s+=NBTHREAD_BLOCK;
	    }
	__syncthreads();
	}

	__device__ static void initialize(float* tabSM, int length)
	    {
	    const int NBTHREAD_BLOCK = Indice1D::nbThreadBlock();
	    const int TID_LOCAL = Indice1D::tidLocal();
	    int s = TID_LOCAL;
	    while(s<length)
		{
		tabSM[s] = 0.0;
		s+=NBTHREAD_BLOCK;
		}
	    __syncthreads();
	}

	__device__ static void initialize(double* tabSM, int length)
	    {
	    const int NBTHREAD_BLOCK = Indice1D::nbThreadBlock();
	    const int TID_LOCAL = Indice1D::tidLocal();
	    int s = TID_LOCAL;
	    while(s<length)
		{
		tabSM[s] = 0.0;
		s+=NBTHREAD_BLOCK;
		}
	    __syncthreads();
	}

	__device__ static void reduceInterBlock(float* tabSM, float* ptrDevResult)
	    {
	    const int TID_LOCAL = Indice1D::tidLocalBlock();
	    if(TID_LOCAL==0)
		{
		atomicAdd(ptrDevResult,tabSM[0]);
		}

	}

	__device__ static void reduceInterBlock(double* tabSM, double* ptrDevResult)
	    {
	    const int TID_LOCAL = Indice1D::tidLocalBlock();
	    if(TID_LOCAL==0)
		{
		atomicAdd(ptrDevResult,tabSM[0]);
		}

	}

	__device__ static void reduceInterBlock_v2(float* tabSM, float* ptrDevResult, int size)
	    {
	    const int NB_THREAD = Indice1D::nbThread();
	    const int TID = Indice1D::tid();
	    const int TID_LOCAL = Indice1D::tidLocalBlock();
	    int s = TID;
	    while(s<size)
		{
		atomicAdd(&ptrDevResult[s],tabSM[s]);
		s+=NB_THREAD;
		}
	}

	__device__ static void reduceInterBlock_v2(int* tabSM, int* ptrDevResult, int size)
	    {
	    const int NB_THREAD = Indice1D::nbThread();
	    const int TID = Indice1D::tid();
	    const int TID_LOCAL = Indice1D::tidLocalBlock();
	    int s = TID;
	    while(s<size)
		{
		atomicAdd(&ptrDevResult[s],tabSM[s]);
		s+=NB_THREAD;
		}
	}

	__device__ static void reduceInterBlock_v2(double* tabSM, double* ptrDevResult, int size){
	    const int NB_THREAD = Indice1D::nbThread();
	    const int TID = Indice1D::tid();
	    const int TID_LOCAL = Indice1D::tidLocalBlock();
	    int s = TID;
	    while(s<size)
		{
		atomicAdd(&ptrDevResult[s],tabSM[s]);
		s+=NB_THREAD;
		}
	}

	__device__ static void reduceIntraBlock(float* tabSM){

	    const int NBTHREAD = Indice1D::nbThread();
	    const int NBTHREADBLOCK=Indice1D::nbThreadBlock();
	    int half = NBTHREADBLOCK/2;
	    while(half>=1){
		ecrasement(tabSM,half);
		__syncthreads();
		half/=2;
	    }

	}

	__device__ static void reduceIntraBlock(double* tabSM){

	    const int NBTHREAD = Indice1D::nbThread();
	    const int NBTHREADBLOCK=Indice1D::nbThreadBlock();
	    int half = NBTHREADBLOCK/2;
	    while(half>=1){
		ecrasement(tabSM,half);
		__syncthreads();
		half/=2;
	    }

	}

	__device__ static void ecrasement(float* tabSM, int half){
	    const int TID_LOCAL = Indice1D::tidLocalBlock();
	    const int NB_THREAD_BLOCK = Indice1D::nbThreadBlock();
	    int s = TID_LOCAL;
	    while(s<half){
		tabSM[s] += tabSM[s+half];
		s+=NB_THREAD_BLOCK;
	    }
	}

	__device__ static void ecrasement(double* tabSM, int half){
	    const int TID_LOCAL = Indice1D::tidLocalBlock();
	    const int NB_THREAD_BLOCK = Indice1D::nbThreadBlock();
	    int s = TID_LOCAL;
	    while(s<half){
		tabSM[s] += tabSM[s+half];
		s+=NB_THREAD_BLOCK;
	    }
	}

    }
;

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
