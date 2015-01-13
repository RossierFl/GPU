#include <assert.h>
#include <cstdio>
#include <curandTools.h>

#include "cuda_utils.h"
#include "cudaTools.h"
#include "Device.h"
#include "Indice1D.h"
#include "AleaTools.h"

#define HISTOGRAMME_SIZE 512

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__host__ bool isHistogramme_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__host__ static bool computeHistogramme(int n);
__global__ static void computeHistogrammeGPU(int n,bool* ptrDevResult, int* ptrDevData, int* ptrDevHistogramme,int length);
__device__ void reduceIntraThreadHistogramme(int* ptrDevData, int* tabSM, int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__host__ bool isHistogramme_Ok(int n)
    {
    cout << endl << "[Histogramme Cuda]" << endl;
    int histogrammeGPU = computeHistogramme(n);
    printf("[GPU HISTOGRAMME] : %d\n",histogrammeGPU);
    return true;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__host__ void swap(int* ptrHostData, int size)
    {
    //fill the data
    for(int i=0;i<size;i++)
	{
	ptrHostData[i]=i%HISTOGRAMME_SIZE;
	}
    //swap
    AleaTools at;
    for(int i=0;i<size*size;i++)
	{
	int a = at.uniformeAB(0,size-1);
	int b = at.uniformeAB(0,size-1);
	int tmpA = ptrHostData[a];
	int tmpB = ptrHostData[b];
	ptrHostData[a]=tmpB;
	ptrHostData[b] = tmpA;
	}
    }

__host__ bool computeHistogramme(int n)
    {
    bool res = false;
    bool* ptrRes=&res;
    bool* ptrDevRes;
    dim3 dg = dim3(16,1,1);
    dim3 db = dim3(32,1,1);


    size_t size_res=sizeof(bool);
    HANDLE_ERROR(cudaMalloc((void**) &ptrDevRes, size_res)); // Device memory allocation (*)
    HANDLE_ERROR(cudaMemset(ptrDevRes,0,size_res)) ;

    int* ptrHostData = new int[n];
    swap(ptrHostData,n);

    int* ptrDevData;
    size_t sizeTabData = sizeof(int)*n;
    HANDLE_ERROR(cudaMalloc((void**) &ptrDevData, sizeTabData)); // Device memory allocation (*)
    HANDLE_ERROR(cudaMemcpy(ptrDevData,ptrHostData,sizeTabData,cudaMemcpyHostToDevice)) ;

    int* ptrDevHistogramme;
    size_t sizeTabHisto = sizeof(int)*HISTOGRAMME_SIZE;
    HANDLE_ERROR(cudaMalloc((void**) &ptrDevHistogramme, sizeTabHisto)); // Device memory allocation (*)
    HANDLE_ERROR(cudaMemset(ptrDevHistogramme,0,sizeTabHisto));

    int length = HISTOGRAMME_SIZE;
    size_t sizeSM = sizeof(int)*length;

    computeHistogrammeGPU<<<dg,db,sizeSM>>>(n,ptrDevRes, ptrDevData,ptrDevHistogramme,HISTOGRAMME_SIZE);

    cudaDeviceSynchronize();

    HANDLE_ERROR(cudaMemcpy(ptrRes, ptrDevRes, size_res, cudaMemcpyDeviceToHost));// Device -> Host

    // avoid memory leak, free memory
    HANDLE_ERROR(cudaFree(ptrDevRes));
    HANDLE_ERROR(cudaFree(ptrDevData));
    HANDLE_ERROR(cudaFree(ptrDevHistogramme));
    return res;
    }

__device__ bool checkHistogramme(int* ptrDevResult,int length,int n){
    const int NBTHREAD = Indice1D::nbThread();
    const int TID = Indice1D::tid();
    const int TID_LOCAL = Indice1D::tidLocalBlock();
    int s = TID;
    bool isCorrect = true;
    int correctResult = n/HISTOGRAMME_SIZE;
    while(isCorrect&&s<length)
	{
	if(ptrDevResult[s]!=correctResult)
	    isCorrect=false;
	s+=NBTHREAD;
	}
    __syncthreads();
    return isCorrect;
}

__global__ void computeHistogrammeGPU(int n,bool* ptrDevResult, int* ptrDevData, int* ptrDevHistogramme,int length)
    {
    const int TID_LOCAL = Indice1D::tidLocalBlock();
    extern __shared__ int tabSM[];
    CUDAUtils::initialize(tabSM,length);
    CUDAUtils::initialize(ptrDevHistogramme,length);
    reduceIntraThreadHistogramme(ptrDevData,tabSM, n); // add suffix, avoid multiple definition error
    __syncthreads();
    CUDAUtils::reduceInterBlock_v2(tabSM,ptrDevHistogramme,HISTOGRAMME_SIZE);
    *ptrDevResult = checkHistogramme(ptrDevHistogramme,length,n);
    }

__device__ void reduceIntraThreadHistogramme(int* ptrDevData, int* tabSM, int n)
    {
    const int NBTHREAD = Indice1D::nbThread();
    const int TID = Indice1D::tid();
    const int TID_LOCAL = Indice1D::tidLocalBlock();
    int s = TID;
    while(s<n){
	int crtValue= ptrDevData[s];
	atomicAdd(&tabSM[crtValue],1);
	s+=NBTHREAD;
    }
    }



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

