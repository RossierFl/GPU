// Attention : Extension .cu
//#include <curandTools.h>
#include <iostream>
#include <stdio.h>
#include "cudaTools.h"
#include "Device.h"
#include "Indice1D.h"
#include "UtilsCuda.h"
#include <assert.h>
#include <math.h>
#include <limits.h>
#include "AleaTools.h"
#include "Chronos.h"
#include "cuda_runtime.h"

//#include <curand_kernel.h>
#include "Lock.h"

using std::cout;
using std::endl;


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

//__host__  bool isHistogramSM_Ok(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__host__  void computeHistogram_ZCM(int* dataImg, int dataLength, int* resultHisto, int lengthHisto);
__global__ static void computeHistogramGPU_ZCM(int n,int* ptrDevRes, int* ptrDevTabData,int lenght);
__device__ void reduce_intra_thread_histogram_ZCM(int* ptrDevTabData, int* tabSM, int n);
__device__ static void reduce_inter_block_histogram_ZCM(int* tabSM, int* tabHistogramGM, int histogramSize);
/*__host__ bool checkHistogram_host(int* ptrDevRes,int lenght,int n);
__global__ void checkHistogram_GPU(int* ptrDevRes,int lenght,int n, bool* ptrDevBoolResult);*/



/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__host__ void computeHistogram_ZCM(int* dataImg, int dataLength, int* resultHisto, int lengthHisto)
    {
    //Device::loadCudaDriverAll(true);
    cout << endl << "[Histogram Cuda 2 Zero Copy Memory]" << endl;
    printf("tets\n");

    int* ptrDevRes; 	// on device (GPU)
    dim3 dg = dim3(4,1,1);
    dim3 db = dim3(8,1,1);

    // Debug
    Device::checkDimError(dg,db);
    printf("tetsfadsf\n");
    Chronos chrono;
    chrono.start();

    //HANDLE_ERROR(cudaSetDeviceFlags(cudaDeviceMapHost));
    //copy tab data
    size_t size_res=sizeof(int)*lengthHisto;
    HANDLE_ERROR(cudaMalloc((void**) &ptrDevRes, size_res)); // Device memory allocation (*)
    HANDLE_ERROR(cudaMemset(ptrDevRes,0,size_res)) ;


    //tab data zerocopy
    printf("tetsfads\n");
    int* dataImgZCM;
    size_t dataSize = dataLength*sizeof(int);
    HANDLE_ERROR(cudaHostAlloc((void**)&dataImgZCM,dataSize,cudaHostAllocMapped));
    HANDLE_ERROR(cudaHostAlloc((void**)&dataImgZCM,dataSize,cudaHostAllocMapped|cudaHostAllocWriteCombined));
    int flagInutialiser=0;
    int* ptrDevTabData;
    //size_t dataSize = dataLength*sizeof(int);
    memcpy(dataImgZCM, dataImg, dataSize);
    //HANDLE_ERROR(cudaMemcpy(dataImgZCM,dataImg,dataSize,cudaMemcpyHostToHost));
    HANDLE_ERROR(cudaHostGetDevicePointer(&ptrDevTabData,dataImgZCM,flagInutialiser));
    //HANDLE_ERROR(cudaMalloc((void**) &ptrDevRes, size_res)); // Device memory allocation (*)
    //HANDLE_ERROR(cudaMemset(ptrDevRes,0,size_res)) ;
    printf("tets\n");



    size_t sizeTabSM = sizeof(int)*lengthHisto;
    assert((lengthHisto&(lengthHisto-1))==0&&"Whoops, length must be a power of two !");
    chrono.stop();
    chrono.print("MM In : ");
    chrono.start();
    computeHistogramGPU_ZCM<<<dg,db,sizeTabSM>>>(dataLength,ptrDevRes, ptrDevTabData,lengthHisto); // asynchrone !!
    Device::checkKernelError("computeHistogramGPU_ZCM"); // facultatif
    Device::synchronize();// Pour printf sur  GPU
    chrono.stop();
    chrono.print("Computation In : ");
    chrono.start();
    // memoryManagement => barrier de synchronisation
    HANDLE_ERROR(cudaMemcpy(resultHisto, ptrDevRes, size_res, cudaMemcpyDeviceToHost));// Device -> Host

    HANDLE_ERROR(cudaFree(ptrDevRes)); // device dispose memory in (*)
    //HANDLE_ERROR(cudaFree(ptrDevTabData)); // device dispose memory in (*)*/
    HANDLE_ERROR(cudaFreeHost(dataImgZCM));
    //HANDLE_ERROR(cudaFree(ptrDevRes));
    chrono.stop();
    chrono.print("MM Out : ");
    }

__global__ void computeHistogramGPU_ZCM(int n,int* ptrDevRes, int* ptrDevTabData,int lenght)
    {

    //une instance par block
      //init tab
      const int TID_LOCAL = Indice1D::tidLocalBlock();
      extern __shared__ int tabSM[];


      UtilsCUDA::initialise(tabSM,lenght);
      //UtilsCUDA::initialise(ptrDevRes,lenght);
      reduce_intra_thread_histogram_ZCM(ptrDevTabData,tabSM, n);
      __syncthreads();
      reduce_inter_block_histogram_ZCM(tabSM,ptrDevRes, lenght);
  }

__device__ void reduce_inter_block_histogram_ZCM(int* tabSM, int* tabHistogramGM, int histogramSize){
	  const int NBTHREAD = Indice1D::nbThread();
	  const int NBTHREADBLOCK = Indice1D::nbThreadBlock();
          const int TID = Indice1D::tid();
          const int TID_LOCAL = Indice1D::tidLocal();

          int s = TID_LOCAL;
          while(s<histogramSize){
              atomicAdd(&tabHistogramGM[s],tabSM[s]);
              s+=NBTHREADBLOCK;
          }

     }


__device__ void reduce_intra_thread_histogram_ZCM(int* ptrDevTabData, int* tabSM, int n){
      const int NBTHREAD = Indice1D::nbThread();
      const int TID = Indice1D::tid();
      const int TID_LOCAL = Indice1D::tidLocalBlock();

      int s = TID;
      while(s<n){
	  int cValue= ptrDevTabData[s];

	  atomicAdd(&tabSM[cValue],1);
          s+=NBTHREAD;
      }
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

