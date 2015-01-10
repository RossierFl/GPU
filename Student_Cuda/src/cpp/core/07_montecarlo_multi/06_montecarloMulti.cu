//#include <curandTools.h>
#include <iostream>
#include <stdio.h>
#include "cudaTools.h"
#include "Device.h"
#include "Indice1D.h"
#include <assert.h>
#include <math.h>
#include <limits.h>

#include <curand_kernel.h>
#include "UtilsCuda.h"
#include <omp.h>

__device__ float uniformMulti( float min, float max, curandState& localState);
__device__ float fMulti(float x);
__global__ void computeMontecarloGPUMulti(float* ptrDevGM, int nTabSM, float xMin, float xMax, int m, long n, curandState* ptrDevRandom);
__device__ void reduce_intra_thread_montecarloMulti(float* tabSM, float xMin, float xMax, int m, long n, curandState* ptrDevRandom);
__host__ bool isMontecarlo_OkMulti(long n, float xMin, float xMax, int m);
__global__ void setup_kernel_rand_montecarloMulti(curandState* ptrDevTabGeneratorThread, int deviceId);


/*---------------------------------------------------------------------------*
 * Lancement
 *---------------------------------------------------------------------------*/

__host__ bool isMontecarloMulti_Ok(long n, float xMin, float xMax, int m) {
	printf("MontecarloMulti[n=%d, min=%f, max=%f, m=%d]\n", n, xMin, xMax, m);
	float* resultHost = new float[6];
	assert(n%6==0);//could be more generic
	int nbNPerGPU = n/6;
	int nThreadPerBlock = 4;
	dim3 dg(1, 1, 1); // TODO to optimize
	dim3 db(nThreadPerBlock, 1, 1); // TODO to optimize
	Device::checkDimError(dg, db);
	Device::checkDimOptimiser(dg, db);

	Device::checkKernelError("setup_kernel_rand_montecarloMulti");
	int nbGPU = 6; //could be more generic
	omp_set_num_threads(nbGPU);
#pragma omp parralel for
	for(int i=0;i<nbGPU;i++)
	  {
	    cudaSetDevice(i);
	   // printf("i:%d\n",i);

	    //init random generator
	    curandState* ptrDevRandom;
	    size_t sizeRandom = sizeof(curandState) * nThreadPerBlock;
	    HANDLE_ERROR(cudaMalloc((void**) &ptrDevRandom, sizeRandom));
	    HANDLE_ERROR(cudaMemset(ptrDevRandom, 0, sizeRandom));
	    setup_kernel_rand_montecarloMulti<<<dg,db>>>(ptrDevRandom,Device::getDeviceId());

	    float* ptrDevGM = NULL;
	    size_t size = sizeof(float);
	    size_t sizeTabSM = sizeof(float) * nThreadPerBlock;
	    HANDLE_ERROR(cudaMalloc(&ptrDevGM, size));
	    HANDLE_ERROR(cudaMemset(ptrDevGM, 0, size));

	    computeMontecarloGPUMulti<<<dg,db,sizeTabSM>>>(ptrDevGM, sizeTabSM, xMin, xMax, m, nbNPerGPU, ptrDevRandom);
	    Device::checkKernelError("computeMontecarloGPUMulti");

	    // Récupération du résultat
	    HANDLE_ERROR(cudaMemcpy(&resultHost[i], ptrDevGM, size, cudaMemcpyDeviceToHost)); // barrière de synchronisation
	  }
	float result = 0.0;
	for(int i=0;i<nbGPU;i++)//could be more generic
	  {
	      result += resultHost[i];
	  }
	result /= nbGPU;


	// Affichage du résultat
	printf("MontecarloMulti[n=%d, min=%f, max=%f, m=%d] = %f\n", n, xMin, xMax, m, result);

	return true;
}



__device__ float uniformMulti(const float MIN, const float MAX, curandState& localState) {
	float r = curand_uniform(&localState);
	return MIN + r * (MAX - MIN);
}

/*---------------------------------------------------------------------------*
 * Montecarlo
 *---------------------------------------------------------------------------*/

__device__ float fMulti(float x) {
	return 0.3;
}

__global__ void computeMontecarloGPUMulti(float* ptrDevGM, int nTabSM, float xMin, float xMax, int m, long n, curandState* ptrDevRandom){
	extern __shared__ float tabSM[];// 1 instance per block !
	const int TID = Indice1D::tid();
	UtilsCUDA::initialise(tabSM, nTabSM);

	__syncthreads();
	reduce_intra_thread_montecarloMulti(tabSM, xMin, xMax, m, n, ptrDevRandom);
	__syncthreads();
	UtilsCUDA::reduce_intra_block(tabSM);
	__syncthreads();
	UtilsCUDA::reduce_inter_block(tabSM, ptrDevGM);
	if(TID == 0) *ptrDevGM = *ptrDevGM / n * (xMax - xMin) * m;
}

__device__ void reduce_intra_thread_montecarloMulti(float* tabSM, float xMin, float xMax, int m, long n,
        curandState* tabGeneratorThread) {
	const int TID = Indice1D::tid();
	const int TID_LOCAL = Indice1D::tidLocal();
	const int NB_THREAD = Indice1D::nbThread();

	curandState localState = tabGeneratorThread[TID];
	float intraThreadSum = 0;
	int s = TID;
	while (s < n) {
		float xAlea = uniformMulti(xMin, xMax, localState);
		float yAlea = uniformMulti(0, m, localState);
		if (yAlea < fMulti(xAlea)) intraThreadSum++;
		s += NB_THREAD;
	}
	tabSM[TID_LOCAL] = intraThreadSum;
}

/*
 * I have to used this hack to avoid multiple definition
 */
__global__ void setup_kernel_rand_montecarloMulti(curandState* ptrDevTabGeneratorThread, int deviceId)
    {
    int tid = Indice1D::tid();

    // Customisation du generator: Proposition (au lecteur de faire mieux)
    // Contrainte : Doit etre diff�rent d'un GPU � l'autre
    int deltaSeed = deviceId * INT_MAX;
    int deltaSequence = deviceId * 100;
    int deltaOffset = deviceId * 100;

    int seed = 1234 + deltaSeed;    // deviceId+tid;
    int sequenceNumber = tid + deltaSequence;    // + tid;
    int offset = deltaOffset;

    //Each thread gets same seed , a different sequence number , no offset
    curand_init(seed, sequenceNumber, offset, &ptrDevTabGeneratorThread[tid]);
    }


