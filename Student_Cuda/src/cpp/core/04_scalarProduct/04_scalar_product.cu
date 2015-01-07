// Attention : Extension .cu

#include <iostream>
#include <stdio.h>
#include "cudaTools.h"
#include "Device.h"
#include "Indice1D.h"
#include "UtilsCuda.h"
#include <assert.h>
#include <math.h>

using std::cout;
using std::endl;

#define M_W 100
#define M_V 100
//#define VI 1.4422495703074083
#define VI 1.4422495703074083017725115
//#define WI 0.7390850782394409
#define WI 0.7390851332151606722931092

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__host__  bool isScalarProduct_Ok(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__host__  static double computeScalarProduct(int n);
__host__ double theoricalResult(int n);
__global__ static void computeScalarProductGPU(int n,double* ptrDevResult, int lenght);
__device__ void reduce_intra_thread_scalar_product(double* tabSM, int n);
__device__ double v(int i);
__device__ double w(int i);


/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__host__  bool isScalarProduct_Ok(int n)
    {
    cout << endl << "[ScalarProduct Cuda 2]" << endl;


    double scalarProductGPU = computeScalarProduct(n);

    //cout <<"\n[GPUPI] "<< sumPiGPU << endl;
    printf("[GPU_SCALAR_PRODUCT] %f\n",scalarProductGPU);

    return true;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__host__ double computeScalarProduct(int n)
    {
    double res = 0.0;
    double* ptrRes=&res;	// on host (CPU)
    double* ptrDevRes; 	// on device (GPU)
    // Specifier nb thread : ici 1 thread au total !
    dim3 dg = dim3(16,1,1);
    dim3 db = dim3(32,1,1);

    // Debug
     Device::checkDimError(dg,db);

    size_t size=sizeof(double);
    HANDLE_ERROR(cudaMalloc((void**) &ptrDevRes, size)); // Device memory allocation (*)
    HANDLE_ERROR(cudaMemset(ptrDevRes,0,size)) ;
    HANDLE_ERROR(cudaMemcpy(ptrRes, ptrDevRes, size, cudaMemcpyDeviceToHost));// Device -> Host
    int length = db.x;
    size_t sizeTabSM = sizeof(double)*length;
    assert((length&(length-1))==0&&"Whoops, length must be a power of two !");
    computeScalarProductGPU<<<dg,db,sizeTabSM>>>(n, ptrDevRes,length); // asynchrone !!
    Device::checkKernelError("computeScalarProductGPU"); // facultatif

    //v1
    Device::synchronize();// Pour printf sur  GPU

    // memoryManagement => barrier de synchronisation
    HANDLE_ERROR(cudaMemcpy(ptrRes, ptrDevRes, size, cudaMemcpyDeviceToHost));// Device -> Host
    HANDLE_ERROR(cudaFree(ptrDevRes)); // device dispose memory in (*)
    printf("Result GPU = %f and theorical result is %f\n",res,theoricalResult(n));
    return res;
    }

__host__ double theoricalResult(int n){
    n--;
    return (n/(double)2)*(n+1);
}



__global__ void computeScalarProductGPU(int n, double* ptrDevRes,int lenght)
    {

    //une instance par block
      //init tab
      const int TID_LOCAL = Indice1D::tidLocalBlock();
      extern __shared__ double tabSM[];
      UtilsCUDA::initialise(tabSM,lenght);


      reduce_intra_thread_scalar_product(tabSM, n);
      UtilsCUDA::reduce_intra_block(tabSM);
      UtilsCUDA::reduce_inter_block(tabSM,ptrDevRes);
  }

__device__ void reduce_intra_thread_scalar_product(double* tabSM, int n){
  const int NBTHREAD = Indice1D::nbThread();
      const int TID = Indice1D::tid();
      const int TID_LOCAL = Indice1D::tidLocalBlock();

      int s = TID;
      double sumCurrentThread = 0.0;
      while(s<n){
          sumCurrentThread += v(s)*w(s);
          s+=NBTHREAD;
      }
      //printf("currentSum=%f PI=%f\n in reduce intrathread", sumCurrentThread,sumCurrentThread*DX);
      //cout<<"currentSum"<<sumCurrentThread<<endl;
      tabSM[TID_LOCAL] = sumCurrentThread;
}


__device__ double v(int i){
    const int TID = Indice1D::tid();
    double x = 1.5+abs(cos((double)i));

    for(int j = 1; j<=M_V; j++){
	double xCarre=x*x;
	x = x-(xCarre * x -3)/(3*xCarre);
    }
    //if(TID==0)printf("xv = %.25f",x);
    return (x/VI)*sqrt((double)i);

}

__device__ double w(int i){
  const int TID = Indice1D::tid();
    double x = abs(cos((double)i));
    for(int j = 1; j<=M_W;j++){
	x = x-(cos(x)-x)/(-sin(x)-1);
    }
    //if(TID==0)printf("xw = %.25f",x);
    return (x/WI)*sqrt((double)i);
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

