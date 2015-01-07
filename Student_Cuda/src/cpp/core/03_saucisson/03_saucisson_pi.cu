// Attention : Extension .cu

#include <iostream>
#include <stdio.h>
#include "cudaTools.h"
#include "Device.h"
#include "Indice1D.h"
#include "UtilsCuda.h"
#include <assert.h>

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

__host__  bool isPiGPU_Ok(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__host__  static float computePi(int n);
__global__ static void computePiGPU(int n,float* ptrDevResult, int lenght);
__device__ void reduce_intra_thread(float* tabSM, int n);
//__device__ void reduce_inter_block(float* tabSM, float* ptrDevResult);
//__device__ void reduce_intra_block(float* tabSM, int length);
//__device__ void ecrasement(float* tabSM, int half);
__device__ float fpi(float x);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__host__  bool isPiGPU_Ok(int n)
    {
    cout << endl << "[PI Cuda 2]" << endl;


    float sumPiGPU = computePi(n);

    //cout <<"\n[GPUPI] "<< sumPiGPU << endl;
    printf("[GPUPI] %.10f\n",sumPiGPU);

    return true;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__host__ float computePi(int n)
    {
    float res = 0.0;
    float* ptrRes=&res;	// on host (CPU)
    float* ptrDevRes; 	// on device (GPU)
    // Specifier nb thread : ici 1 thread au total !
    dim3 dg = dim3(32,1,1);
    dim3 db = dim3(64,1,1);

    // Debug
     Device::checkDimError(dg,db);

    size_t size=sizeof(float);
    HANDLE_ERROR(cudaMalloc((void**) &ptrDevRes, size)); // Device memory allocation (*)
    HANDLE_ERROR(cudaMemset(ptrDevRes,0,size)) ;
    HANDLE_ERROR(cudaMemcpy(ptrRes, ptrDevRes, size, cudaMemcpyDeviceToHost));// Device -> Host
    int length = db.x;
    size_t sizeTabSM = sizeof(float)*length;
    assert((length&(length-1))==0&&"Whoops, length must be a power of two !");
    computePiGPU<<<dg,db,sizeTabSM>>>(n, ptrDevRes,length); // asynchrone !!
    Device::checkKernelError("computePiGPU"); // facultatif

    //v1
    Device::synchronize();// Pour printf sur  GPU

    //v2
   // cudaDeviceSynchronize(); // Pour printf sur  GPU

    // memoryManagement => barrier de synchronisation
    HANDLE_ERROR(cudaMemcpy(ptrRes, ptrDevRes, size, cudaMemcpyDeviceToHost));// Device -> Host
    HANDLE_ERROR(cudaFree(ptrDevRes)); // device dispose memory in (*)
    double DX = 1.0/(double)n;
    return res*DX;
    }



__global__ void computePiGPU(int n, float* ptrDevRes,int lenght)
    {

    //une instance par block
      //init tab
      const int TID_LOCAL = Indice1D::tidLocalBlock();
      extern __shared__ float tabSM[];

      //UtilsCUDA::initialise(tabSM,lenght); //pas vraiment utile ici mais a garder

      reduce_intra_thread(tabSM, n);
      __syncthreads;
      UtilsCUDA::reduce_intra_block(tabSM);
      UtilsCUDA::reduce_inter_block(tabSM,ptrDevRes);
  }

__device__ void reduce_intra_thread(float* tabSM, int n){
  const int NBTHREAD = Indice1D::nbThread();
      const int TID = Indice1D::tid();
      const int TID_LOCAL = Indice1D::tidLocalBlock();
      const double DX = 1.0/(double)n;

      int s = TID;
      float sumCurrentThread = 0.0;
      float xs = 0.0;
      while(s<n){
	  xs = s * DX;
          sumCurrentThread += fpi(xs);
          s+=NBTHREAD;
      }
      //printf("currentSum=%f PI=%f\n in reduce intrathread", sumCurrentThread,sumCurrentThread*DX);
      //cout<<"currentSum"<<sumCurrentThread<<endl;
      tabSM[TID_LOCAL] = sumCurrentThread;
}





  __device__ float fpi(float x)
      {
      return 4.0 / (1.0 + x * x);
      }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

