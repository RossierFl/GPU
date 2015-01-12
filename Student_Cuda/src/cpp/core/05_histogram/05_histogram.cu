// Attention : Extension .cu
#include <curandTools.h>
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

__host__  bool isHistogram_Ok(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__host__  static bool computeHistogram(int n);
__global__ static void computeHistogramGPU(int n,bool* ptrDevRes, int* ptrDevTabData, int* ptrDevTabHisto,int lenght);
__global__ static void initTabData(curandState* tabGeneratorThread,int n,int ptrDevTabData[], int lenght);
__device__ void reduce_intra_thread_histogram(int* ptrDevTabData, int* tabSM, int n);
__device__ bool checkHistogram(int* ptrDevRes,int lenght,int n);
__device__ static void reduce_inter_block_histogram(int* tabSM, int* tabHistogramGM);
__host__ void fillAndSwapData(int* ptrHostData, int size);
#define HISTOGRAM_SIZE 256


/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__host__  bool isHistogram_Ok(int n)
    {
    cout << endl << "[Histogram Cuda 2]" << endl;


    bool histogramGPU = computeHistogram(n);

    //cout <<"\n[GPUPI] "<< sumPiGPU << endl;
    //printf("[GPU_Histogram] %f\n",histogramGPU);

    return histogramGPU;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__host__ bool computeHistogram(int n)
    {
    assert(n%HISTOGRAM_SIZE==0&&"n mut be a multiple of HISTOGRAM_SIZE");
    bool res = false;
    bool* ptrRes=&res;	// on host (CPU)
    bool* ptrDevRes; 	// on device (GPU)
    // Specifier nb thread : ici 1 thread au total !
    //dim3 dg = dim3(2,1,1);
    //dim3 db = dim3(4,1,1);
    //dim3 dg = dim3(16,1,1);
    //dim3 db = dim3(32,1,1);
    dim3 dg = dim3(16,1,1);
    dim3 db = dim3(32,1,1);

    // Debug
    Device::checkDimError(dg,db);

    //init result
    size_t size_res=sizeof(bool);
    HANDLE_ERROR(cudaMalloc((void**) &ptrDevRes, size_res)); // Device memory allocation (*)
    HANDLE_ERROR(cudaMemset(ptrDevRes,0,size_res)) ;
    //HANDLE_ERROR(cudaMemcpy(ptrRes, ptrDevRes, size_res, cudaMemcpyDeviceToHost));// Device -> Host

    int* ptrHostData = new int[n];
    fillAndSwapData(ptrHostData,n);
    //copy tab data
    int* ptrDevTabData;
    size_t sizeTabData = sizeof(int)*n;
    HANDLE_ERROR(cudaMalloc((void**) &ptrDevTabData, sizeTabData)); // Device memory allocation (*)
    HANDLE_ERROR(cudaMemcpy(ptrDevTabData,ptrHostData,sizeTabData,cudaMemcpyHostToDevice)) ;

    //init tab histogram final
    int* ptrDevTabHisto;
    size_t sizeTabHisto = sizeof(int)*HISTOGRAM_SIZE;
    HANDLE_ERROR(cudaMalloc((void**) &ptrDevTabHisto, sizeTabHisto)); // Device memory allocation (*)
    HANDLE_ERROR(cudaMemset(ptrDevTabHisto,0,sizeTabHisto));

    /*//init random generator
    curandState* ptrDevRandom; //will be done in a better version
    size_t sizeRandom = sizeof(curandState);
    HANDLE_ERROR(cudaMalloc((void**) &ptrDevRandom, sizeRandom)); // Device memory allocation (*)
    HANDLE_ERROR(cudaMemset(ptrDevRandom,0,sizeRandom));
    setup_kernel_rand<<<dg,db>>>(ptrDevRandom,Device::getDeviceId());
    Device::checkKernelError("setup_kernel_rand");*///will be done in a better version

    //init tabData
    /*initTabData<<<dg,db>>>(ptrDevRandom,n,ptrDevTabData,HISTOGRAM_SIZE);
    Device::checkKernelError("initTabData"); // facultatif*/


    int length = HISTOGRAM_SIZE;
    size_t sizeTabSM = sizeof(int)*length;
    assert((length&(length-1))==0&&"Whoops, length must be a power of two !");
    //int n,bool* ptrRes,float* ptrDevRes, float* ptrDevTabData,int lenght
    computeHistogramGPU<<<dg,db,sizeTabSM>>>(n,ptrDevRes, ptrDevTabData,ptrDevTabHisto,HISTOGRAM_SIZE); // asynchrone !!
    Device::checkKernelError("computeHistogramGPU"); // facultatif

    //v1
    Device::synchronize();// Pour printf sur  GPU

    // memoryManagement => barrier de synchronisation
    HANDLE_ERROR(cudaMemcpy(ptrRes, ptrDevRes, size_res, cudaMemcpyDeviceToHost));// Device -> Host
    if(res){
	printf("Result of histogramm computation : SUCCESS");
    }else{
	printf("Result of histogramm computation : FAIL");
    }

    HANDLE_ERROR(cudaFree(ptrDevRes)); // device dispose memory in (*)
    HANDLE_ERROR(cudaFree(ptrDevTabData)); // device dispose memory in (*)
    HANDLE_ERROR(cudaFree(ptrDevTabHisto)); // device dispose memory in (*)
    //HANDLE_ERROR(cudaFree(ptrDevRandom)); // device dispose memory in (*)
    //HANDLE_ERROR(cudaFree(ptrDevTabData)); // device dispose memory in (*)
    return res;
    }

__host__ void fillAndSwapData(int* ptrHostData, int size){

    //fill the data
    for(int i=0;i<size;i++)
      {
	ptrHostData[i]=i%HISTOGRAM_SIZE;
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




__global__ static void initTabData(curandState* ptrDevTabGeneratorThread,int n,int ptrDevTabData[], int lenght){ // try to do it on gpu, will be done in a better version
	  //init curand
	  /*int tid = Indice1D::tid();
	  // Global Memory -> Register
	  curandState localState = ptrDevTabGeneratorThread[tid]; //Optimisation
	  const int NBTHREAD = Indice1D::nbThread();
          const int TID = Indice1D::tid();

          int s = TID;
          while(s<n){
              ptrDevTabData[s]=s%HISTOGRAM_SIZE;
              s+=NBTHREAD;
          }
          __syncthreads();
          if(TID==0){
              for(int i = 0; i<n;i++)printf("value before swap %i\n",ptrDevTabData[i]);
          }
          s = TID;
          //xAlea = curand_uniform(&generatorThread);

          //assert(idx1==idx2);



	  while(s<n){
	      float idx1 = curand_uniform(&localState);
	      float idx2 = curand_uniform(&localState);
	      int id1 = (int)(idx1 * ((n) + 1));
	      int id2 = (int)(idx2 * ((n) + 1));
	      //lock.lock();
	      int tmp1 = ptrDevTabData[id1];
	      int tmp2 = ptrDevTabData[id2];
	      Lock lock1=Lock(&id1);
	      Lock lock2=Lock(&id2);
	      lock1.lock();
	      lock2.lock();
	      ptrDevTabData[id1] = tmp2;
	      ptrDevTabData[id2] = tmp1;
	      lock1.unlock();
	      lock2.unlock();
	      assert(tmp1==ptrDevTabData[id2]);
	      assert(tmp2==ptrDevTabData[id1]);
	      s+=NBTHREAD;
	      //lock.unlock();
	  }
	  if(TID==0)for(int i = 0; i<n;i++)printf("value after swap %i\n",ptrDevTabData[i]);*/

}

__global__ void computeHistogramGPU(int n,bool* ptrDevRes, int* ptrDevTabData, int* ptrDevTabHisto,int lenght)
    {

    //une instance par block
      //init tab
      const int TID_LOCAL = Indice1D::tidLocalBlock();
      extern __shared__ int tabSM[];


      UtilsCUDA::initialise(tabSM,lenght);
      UtilsCUDA::initialise(ptrDevTabHisto,lenght);
      reduce_intra_thread_histogram(ptrDevTabData,tabSM, n);
      __syncthreads();
      reduce_inter_block_histogram(tabSM,ptrDevTabHisto);
      *ptrDevRes = checkHistogram(ptrDevTabHisto,lenght,n);
  }

__device__ void reduce_inter_block_histogram(int* tabSM, int* tabHistogramGM){
	  const int NBTHREAD = Indice1D::nbThread();
	  const int NBTHREADBLOCK = Indice1D::nbThreadBlock();
          const int TID = Indice1D::tid();
          const int TID_LOCAL = Indice1D::tidLocal();

          int s = TID_LOCAL;
          while(s<HISTOGRAM_SIZE){
              atomicAdd(&tabHistogramGM[s],tabSM[s]);
              s+=NBTHREADBLOCK;
          }

     }

__device__ bool checkHistogram(int* ptrDevRes,int lenght,int n){
	const int NBTHREAD = Indice1D::nbThread();
        const int TID = Indice1D::tid();
        const int TID_LOCAL = Indice1D::tidLocalBlock();

        int s = TID;
        bool isOK = true;
        int expectedResult = n/HISTOGRAM_SIZE;
        while(isOK&&s<lenght){
	    if(ptrDevRes[s]!=expectedResult)isOK=false;
            s+=NBTHREAD;
        }
        __syncthreads();
        return isOK;
}


__device__ void reduce_intra_thread_histogram(int* ptrDevTabData, int* tabSM, int n){
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

