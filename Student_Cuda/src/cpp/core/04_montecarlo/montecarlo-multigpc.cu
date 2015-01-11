#include <stdio.h>
#include <limits.h>
#include "cudaTools.h"
#include "curand_kernel.h"
#include "Indice1D.h"
#include "Device.h"
#include "reduction.h"

// #define DEBUG 1

static __device__ float uniform(const float MIN, const float MAX, curandState& localState);
static __global__ void setup_kernel_rand(curandState* tabGeneratorThread, const int DEVICE_ID);
static __device__ float f(float x);
static __global__ void kernel(float* ptrDevGM, const int nTabSM, const float X_MIN, const float X_MAX, const int M, const unsigned long N,
        curandState* tabGeneratorThread);
static __device__ void reduceIntraThread(float* tabSM, const float X_MIN, const float X_MAX, const int M, const unsigned long N, curandState* tabGeneratorThread);
__host__ bool useMontecarloMultiGPU();

/*---------------------------------------------------------------------------*
 * Nombres al������atoires
 *---------------------------------------------------------------------------*/

static __device__ float uniform(const float MIN, const float MAX, curandState& localState) {
	float r = curand_uniform(&localState);
	return MIN + r * (MAX - MIN);
}

static __global__ void setup_kernel_rand(curandState* tabGeneratorThread, const int DEVICE_ID) {
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

static __device__ float f(float x) {
	return 0.3;
}

static __global__ void kernel(float* ptrDevGM, const int nTabSM, const float X_MIN, const float X_MAX, const int M, const unsigned long N,
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
#ifdef DEBUG
	debugTabGM(ptrDevGM, 1, "Result");
#endif
}

static __device__ void reduceIntraThread(float* tabSM, const float X_MIN, const float X_MAX, const int M, const unsigned long N,
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

static __host__ float runOnDevice(const uint DEVICE, const unsigned long N, const float X_MIN, const float X_MAX, const int M, const uint N_THREAD_PER_BLOCK) {
	// Use GPU
	cudaSetDevice(DEVICE);

	// r��sultat final en RAM
	float resultRAM = 0;

	// r��sultat final sur le GPU apr��s r��duction
	float* ptrDevGM = NULL;
	size_t size = sizeof(float);
	size_t sizeTabSM = sizeof(float) * N_THREAD_PER_BLOCK;
	HANDLE_ERROR(cudaMalloc(&ptrDevGM, size));
	HANDLE_ERROR(cudaMemset(ptrDevGM, 0, size));

	// Param��tres du GPU
	dim3 dg(1, 1, 1); // TODO to optimize
	dim3 db(N_THREAD_PER_BLOCK, 1, 1); // TODO to optimize
#ifdef DEBUG
	Device::checkDimError(dg, db);
	Device::checkDimOptimiser(dg, db);
#endif

	// G��n��rateurs de nombres al��atoires sur le GPU
	curandState* ptrDevTabGeneratorThread = NULL;
	size_t sizeTabGeneratorThread = sizeof(curandState) * N_THREAD_PER_BLOCK;
	HANDLE_ERROR(cudaMalloc(&ptrDevTabGeneratorThread, sizeTabGeneratorThread));
	HANDLE_ERROR(cudaMemset(ptrDevTabGeneratorThread, 0, sizeTabGeneratorThread));

	// Lancement du kernel 1: initialisation des g��n��rateurs de nombres al��atoires
	setup_kernel_rand<<<dg,db,sizeTabSM>>>(ptrDevTabGeneratorThread, DEVICE);
	Device::checkKernelError("Kernel error: setup_kernel_rand");
	Device::synchronize();

	// Lancement du kernel 2: calcul de montecarlo
	kernel<<<dg,db,sizeTabSM>>>(ptrDevGM, sizeTabSM, X_MIN, X_MAX, M, N, ptrDevTabGeneratorThread);
	Device::checkKernelError("Kernel error: montecarlo");
	Device::synchronize();

	// R��cup��ration du r��sultat
	HANDLE_ERROR(cudaMemcpy(&resultRAM, ptrDevGM, size, cudaMemcpyDeviceToHost)); // barri��re de synchronisation

	// Lib��ration de la m��moire
	cudaFree(ptrDevGM);

	return resultRAM;
}

__host__ bool useMontecarloMultiGPU() {
	// Parametres de l'algorithme
	const uint NB_GPU = Device::getDeviceCount();
	unsigned long N = 5000000;
	const unsigned long N_PER_GPU = N / NB_GPU;
	const float X_MIN = 0;
	const float X_MAX = 2;
	const int M = 1;
	const uint N_THREAD_PER_BLOCK = 1;

	double sum = 0;

#pragma omp parallel for reduction(+:sum)
	for(uint device = 0; device < NB_GPU; device++) {
		sum += runOnDevice(device, N_PER_GPU, X_MIN, X_MAX, M, N_THREAD_PER_BLOCK);
	}

	// Moyenne
	sum = sum / N * (X_MAX - X_MIN) * M;

	// Affichage du r��sultat
	printf("Montecarlo multigpu[n=%lu, min=%f, max=%f, m=%d] = %f\n", N, X_MIN, X_MAX, M, sum);

	return true;
}

