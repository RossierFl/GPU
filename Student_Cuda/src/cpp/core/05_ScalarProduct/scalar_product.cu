#include <iostream>
#include <stdio.h>
#include "cudaTools.h"
#include "Device.h"
#include "Indice1D.h"
#include <assert.h>
#include <math.h>
#include "reduction.h"

using std::cout;
using std::endl;

#define M_W 100
#define M_V 100
#define VI 1.4422495703074083017725115
#define WI 0.7390851332151606722931092

__host__ double theoricalResult(uint n);
__global__ void scalarProduct(const uint N, float* ptrDevResultGM, const uint nTabSM);
__device__ void reduceIntraThread(float* tabSM, uint n);
__device__ float v(int i);
__device__ float w(int i);
__host__ bool useScalarProduct();

__host__ double theoricalResult(uint n) {
	n--;
	return (n / (double) 2) * (n + 1);
}

__global__ void scalarProduct(const uint N, float* ptrDevResultGM, const uint N_TAB_SM) {
	/* Shared memory */
	extern __shared__ float tabSM[];

	const uint TID_LOCAL = Indice1D::tidLocalBlock();
	initTabSM(tabSM, N_TAB_SM, 0);

	// reduceIntraThread
	reduceIntraThread(tabSM, N_TAB_SM);

	__syncthreads(); // TODO is really necessary ??

	// reduceIntraBlock
	reduceIntraBlock(tabSM, N_TAB_SM);

	// reduceIntraBlock
	reduceInterBlock(tabSM, ptrDevResultGM);
}

__device__ void reduceIntraThread(float* tabSM, uint n) {
	const uint NB_THREAD = Indice1D::nbThread();
	const uint TID = Indice1D::tid();
	const uint TID_LOCAL = Indice1D::tidLocalBlock();

	uint s = TID;
	float sum = 0;
	while (s < n) {
		sum += v(s) * w(s);
		s += NB_THREAD;
	}

	tabSM[TID_LOCAL] = sum;
}

__device__ float v(int i) {
	float x = 1.5 + abs(cos((float) i));
	for (int j = 1; j <= M_V; j++) {
		float xCarre = x * x;
		x = x - (xCarre * x - 3) / (3 * xCarre);
	}
	return (x / VI) * sqrt((float) i);
}

__device__ float w(int i) {
	float x = abs(cos((float) i));
	for (int j = 1; j <= M_W; j++) {
		x = x - (cos(x) - x) / (-sin(x) - 1);
	}
	return (x / WI) * sqrt((float) i);
}

__host__ bool useScalarProduct() {
	const uint N = 100000;
	printf("[Scalar Product]\n");

	// Paramètres du GPU
	const uint NB_THREAD = 16;
	assert(NB_THREAD % 2 == 0);
	dim3 dg = dim3(NB_THREAD, 1, 1);
	dim3 db = dim3(32, 1, 1);
	Device::checkDimError(dg, db);
	Device::checkDimOptimiser(dg, db);

	/* Result on CPU */
	float scalarProductResult = 0;

	/* Result on GPU */
	float* ptrScalarProductResultDevGRAM;
	HANDLE_ERROR(cudaMalloc(&ptrScalarProductResultDevGRAM, sizeof(float)));
	HANDLE_ERROR(cudaMemset(ptrScalarProductResultDevGRAM, 0, sizeof(float)));

	/* Launch kernel */
	size_t sizeTabSMByte = sizeof(float) * NB_THREAD;
	scalarProduct<<<dg,db,sizeTabSMByte>>>(N, ptrScalarProductResultDevGRAM, NB_THREAD);
	Device::checkKernelError("Kernel error: scalarProduct");
	Device::synchronize(); // Display printf

	/* Fetch result */
	HANDLE_ERROR(cudaMemcpy(&scalarProductResult, ptrScalarProductResultDevGRAM, sizeof(float), cudaMemcpyDeviceToHost));
	HANDLE_ERROR(cudaFree(ptrScalarProductResultDevGRAM));
	printf("Result GPU = %f - CPU = %f\n", scalarProductResult, theoricalResult(N));

	return true;
}

