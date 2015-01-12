#include <iostream>
#include <limits.h>
#include <stdio.h>

#include "cudaTools.h"
#include "Device.h"
#include "Indice1D.h"
#include "00_pi_tools.h"
#include "reduction.h"

// #define DEBUG 1

static __global__ void kernel(float* ptrDevPiGM, const int n, const int nTabSM);
static __device__ void reduceIntraThread(float* tabSM, int const n);
static __device__ float fpi(float x);
static double piCuda(const int n);
bool usePI();

/**
 * Kernel used to compute PI
 *
 * @param ptrDevPiGM location to save the final result of PI
 * @param n number of iterations
 */
__global__ void kernel(float* ptrDevPiGM, const int n, const int nTabSM) {
	// @formatter:off
	extern __shared__ float tabSM[];// 1 instance per block !
	// @formatter:on

	// Init
	initTabSM(tabSM, nTabSM, 0);
#ifdef DEBUG
	debugTabSM(tabSM, nTabSM, "After init");
#endif

	__syncthreads(); // TODO useless?

	// reduceIntraThread
	reduceIntraThread(tabSM, n);
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
	reduceInterBlock(tabSM, ptrDevPiGM);
#ifdef DEBUG
	debugTabGM(ptrDevPiGM, 1, "PI");
#endif
}

__device__ void reduceIntraThread(float* tabSM, const int N) {
	const int TID = Indice1D::tid();
	const int TID_LOCAL = Indice1D::tidLocal();
	const int NB_THREAD = Indice1D::nbThread();

	const float DX = 1.0 / N;
	float intraThreadSum = 0;
	int s = TID;
	while (s < N) {
		float xi = s * DX;

		intraThreadSum += fpi(xi);

		s += NB_THREAD;
	}
	tabSM[TID_LOCAL] = intraThreadSum * DX;
}

__device__ float fpi(float x) {
	return 4 / (1 + x * x);
}

double piCuda(const int n) {
	// résultat final de Pi en RAM
	float resultRAM = 0;

	// résultat final de Pi sur le GPU après réduction
	float* ptrDevPiGM = NULL;
	size_t size = sizeof(float);
	int nThreadPerBlock = 4;
	size_t sizeTabSM = sizeof(float) * nThreadPerBlock;
	HANDLE_ERROR(cudaMalloc(&ptrDevPiGM, size));
	HANDLE_ERROR(cudaMemset(ptrDevPiGM, 0, size));

	// Lancement du kernel
	dim3 dg(1, 1, 1); // TODO to optimize
	dim3 db(nThreadPerBlock, 1, 1); // TODO to optimize
#ifdef DEBUG
	Device::checkDimError(dg, db);
	Device::checkDimOptimiser(dg, db);
#endif
	kernel<<<dg,db,sizeTabSM>>>(ptrDevPiGM, n, nThreadPerBlock); // asynchronous
	Device::checkKernelError("Kernel error");

	// Récupération du résultat
	HANDLE_ERROR(cudaMemcpy(&resultRAM, ptrDevPiGM, size, cudaMemcpyDeviceToHost)); // barrière de synchronisation

	return (double) resultRAM;
}

bool usePI() {

	printf("\n[PI]\n");

	const int N = 2000000;
	return isAlgoPI_OK(piCuda, N, "Pi cuda");
}
