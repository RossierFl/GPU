#include <iostream>
#include <stdio.h>
#include "cudaTools.h"
#include "Device.h"
#include "Indice1D.h"
#include "reduction.h"
#include <assert.h>
#include <math.h>
#include "MathTools.h"

// #define DEBUG 1

#define M_W 100
#define M_V 100
#define VI 1.4422495703074083017725115
#define WI 0.7390851332151606722931092

__host__ bool useScalarProduct();
static __host__ double theoricalResult(int n);
static __global__ void scalarProduct(const uint N, double* ptrDevResult, const uint NB_THREAD);
static __device__ void reduceIntraThread(double* tabSM, int n);
static __device__ double v(int i);
static __device__ double w(int i);

static __host__ double theoricalResult(int n) {
	n--;
	return (n / (double) 2) * (n + 1);
}

static __global__ void scalarProduct(const uint N, double* ptrDevRes, const uint NB_THREAD) {
	/* Shared memory */
	extern __shared__ double tabSM[];
	initTabSM(tabSM, NB_THREAD, 0);

	// Reduce intra thread
	reduceIntraThread(tabSM, N);

	__syncthreads(); // TODO is really necessary ??

	// Reduce intra block
	reduceIntraBlock(tabSM, NB_THREAD);

	__syncthreads(); // TODO is really necessary ??

	// Reduce inter block
	reduceInterBlock(tabSM, ptrDevRes);
}

static __device__ void reduceIntraThread(double* tabSM, int n) {
	const uint TID = Indice1D::tid();
	const uint TID_LOCAL = Indice1D::tidLocalBlock();
	const uint NB_THREAD = Indice1D::nbThread();

	int s = TID;
	double sum = 0.0;
	while (s < n) {
		sum += v(s) * w(s);
		s += NB_THREAD;
	}

	tabSM[TID_LOCAL] = sum;
}

static __device__ double v(int i) {
	const uint TID = Indice1D::tid();
	double x = 1.5 + abs(cos((double) i));

	for (int j = 1; j <= M_V; j++) {
		double xCarre = x * x;
		x = x - (xCarre * x - 3) / (3 * xCarre);
	}

	return (x / VI) * sqrt((double) i);
}

static __device__ double w(int i) {
	const uint TID = Indice1D::tid();
	double x = abs(cos((double) i));

	for (int j = 1; j <= M_W; j++) {
		x = x - (cos(x) - x) / (-sin(x) - 1);
	}

	return (x / WI) * sqrt((double) i);
}

__host__ bool useScalarProduct() {

	printf("\n[Scalar Product]\n");

	const uint N = 50000;

	/* Scalar product in RAM */
	double scalarProductRAM = 0.0;
	double* ptrScalarProductRAM = &scalarProductRAM;

	/* Scalar product in GRAM */
	double* ptrDevScalarProductGRAM = NULL;
	size_t size = sizeof(double);
	HANDLE_ERROR(cudaMalloc(&ptrDevScalarProductGRAM, size));
	HANDLE_ERROR(cudaMemset(ptrDevScalarProductGRAM, 0, size));

	/* Parameters */
	const uint NB_THREAD = 32;
	assert((NB_THREAD & (NB_THREAD - 1)) == 0); // should be 2^xy
	dim3 dg = dim3(16, 1, 1);
	dim3 db = dim3(NB_THREAD, 1, 1);
#ifdef DEBUG
	Device::checkDimError(dg, db);
	Device::checkDimOptimiser(dg, db);
#endif

	/* Processing */
	size_t sizeTabSM = sizeof(double) * NB_THREAD;
	scalarProduct<<<dg,db,sizeTabSM>>>(N, ptrDevScalarProductGRAM, NB_THREAD); // asynchrone
	Device::checkKernelError("kernel error: scalarProduct");
	Device::synchronize(); // printf

	/* Fetch result */
	HANDLE_ERROR(cudaMemcpy(ptrScalarProductRAM, ptrDevScalarProductGRAM, size, cudaMemcpyDeviceToHost));
	HANDLE_ERROR(cudaFree(ptrDevScalarProductGRAM));

	/* Control result */
	double referenceValue = theoricalResult(N);
	printf("Result GPU = %f\n", scalarProductRAM);
	printf("Result CPU = %f\n", referenceValue);
	bool isOk = MathTools::isEquals(scalarProductRAM, referenceValue, 1);
	printf("isOk = %d\n", isOk);

	return isOk;
}
