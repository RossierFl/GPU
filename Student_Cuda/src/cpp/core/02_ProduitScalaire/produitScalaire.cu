#include <assert.h>
#include <cstdio>

#include "cuda_utils.h"
#include "cudaTools.h"
#include "Device.h"
#include "Indice1D.h"

#define M_W 100
#define M_V 100
#define VI 1.4422495703074083017725115
#define WI 0.7390851332151606722931092

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__host__ bool isProduitScalaire_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__host__ static double computeProduitScalaire(int n);
__host__ double result(int n);
__global__ static void computeProduitScalaireGPU(int n,double* ptrDevResult, int length);
__device__ void reduceIntraThreadProduitScalaire(double* tabSM, int n);
__device__ double v(int i);
__device__ double w(int i);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__host__ bool isProduitScalaire_Ok(int n)
    {
    cout << endl << "[Produit Scalaire Cuda]" << endl;
    double scalarProductGPU = computeProduitScalaire(n);
    printf("[GPU PRODUIT SCALAIRE] : %f\n",scalarProductGPU);
    return true;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__host__ double computeProduitScalaire(int n)
    {
    double res = 0.0;
    double* ptrHostRes=&res;
    double* ptrDevRes;

    dim3 dg = dim3(16,1,1); // block
    dim3 db = dim3(32,1,1); // thread/block

    Device::checkDimError(dg,db);
    size_t size=sizeof(double);
    HANDLE_ERROR(cudaMalloc((void**) &ptrDevRes, size));
    HANDLE_ERROR(cudaMemset(ptrDevRes,0,size)) ;
    HANDLE_ERROR(cudaMemcpy(ptrHostRes, ptrDevRes, size, cudaMemcpyDeviceToHost));// Device -> Host
    int length = db.x;
    size_t sizeTabSM = sizeof(double)*length;

    computeProduitScalaireGPU<<<dg,db,sizeTabSM>>>(n, ptrDevRes,length);
    Device::checkKernelError("computeScalarProductGPU");
    //v1
    Device::synchronize();
    HANDLE_ERROR(cudaMemcpy(ptrHostRes, ptrDevRes, size, cudaMemcpyDeviceToHost));// Device -> Host
    HANDLE_ERROR(cudaFree(ptrDevRes));
    printf("Result GPU = %f\n",res);
    printf("Expected result is: %f\n",result(n));
    return res;
    }

__host__ double result(int n)
    {
    n--;
    return (n/2.0)*(n+1);
    }

__global__ void computeProduitScalaireGPU(int n, double* ptrDevResult,int length)
    {
    const int TID_LOCAL = Indice1D::tidLocalBlock();
    extern __shared__ double tabSM[];
    CUDAUtils::initialize(tabSM,length);
    reduceIntraThreadProduitScalaire(tabSM, n);
    CUDAUtils::reduceIntraBlock(tabSM);
    CUDAUtils::reduceInterBlock(tabSM,ptrDevResult);
    }

// add suffix to avoid multiple definition error
__device__ void reduceIntraThreadProduitScalaire(double* tabSM, int n)
    {
    const int NBTHREAD = Indice1D::nbThread();
    const int TID = Indice1D::tid();
    const int TID_LOCAL = Indice1D::tidLocalBlock();
    int s = TID;
    double sumCurrentThread = 0.0;
    while(s<n){
	sumCurrentThread += v(s)*w(s);
	s+=NBTHREAD;
    }

    tabSM[TID_LOCAL] = sumCurrentThread;
    }

__device__ double v(int i)
    {
    const int TID = Indice1D::tid();
    double x = 1.5+abs(cos((double)i));
    for(int j = 1; j<=M_V; j++){
	double xCarre=x*x;
	x = x-(xCarre * x -3)/(3*xCarre);
    }

    return (x/VI)*sqrt((double)i);
    }

__device__ double w(int i)
    {
    const int TID = Indice1D::tid();
    double x = abs(cos((double)i));
    for(int j = 1; j<=M_W;j++)
	{
	x = x-(cos(x)-x)/(-sin(x)-1);
	}

    return (x/WI)*sqrt((double)i);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

