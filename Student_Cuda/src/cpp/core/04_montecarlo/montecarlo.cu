#include <stdio.h>
#include <limits.h>
#include "cudaTools.h"
#include "curand_kernel.h"
#include "Indice1D.h"
#include "Device.h"
#include "reduction.h"

// #define DEBUG 1

__device__ float uniform(const float MIN, const float MAX, curandState& localState);
__global__ void setup_kernel_rand(curandState* tabGeneratorThread, const int DEVICE_ID);
__device__ float f(float x);
__global__ void kernel(float* ptrDevGM, const int nTabSM, const float X_MIN, const float X_MAX, const int M, const unsigned long long N,
        curandState* tabGeneratorThread);
__device__ void reduceIntraThread(float* tabSM, const float X_MIN, const float X_MAX, const int M, const unsigned long long N, curandState* tabGeneratorThread);
__host__ bool useMontecarlo();

/*---------------------------------------------------------------------------*
 * Nombres aléatoires
 *---------------------------------------------------------------------------*/

__device__ float uniform(const float MIN, const float MAX, curandState& localState) {
	float r = curand_uniform(&localState);
	return MIN + r * (MAX - MIN);
}

__global__ void setup_kernel_rand(curandState* tabGeneratorThread, const int DEVICE_ID) {
	const int TID = Indice1D::tid();

	int deltaSeed = DEVICE_ID * INT_MAX;
	int deltaSequence = DEVICE_ID * 100;
	int deltaOffset = DEVICE_ID * 100;

	int seed = 1234 + deltaSeed;
	int sequenceNumber = TID + deltaSequence;
	int offset = deltaOffset;
	curand_init(seed, sequenceNumber, offset, &tabGeneratorThread[TID]);
}

/*---------------------------------------------------------------------------*
 * Montecarlo
 *---------------------------------------------------------------------------*/

__device__ float f(float x) {
	return 0.3;
}

__global__ void kernel(float* ptrDevGM, const int nTabSM, const float X_MIN, const float X_MAX, const int M, const unsigned long long N,
        curandState* tabGeneratorThread) {
	// @formatter:off
	extern __shared__ float tabSM[];// 1 instance per block !
	// @formatter:on

	// TID
	const int TID = Indice1D::tid();

	// Init
	initTabSM(tabSM, nTabSM, 0);
#ifdef DEBUG
	debugTabSM(tabSM, nTabSM, "After init");
#endif

	__syncthreads(); // TODO useless?

	// reduceIntraThread
	reduceIntraThread(tabSM, X_MIN, X_MAX, M, N, tabGeneratorThread);
#ifdef DEBUG
	debugTabSM(tabSM, nTabSM, "After reduceIntraThread");
#endif

	__syncthreads(); // TODO is really necessary ??

	// reduceIntraBlock
	reduceIntraBlock(tabSM, nTabSM);
#ifdef DEBUG
	debugTabSM(tabSM, nTabSM, "After reduceIntraBlock");
#endif

	__syncthreads(); // TODO is really necessary ??

	// reduceInterBlock
	reduceInterBlock(tabSM, ptrDevGM);
	if(TID == 0) {
		*ptrDevGM = *ptrDevGM / N * (X_MAX - X_MIN) * M;
	}
#ifdef DEBUG
	debugTabGM(ptrDevGM, 1, "Result");
#endif
}

__device__ void reduceIntraThread(float* tabSM, const float X_MIN, const float X_MAX, const int M, const unsigned long long N,
        curandState* tabGeneratorThread) {
	const int TID = Indice1D::tid();
	const int TID_LOCAL = Indice1D::tidLocal();
	const int NB_THREAD = Indice1D::nbThread();

	curandState localState = tabGeneratorThread[TID];
	float intraThreadSum = 0;
	int s = TID;
	while (s < N) {
		const float X_ALEA = uniform(X_MIN, X_MAX, localState);
		const float Y_ALEA = uniform(0, M, localState);
		if (Y_ALEA < f(X_ALEA)) {
			intraThreadSum++;
		}

		s += NB_THREAD;
	}
	tabSM[TID_LOCAL] = intraThreadSum;
}

/*---------------------------------------------------------------------------*
 * Lancement
 *---------------------------------------------------------------------------*/

__host__ bool useMontecarlo() {

	// Paramètres de l'algorithme
	const unsigned long long N = 5000000;
	const float X_MIN = 0;
	const float X_MAX = 2;
	const int M = 1;

	// résultat final en RAM
	float resultRAM = 0;

	// résultat final sur le GPU après réduction
	float* ptrDevGM = NULL;
	size_t size = sizeof(float);
	int nThreadPerBlock = 4;
	size_t sizeTabSM = sizeof(float) * nThreadPerBlock;
	HANDLE_ERROR(cudaMalloc(&ptrDevGM, size));
	HANDLE_ERROR(cudaMemset(ptrDevGM, 0, size));

	// Paramètres du GPU
	dim3 dg(1, 1, 1); // TODO to optimize
	dim3 db(nThreadPerBlock, 1, 1); // TODO to optimize
	Device::checkDimError(dg, db);
	Device::checkDimOptimiser(dg, db);
	const int DEVICE_ID = 1;

	// générateurs de nombres aléatoires sur le GPU
	curandState* ptrDevTabGeneratorThread = NULL;
	size_t sizeTabGeneratorThread = sizeof(curandState) * nThreadPerBlock;
	HANDLE_ERROR(cudaMalloc(&ptrDevTabGeneratorThread, sizeTabGeneratorThread));
	HANDLE_ERROR(cudaMemset(ptrDevTabGeneratorThread, 0, sizeTabGeneratorThread));

	// Lancement du kernel 1: initialisation des générateurs de nombres aléatoires
	setup_kernel_rand<<<dg,db,sizeTabSM>>>(ptrDevTabGeneratorThread, DEVICE_ID);
	Device::checkKernelError("Kernel error: setup_kernel_rand");

	// Lancement du kernel 2: calcul de montecarlo
	kernel<<<dg,db,sizeTabSM>>>(ptrDevGM, sizeTabSM, X_MIN, X_MAX, M, N, ptrDevTabGeneratorThread);
	Device::checkKernelError("Kernel error: montecarlo");

	// Récupération du résultat
	HANDLE_ERROR(cudaMemcpy(&resultRAM, ptrDevGM, size, cudaMemcpyDeviceToHost)); // barrière de synchronisation

	// Affichage du résultat
	printf("Montecarlo[n=%d, min=%f, max=%f, m=%d] = %f\n", N, X_MIN, X_MAX, M, resultRAM);

	return true;
}

