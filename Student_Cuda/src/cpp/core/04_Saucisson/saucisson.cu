#include <assert.h>
#include <cstdio>

#include "cuda_utils.h"
#include "cudaTools.h"
#include "Device.h"
#include "Indice1D.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__host__ bool isSaucisson_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__host__ static float computeSaucisson(int n);
__global__ static void computeSaucissonGPU(int n,float* ptrDevResult, int length);
__device__ void reduceIntraThreadSaucisson(float* tabSM, int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__host__ bool isSaucisson_Ok(int n)
    {
    cout << endl << "[Saucisson Cuda]" << endl;
    float saucissonGPU = computeSaucisson(n);
    printf("[GPU SAUCISSON] : %f\n",saucissonGPU);
    return true;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__host__ float computeSaucisson(int n)
    {
    float res = 0.0;
    float* ptrHostResult=&res;
    float* ptrDevResult;

    dim3 dg = dim3(32,1,1);
    dim3 db = dim3(64,1,1);

    Device::checkDimError(dg,db);
    size_t size=sizeof(float);

    HANDLE_ERROR(cudaMalloc((void**) &ptrDevResult, size));
    HANDLE_ERROR(cudaMemset(ptrDevResult,0,size)) ;
    HANDLE_ERROR(cudaMemcpy(ptrHostResult, ptrDevResult, size, cudaMemcpyDeviceToHost));// Device -> Host

    int nbThreads = db.x;
    size_t sizeSM = sizeof(float)*nbThreads;

    computeSaucissonGPU<<<dg,db,sizeSM>>>(n, ptrDevResult,nbThreads);


    cudaDeviceSynchronize();

    HANDLE_ERROR(cudaMemcpy(ptrHostResult, ptrDevResult, size, cudaMemcpyDeviceToHost));
    HANDLE_ERROR(cudaFree(ptrDevResult));

    double DX = 1.0/(double)n;
    return res*DX;
    }

__global__ void computeSaucissonGPU(int n, float* ptrDevResult,int length)
    {
    const int TID_LOCAL = Indice1D::tidLocalBlock();
    extern __shared__ float tabSM[];

    reduceIntraThreadSaucisson(tabSM, n);
    __syncthreads();
    CUDAUtils::reduceIntraBlock(tabSM);
    CUDAUtils::reduceInterBlock(tabSM,ptrDevResult);
    }

__device__ float f(float x)
    {
    return 4.0 / (1.0 + x * x); // see pdf
    }

__device__ void reduceIntraThreadSaucisson(float* tabSM, int n)
    {
    const int NBTHREAD = Indice1D::nbThread();
    const int TID = Indice1D::tid();
    const int TID_LOCAL = Indice1D::tidLocalBlock();

    const double DX = 1.0/(double)n;
    int s = TID;
    float sumCrtThread = 0.0;
    float xs = 0.0;

    while(s<n)
	{
	xs = s * DX;
	sumCrtThread += f(xs);
	s+=NBTHREAD;
	}

    tabSM[TID_LOCAL] = sumCrtThread;
    }



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

