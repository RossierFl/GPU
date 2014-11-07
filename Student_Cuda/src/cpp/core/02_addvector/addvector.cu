#include "Indice2D.h"
#include "cudaTools.h"
#include <iostream>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
__host__ void useAdd();

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/
static __global__ void add(float* ptrDevV1, float* ptrDevV2, int n, float* ptrDevResult);
static __device__ float work(float v1, float v2);
static __host__ void fillArray(float* floatArray, int n, int k);
/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
__host__ void useAdd()
    {
    int n = 3;

    float v1[n];
    fillArray(v1,n,1);

    float v2[n];
    fillArray(v2,n,2);

    float vResult[n];
    size_t size = n*sizeof(float);
    float* ptrDevV1 = NULL;
    float* ptrDevV2 = NULL;
    float* ptrDevResult = NULL;

    HANDLE_ERROR(cudaMalloc(&ptrDevV1,size));
    HANDLE_ERROR(cudaMalloc(&ptrDevV2,size));
    HANDLE_ERROR(cudaMalloc(&ptrDevResult,size));
    //
    HANDLE_ERROR(cudaMemset(ptrDevV1,0,size));
    HANDLE_ERROR(cudaMemset(ptrDevV2,0,size));
    HANDLE_ERROR(cudaMemset(ptrDevResult,0,size));
    //memCpy(src, dst, size, flag-copy)
    HANDLE_ERROR(cudaMemcpy(ptrDevV1, v1, size, cudaMemcpyHostToDevice));
    HANDLE_ERROR(cudaMemcpy(ptrDevV2, v2, size, cudaMemcpyHostToDevice));

    dim3 dg = dim3(2,2,1);
    dim3 db = dim3(2,2,1);
    Device::checkDimError(dg,db);
    add<<<dg,db>>>(ptrDevV1, ptrDevV2, 3, ptrDevResult);//asynchronous
    Device::checkKernelError("addVector");
    HANDLE_ERROR(cudaMemcpy(vResult, ptrDevResult, size, cudaMemcpyDeviceToHost));//barriere implicite de sync
    std::cout << vResult[0] << "," << vResult[1] << "," << vResult[2] << std::endl;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/
__global__ void add(float* ptrDevV1, float* ptrDevV2, int n, float* ptrDevResult)
    {
	const int NB_THREADS = Indice2D::nbThread();
	const int TID = Indice2D::tid();

	int s = TID;

	while(s < n)
	    {
	    ptrDevResult[s] = work(ptrDevV1[s], ptrDevV2[s]);
	    s+=NB_THREADS;
	    }
    }

__device__ float work(float v1, float v2)
    {
	return v1 + v2;
    }

__host__ void fillArray(float* floatArray, int n, int k)
    {
	for(int i = 0;i<n;i++)
	    {
	    floatArray[i] = (i+1)*k;
	    }
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

