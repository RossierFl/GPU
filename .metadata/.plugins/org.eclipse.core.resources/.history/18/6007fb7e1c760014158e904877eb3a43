#include "Indice1D.h"
#include "cudaTools.h"
#include "PiDevice.h"
#include <iostream>
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

static __global__ void calculPi(int n,int nTabSM,float* ptrDevResult);
/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/



static __device__ void ecrasement(float * tabSM,int moitier){

    const int NBR_THREAD = Indice1D::nbThreadBlock();
    const int TID_LOCAL = Indice1D::tidLocalBlock();
    int saut = moitier;
    int s = TID_LOCAL;
    while(s<moitier){
	tabSM[s]+=tabSM[s+saut];
	s+=NBR_THREAD;

    }


}




static __device__ void reduction_intra_block(float * tabSM,int n){
    const int NBR_THREAD = Indice1D::nbThread();
           // const int TID = Indice1D::tid();
           // const int TID_LOCAL = Indice1D::tidLocalBlock();
            int moitier = n/2;
            //int s = TID_LOCAL;
          //  float sommeThread=0;
            while(moitier>=1){
        	ecrasement(tabSM,moitier);
               // s+=NBR_THREAD;
                moitier/=2;
                __syncthreads;//Faire attention
            }




}

static __device__ void reduction_inter_block(float * tabSM,float * ptrDevResult){
    const int TID_LOCAL = Indice1D::tidLocalBlock();
    if(threadIdx.x==0){
	//ptrDevResult[TID_LOCAL]=tabSM[0];
	atomicAdd(ptrDevResult,tabSM[0]);
	//atomicAdd(ptrDevResult,4);
    }

}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/
static __device__ float fpi(float x)
    {
    return 4 / (1 + x * x);
    }

static __device__ void reduction_intra_thread(float * tabSM,int nSausisson){
    //Executer par thread
       const int NBR_THREAD = Indice1D::nbThread();
       const int NBR_THREAD_LOCAL = Indice1D::nbThreadBlock();
           const int TID = Indice1D::tid();
           const int TID_LOCAL = Indice1D::tidLocalBlock();
           const float DX = 1.0/(float)nSausisson;
           float xs=0;
           int s = TID;
           float sommeThread=0;
           while(s<nSausisson){
               xs= s*DX;
               sommeThread+=fpi(xs);
               s+=NBR_THREAD;

           }
           sommeThread*=DX;

           tabSM[TID_LOCAL]=sommeThread;
           __syncthreads;
}
__device__ static void init_tabSM(float * tabSM,int nTabSM){
    const int NB_THREAD_LOCAL = Indice1D::nbThreadBlock();
    int s = Indice1D::tidLocal();
    while(s<nTabSM){
	 tabSM[s]=0;//TID local
	 s+=NB_THREAD_LOCAL;
    }

    __syncthreads;


}

static __global__ void calculPi(int n, int nTabSM,float* ptrDevResult){
   //Une instance par bloc
     extern __shared__ float tabSM[];

    init_tabSM(tabSM,nTabSM);
    reduction_intra_thread(tabSM,n);
    reduction_intra_block(tabSM,nTabSM);
    reduction_inter_block(tabSM,ptrDevResult);


}


 void PiDevice::runPi(int n,int  nTabSM,float * ptrDevResult,dim3 dg,dim3 db){

    calculPi<<<dg,db,nTabSM>>>(n,nTabSM,ptrDevResult);//asynchronous

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

