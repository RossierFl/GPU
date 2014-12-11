#include "Indice1D.h"
#include "Indice2D.h"
#include "cudaTools.h"
#include "HistogrammeDevice.h"
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
static __global__ void calculeHistogramme(int n,int nTabSM,int* ptrDevResult);
/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/





static __device__ void ecrasement(int * tabSM,int moitier){

    const int NBR_THREAD = Indice1D::nbThreadBlock();
    const int TID_LOCAL = Indice1D::tidLocalBlock();
    int saut = moitier;
    int s = TID_LOCAL;
    while(s<moitier){
	tabSM[s]+=tabSM[s+saut];
	s+=NBR_THREAD;

    }


}




static __device__ void reduction_intra_block(int * tabSM,int n){
    const int NBR_THREAD = Indice1D::nbThread();

            int moitier = n/2;

            while(moitier>=1){
        	ecrasement(tabSM,moitier);

                moitier/=2;
                __syncthreads;//Faire attention
            }




}

static __device__ void reduction_inter_block(int * tabSM,int * ptrDevResult,int nTabSM){
    const int TID_LOCAL = Indice1D::tidLocalBlock();
    const int NBR_THREAD_LOCAL = Indice1D::nbThreadBlock();
    int s = TID_LOCAL;

    while(s<nTabSM){
	//Lock lock(&mutex);
	//lock.lock();
	//*ptrDevResult+=tabSM[0];
	atomicAdd(&ptrDevResult[s],tabSM[s]);
	s+=NBR_THREAD_LOCAL;
	//lock.unlock();

    }

}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/


static __device__ void reduction_intra_thread(int * tabSM,int nTabSM,int * tabEntrees,int nTabEntrees){
    //Executer par thread
       const int NBR_THREAD = Indice2D::nbThread();
       //const int NBR_THREAD_LOCAL = Indice1D::nbThreadBlock();
           const int TID = Indice2D::tid();
          // const int TID_LOCAL = Ind::tidLocalBlock();
           long s = TID;
     //      float sommeThread=0;
           while(s<nTabEntrees){

             //  sommeThread+=prodScalaire(s);
              atomicAdd(&tabSM[tabEntrees[s]],1);

               s+=NBR_THREAD;

           }


           //tabSM[TID_LOCAL]=sommeThread;
           __syncthreads;
}
__device__ static void init_tabSM(int * tabSM,int nTabSM){
    const int NB_THREAD_LOCAL = Indice1D::nbThreadBlock();
    int s = Indice1D::tidLocal();
    while(s<nTabSM){
	 tabSM[s]=0;//TID local
	 s+=NB_THREAD_LOCAL;
    }

    __syncthreads;


}

static __global__ void calculeHistogramme(int nEntrees, int nTabSM,int* ptrDevResult,int * tabEntrees){
   //Une instance par bloc
     extern __shared__ int tabSM[];

    init_tabSM(tabSM,nTabSM);
    reduction_intra_thread(tabSM,nTabSM,tabEntrees,nEntrees);
    //reduction_intra_block(tabSM,nTabSM);
    reduction_inter_block(tabSM,ptrDevResult,nTabSM);


}


 void HistogrammeDevice::runHistogramme(int nEntrees,int  nTabSM,int * ptrDevResult,int * tabEntrees,dim3 dg,dim3 db){
     size_t size = nTabSM*sizeof(int);
     calculeHistogramme<<<dg,db,size>>>(nEntrees,nTabSM,ptrDevResult,tabEntrees);//asynchronous
     Device::checkKernelError("calculeHistogramme");

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

