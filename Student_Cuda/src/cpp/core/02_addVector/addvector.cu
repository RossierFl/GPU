#include "Indice2D.h"
#include "cudaTools.h"
#include <stdio.h>
#include "Device.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/
static __global__ void add(float* ptrDevV1,float* ptrDevV2, int n, float* ptrDevResult);
static __device__ float work(float v1,float v2);
void fillArray(float* tab,int n,int power);
/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void use(){
  int n = 3;
  float v1[n];
  fillArray(v1,n,1);
  float v2[n];
  fillArray(v2,n,2);

  float vResult[3];
  float* ptrDevV1 = NULL;
  float* ptrDevV2 = NULL;
  float* ptrDevResult =NULL;
  size_t size = 3*sizeof(float);
  HANDLE_ERROR(cudaMalloc(&ptrDevV1,size));
  HANDLE_ERROR(cudaMalloc(&ptrDevV2,size));
  HANDLE_ERROR(cudaMalloc(&ptrDevResult,size));

  HANDLE_ERROR(cudaMemset(ptrDevV1,0,size));
  HANDLE_ERROR(cudaMemset(ptrDevV2,0,size));
  HANDLE_ERROR(cudaMemset(ptrDevResult,0,size));
  //memcpy(src,dst,size,flag-copy)
  HANDLE_ERROR(cudaMemcpy(ptrDevV1,v1,size,cudaMemcpyHostToDevice));
  HANDLE_ERROR(cudaMemcpy(ptrDevV2,v2,size,cudaMemcpyHostToDevice));


  dim3 dg = dim3(2,2,1);
  dim3 db = dim3(2,2,1);
  add<<<dg,db>>>(ptrDevV1,ptrDevV2,3,ptrDevResult);//asynchrone
  HANDLE_ERROR(cudaMemcpy(vResult,ptrDevResult,size,cudaMemcpyDeviceToHost)); //cudaMemcpy = barrière de synchronisation
  Device::checkKernelError("addvector");
  printf("%f,%f,%f",vResult[0],vResult[1],vResult[2]);
}

void fillArray(float* tab,int n,int power){
  for(int i=1;i<n+1;i++){
      tab[i]=i*power;
  }
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__global__ void add(float* ptrDevV1,float* ptrDevV2, int n, float* ptrDevResult)
{
  const int NBTHREAD = Indice2D::nbThread();
  const int TID = Indice2D::tid();

  int s = TID;

  while(s<n){
      ptrDevResult[s] = work(ptrDevV1[s],ptrDevV2[s]);
      s+=NBTHREAD;
  }
}

__device__ float work(float v1,float v2){
    return v1+v2;
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

