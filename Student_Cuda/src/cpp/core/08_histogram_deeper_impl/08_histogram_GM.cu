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

__host__  void computeHistogram_GM(int* dataImg, int dataLength, int* resultHisto, int lengthHisto);
__global__ static void computeHistogramGPU_GM(int n,int* ptrDevRes, int* ptrDevTabData,int lenght);
__device__ void reduce_intra_thread_histogram_GM(int* ptrDevTabData, int* ptrDevRes, int n);
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

__host__ void computeHistogram_GM(int* dataImg, int dataLength, int* resultHisto, int lengthHisto)
    {
    //Device::loadCudaDriverAll(false);
    cout << endl << "[Histogram Cuda 2 Global Memory]" << endl;

    int* ptrDevRes; 	// on device (GPU)
    dim3 dg = dim3(4,1,1);
    dim3 db = dim3(8,1,1);

    // Debug
    Device::checkDimError(dg,db);

    Chronos chrono;
    chrono.start();
    //init result
    size_t size_res=sizeof(int)*lengthHisto;
    HANDLE_ERROR(cudaMalloc((void**) &ptrDevRes, size_res)); // Device memory allocation (*)
    HANDLE_ERROR(cudaMemset(ptrDevRes,0,size_res)) ;

    //copy tab data
    int* ptrDevTabData;
    size_t sizeTabData = sizeof(int)*dataLength;
    HANDLE_ERROR(cudaMalloc((void**) &ptrDevTabData, sizeTabData)); // Device memory allocation (*)
    HANDLE_ERROR(cudaMemcpy(ptrDevTabData,dataImg,sizeTabData,cudaMemcpyHostToDevice));



    //size_t sizeTabSM = sizeof(int)*lengthHisto;
    //assert((lengthHisto&(lengthHisto-1))==0&&"Whoops, length must be a power of two !");
    chrono.stop();
    chrono.print("MM In : ");
    chrono.start();
    computeHistogramGPU_GM<<<dg,db>>>(dataLength,ptrDevRes, ptrDevTabData,lengthHisto); // asynchrone !!
    Device::checkKernelError("computeHistogramGPU_GM"); // facultatif

    //v1
    Device::synchronize();// Pour printf sur  GPU
    chrono.stop();
    chrono.print("Computation In : ");
    chrono.start();
    // memoryManagement => barrier de synchronisation
    HANDLE_ERROR(cudaMemcpy(resultHisto, ptrDevRes, size_res, cudaMemcpyDeviceToHost));// Device -> Host

    HANDLE_ERROR(cudaFree(ptrDevRes)); // device dispose memory in (*)
    HANDLE_ERROR(cudaFree(ptrDevTabData)); // device dispose memory in (*)
    chrono.stop();
    chrono.print("MM Out : ");
    }

__global__ void computeHistogramGPU_GM(int n,int* ptrDevRes, int* ptrDevTabData,int lenght)
    {

    //une instance par block
      //init tab
      const int TID_LOCAL = Indice1D::tidLocalBlock();
      //extern __shared__ int tabSM[];


      //UtilsCUDA::initialise(tabSM,lenght);
      UtilsCUDA::initialise(ptrDevRes,lenght);
      reduce_intra_thread_histogram_GM(ptrDevTabData,ptrDevRes, n);
      //__syncthreads();
      //reduce_inter_block_histogram_GM(tabSM,ptrDevRes, lenght); useless
  }


__device__ void reduce_intra_thread_histogram_GM(int* ptrDevTabData, int* ptrDevRes, int n){
      const int NBTHREAD = Indice1D::nbThread();
      const int TID = Indice1D::tid();
      const int TID_LOCAL = Indice1D::tidLocalBlock();

      int s = TID;
      while(s<n){
	  int cValue= ptrDevTabData[s];

	  atomicAdd(&ptrDevRes[cValue],1);
          s+=NBTHREAD;
      }
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

