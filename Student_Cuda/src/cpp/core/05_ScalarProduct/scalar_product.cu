#include <iostream>
#include <stdio.h>
#include "cudaTools.h"
#include "Device.h"
#include "Indice1D.h"
#include <assert.h>
#include <math.h>
#include "reduction.h"

#define DEBUG 1

#define M_W 50
#define M_V 50
#define VI 1.4422495703074083017725115
#define WI 0.7390851332151606722931092

__host__ double checkScalarProduct(uint n);
__global__ void scalarProduct(const uint N, double* ptrDevResultGM, const uint nTabSM);
__device__ void reduceIntraThread(double* tabSM, uint n);
__device__ double v(int i);
__device__ double w(int i);
__host__ bool useScalarProduct();

__host__ double checkScalarProduct(uint n) {
	n--;
	return (n / 2.0) * (n + 1);
}

__global__ void scalarProduct(const uint N, double* ptrDevResultGM, const uint N_TAB_SM) {
	/* Shared memory */
	extern __shared__ double tabSM[];

	const uint TID_LOCAL = Indice1D::tidLocalBlock();
	initTabSM(tabSM, N_TAB_SM, 0);

	// reduceIntraThread
	reduceIntraThread(tabSM, N_TAB_SM);

	__syncthreads(); // TODO is really necessary ??

#ifdef DEBUG
	if(TID_LOCAL == 0)
	debugTabSM(tabSM, N_TAB_SM, "after intra thread");
#endif

	// reduceIntraBlock
	reduceIntraBlock(tabSM, N_TAB_SM);

	__syncthreads(); // TODO is really necessary ??

	// reduceIntraBlock
	reduceInterBlock(tabSM, ptrDevResultGM);
}

__device__ void reduceIntraThread(double* tabSM, uint n) {
	const int NB_THREAD = Indice1D::nbThread();
	const int TID = Indice1D::tid();
	const int TID_LOCAL = Indice1D::tidLocalBlock();

	int s = TID;
	double sum = 0;
	while (s < n) {
		sum += v(s) * w(s);
		s += NB_THREAD;
	}

	tabSM[TID_LOCAL] = sum;
}

__device__ double v(int i) {
	double x = 1.5 + abs(cos((double) i));
	for (int j = 1; j <= M_V; j++) {
		double xCarre = x * x;
		x = x - (xCarre * x - 3) / (3 * xCarre);
	}
	return (x / VI) * sqrt((double) i);
}

__device__ double w(int i) {
	double x = abs(cos((double) i));
	for (int j = 1; j <= M_W; j++) {
		x = x - (cos(x) - x) / (-sin(x) - 1);
	}
	return (x / WI) * sqrt((double) i);
}

__host__ bool useScalarProduct() {
	printf("\n[Scalar Product]\n");

	const uint N = 100000;

	// Paramètres du GPU
	const uint NB_THREAD = 32;
	assert(NB_THREAD % 2 == 0);
	dim3 dg = dim3(16, 1, 1);
	dim3 db = dim3(NB_THREAD, 1, 1);
#ifdef DEBUG
	Device::checkDimError(dg, db);
	Device::checkDimOptimiser(dg, db);
#endif

	/* Result on CPU */
	double scalarProductResult = 0;

	/* Result on GPU */
	double* ptrScalarProductResultDevGRAM = NULL;
	HANDLE_ERROR(cudaMalloc(&ptrScalarProductResultDevGRAM, sizeof(double)));
	HANDLE_ERROR(cudaMemset(ptrScalarProductResultDevGRAM, 0, sizeof(double)));

	/* Launch kernel */
	size_t sizeTabSMByte = sizeof(double) * NB_THREAD;
	scalarProduct<<<dg,db,sizeTabSMByte>>>(N, ptrScalarProductResultDevGRAM, NB_THREAD);
	Device::checkKernelError("Kernel error: scalarProduct");
	Device::synchronize(); // Display printf

	/* Fetch result */
	HANDLE_ERROR(cudaMemcpy(&scalarProductResult, ptrScalarProductResultDevGRAM, sizeof(double), cudaMemcpyDeviceToHost));
	printf("GPU = %f\n", scalarProductResult);
	printf("CPU = %f\n", checkScalarProduct(N));

	/* Free memory */
	HANDLE_ERROR(cudaFree(ptrScalarProductResultDevGRAM));

	return true;
}

