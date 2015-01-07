#ifndef UTILSCUDA_H_
#define UTILSCUDA_H_

#include <iostream>
#include "Lock.h"
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Dans un header only pour preparer la version cuda
 */
__device__ int mutex=0;
class UtilsCUDA
    {
	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

  __device__ UtilsCUDA(){}

  __device__ ~UtilsCUDA(void){}



	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	__device__ static void initialise(float* tabSM, int length){
	      const int NBTHREAD_BLOCK = Indice1D::nbThreadBlock();
	      const int TID_LOCAL = Indice1D::tidLocal();
		int s = TID_LOCAL;
		while(s<length){
		    tabSM[s] = 0.0;
		    s+=NBTHREAD_BLOCK;
		}
		__syncthreads();
	}

	__device__ static void initialise(double* tabSM, int length){
		      const int NBTHREAD_BLOCK = Indice1D::nbThreadBlock();
		      const int TID_LOCAL = Indice1D::tidLocal();
			int s = TID_LOCAL;
			while(s<length){
			    tabSM[s] = 0.0;
			    s+=NBTHREAD_BLOCK;
			}
			__syncthreads();
		}

      __device__ static void reduce_inter_block(float* tabSM, float* ptrDevResult){
	  const int TID_LOCAL = Indice1D::tidLocalBlock();
	  if(TID_LOCAL==0){
	    atomicAdd(ptrDevResult,tabSM[0]);
	  }

      }

      __device__ static void reduce_inter_block(double* tabSM, double* ptrDevResult){
     	  const int TID_LOCAL = Indice1D::tidLocalBlock();
     	  if(TID_LOCAL==0){
     	      Lock lock=Lock(&mutex);
     	    lock.lock();
     	    *ptrDevResult += tabSM[0];
     	    //atomicAdd(ptrDevResult,tabSM[0]);
     	    lock.unlock();
     	  }

           }

      __device__ static void reduce_intra_block(float* tabSM){

	  const int NBTHREAD = Indice1D::nbThread();
	  const int NBTHREADBLOCK=Indice1D::nbThreadBlock();
	  int half = NBTHREADBLOCK/2;
	  while(half>=1){
	    ecrasement(tabSM,half);
	    __syncthreads();
	    half/=2;
	  }

      }

      __device__ static void reduce_intra_block(double* tabSM){

      	  const int NBTHREAD = Indice1D::nbThread();
      	  const int NBTHREADBLOCK=Indice1D::nbThreadBlock();
      	  int half = NBTHREADBLOCK/2;
      	  while(half>=1){
      	    ecrasement(tabSM,half);
      	    __syncthreads();
      	    half/=2;
      	  }

            }

      __device__ static void ecrasement(float* tabSM, int half){
	  const int TID_LOCAL = Indice1D::tidLocalBlock();
	  const int NB_THREAD_BLOCK = Indice1D::nbThreadBlock();
	  int s = TID_LOCAL;
	  while(s<half){
	    tabSM[s] += tabSM[s+half];
	    s+=NB_THREAD_BLOCK;
	  }
      }

      __device__ static void ecrasement(double* tabSM, int half){
      	  const int TID_LOCAL = Indice1D::tidLocalBlock();
      	  const int NB_THREAD_BLOCK = Indice1D::nbThreadBlock();
      	  int s = TID_LOCAL;
      	  while(s<half){
      	    tabSM[s] += tabSM[s+half];
      	    s+=NB_THREAD_BLOCK;
      	  }
       }

    }
;

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
