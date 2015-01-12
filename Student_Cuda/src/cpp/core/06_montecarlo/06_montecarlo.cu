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

__device__ float uniform( float min, float max, curandState& localState);
__device__ float f(float x);
__global__ void computeMontecarloGPU(float* ptrDevGM, int nTabSM, float xMin, float xMax, int m, long n, curandState* ptrDevRandom);
__device__ void reduce_intra_thread_montecarlo(float* tabSM, float xMin, float xMax, int m, long n, curandState* ptrDevRandom);
__host__ bool isMontecarlo_Ok(long n, float xMin, float xMax, int m);
__global__ void setup_kernel_rand_montecarlo(curandState* ptrDevTabGeneratorThread, int deviceId);


/*---------------------------------------------------------------------------*
 * Lancement
 *---------------------------------------------------------------------------*/

__host__ bool isMontecarlo_Ok(long n, float xMin, float xMax, int m) {
	printf("Montecarlo[n=%d, min=%f, max=%f, m=%d]\n", n, xMin, xMax, m);
	float resultHost = 0;
	float* ptrDevGM = NULL;
	size_t size = sizeof(float);
	int nThreadPerBlock = 4;
	size_t sizeTabSM = sizeof(float) * nThreadPerBlock;
	HANDLE_ERROR(cudaMalloc(&ptrDevGM, size));
	HANDLE_ERROR(cudaMemset(ptrDevGM, 0, size));

	dim3 dg(1, 1, 1); // TODO to optimize
	dim3 db(nThreadPerBlock, 1, 1); // TODO to optimize
	Device::checkDimError(dg, db);
	Device::checkDimOptimiser(dg, db);

	//init random generator
	curandState* ptrDevRandom;
	size_t sizeRandom = sizeof(curandState) * nThreadPerBlock;
	HANDLE_ERROR(cudaMalloc((void**) &ptrDevRandom, sizeRandom));
	HANDLE_ERROR(cudaMemset(ptrDevRandom, 0, sizeRandom));
	setup_kernel_rand_montecarlo<<<dg,db>>>(ptrDevRandom,Device::getDeviceId());
	Device::checkKernelError("setup_kernel_rand");

	computeMontecarloGPU<<<dg,db,sizeTabSM>>>(ptrDevGM, sizeTabSM, xMin, xMax, m, n, ptrDevRandom);
	Device::checkKernelError("computeMontecarloGPU");

	// Récupération du résultat
	HANDLE_ERROR(cudaMemcpy(&resultHost, ptrDevGM, size, cudaMemcpyDeviceToHost)); // barrière de synchronisation

	// Affichage du résultat
	printf("Montecarlo[n=%d, min=%f, max=%f, m=%d] = %f\n", n, xMin, xMax, m, resultHost);

	return true;
}



__device__ float uniform(const float MIN, const float MAX, curandState& localState) {
	float r = curand_uniform(&localState);
	return MIN + r * (MAX - MIN);
}

/*---------------------------------------------------------------------------*
 * Montecarlo
 *---------------------------------------------------------------------------*/

__device__ float f(float x) {
	return 0.3;
}

__global__ void computeMontecarloGPU(float* ptrDevGM, int nTabSM, float xMin, float xMax, int m, long n, curandState* ptrDevRandom){
	extern __shared__ float tabSM[];// 1 instance per block !
	const int TID = Indice1D::tid();
	UtilsCUDA::initialise(tabSM, nTabSM);

	__syncthreads();
	reduce_intra_thread_montecarlo(tabSM, xMin, xMax, m, n, ptrDevRandom);
	__syncthreads();
	UtilsCUDA::reduce_intra_block(tabSM);
	__syncthreads();
	UtilsCUDA::reduce_inter_block(tabSM, ptrDevGM);
	if(TID == 0) *ptrDevGM = *ptrDevGM / n * (xMax - xMin) * m;
}

__device__ void reduce_intra_thread_montecarlo(float* tabSM, float xMin, float xMax, int m, long n,
        curandState* tabGeneratorThread) {
	const int TID = Indice1D::tid();
	const int TID_LOCAL = Indice1D::tidLocal();
	const int NB_THREAD = Indice1D::nbThread();

	curandState localState = tabGeneratorThread[TID];
	float intraThreadSum = 0;
	int s = TID;
	while (s < n) {
		float xAlea = uniform(xMin, xMax, localState);
		float yAlea = uniform(0, m, localState);
		if (yAlea < f(xAlea)) intraThreadSum++;
		s += NB_THREAD;
	}
	tabSM[TID_LOCAL] = intraThreadSum;
}

/*
 * I have to used this hack to avoid multiple definition
 */
__global__ void setup_kernel_rand_montecarlo(curandState* ptrDevTabGeneratorThread, int deviceId)
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


