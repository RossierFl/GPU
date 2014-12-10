#include "Indice1D.h"
#include "cudaTools.h"
#include "ProduitScalaireDevice.h"
#include "Lock.h"
#include <iostream>
#include "Device.h"
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
#define M_W 50
#define M_V 50
#define VI 1.442249570307408
#define WI 0.7390851332151607

__device__ int mutex=0;
static __global__ void calculeProduitScalaire(int n,int nTabSM,double* ptrDevResult);
/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/


static __device__ double w(long i){
    double x = abs(cos((double)i));
    for(long j =1;j<=M_W;j++){
	x=x-(cos(x)-x)/(-sin(x)-1);

    }
    return (x/WI)*sqrt((double)i);
   // return sqrt((double)i);

}


static __device__ double v(long i){
    double x =1.5 + abs(cos((double) i));
    for(long j = 1;j < M_V;j++){
	double xCarre=x*x;
	x = x-(xCarre * x-3)/(3*xCarre);
    }
    return (x/VI)*sqrt((double) i);
  //  return sqrt((double) i);
}


static __device__ void ecrasement(double * tabSM,int moitier){

    const int NBR_THREAD = Indice1D::nbThreadBlock();
    const int TID_LOCAL = Indice1D::tidLocalBlock();
    int saut = moitier;
    int s = TID_LOCAL;
    while(s<moitier){
	tabSM[s]+=tabSM[s+saut];
	s+=NBR_THREAD;

    }


}




static __device__ void reduction_intra_block(double * tabSM,int n){
    const int NBR_THREAD = Indice1D::nbThread();

            int moitier = n/2;

            while(moitier>=1){
        	ecrasement(tabSM,moitier);

                moitier/=2;
                __syncthreads;//Faire attention
            }




}

static __device__ void reduction_inter_block(double * tabSM,double * ptrDevResult){
    const int TID_LOCAL = Indice1D::tidLocalBlock();
    if(threadIdx.x==0){
	Lock lock(&mutex);
	lock.lock();
	*ptrDevResult+=tabSM[0];
	//atomicAdd(ptrDevResult,tabSM[0]);
	lock.unlock();

    }

}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/
static __device__ float prodScalaire(long i)
    {
	return w(i)*v(i);
    }

static __device__ void reduction_intra_thread(double * tabSM,long vectorLenght){
    //Executer par thread
       const int NBR_THREAD = Indice1D::nbThread();
       const int NBR_THREAD_LOCAL = Indice1D::nbThreadBlock();
           const int TID = Indice1D::tid();
           const int TID_LOCAL = Indice1D::tidLocalBlock();
           long s = TID;
           double sommeThread=0;
           while(s<vectorLenght){

               sommeThread+=prodScalaire(s);
               s+=NBR_THREAD;

           }


           tabSM[TID_LOCAL]=sommeThread;
           __syncthreads;
}
__device__ static void init_tabSM(double * tabSM,int nTabSM){
    const int NB_THREAD_LOCAL = Indice1D::nbThreadBlock();
    int s = Indice1D::tidLocal();
    while(s<nTabSM){
	 tabSM[s]=0;//TID local
	 s+=NB_THREAD_LOCAL;
    }

    __syncthreads;


}

static __global__ void calculeProduitScalaire(int n, int nTabSM,double* ptrDevResult){
   //Une instance par bloc
     extern __shared__ double tabSM[];

    init_tabSM(tabSM,nTabSM);
    reduction_intra_thread(tabSM,n);
    reduction_intra_block(tabSM,nTabSM);
    reduction_inter_block(tabSM,ptrDevResult);


}


 void ProduitScalaireDevice::runProduitScalaire(int n,int  nTabSM,double * ptrDevResult,dim3 dg,dim3 db){
     size_t size = nTabSM*sizeof(double);
     calculeProduitScalaire<<<dg,db,size>>>(n,nTabSM,ptrDevResult);//asynchronous
     Device::checkKernelError("calculeProduitScalaire");

}

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

