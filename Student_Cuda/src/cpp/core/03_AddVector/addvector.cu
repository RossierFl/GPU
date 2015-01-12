
#include <iostream>
#include <stdlib.h>
#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"

// #define DEBUG 1

__host__ void useAdd();
static __global__ void add(float* ptrDevV1, float* ptrDevV2, int n, float* ptrDevResult);
static __device__ float work(float v1, float v2);
static __host__ void fillArray(float* ptrArray, int n, int start, int pas);

__host__ void useAdd() {
	int n = 10;

	float* v1 = new float[n];
	float* v2 = new float[n];
	float* vResult = new float[n];
	fillArray(v1, n, 1, 1);
	fillArray(v2, n, 2, 2);

	size_t size = sizeof(float) * n;
	float* ptrDevV1 = NULL;
	float* ptrDevV2 = NULL;
	float* ptrDevResult = NULL;
	HANDLE_ERROR( cudaMalloc(&ptrDevV1, size) );
	HANDLE_ERROR( cudaMalloc(&ptrDevV2, size) );
	HANDLE_ERROR( cudaMalloc(&ptrDevResult, size) );
	//
	HANDLE_ERROR( cudaMemset(ptrDevV1, 0, size) );
	HANDLE_ERROR( cudaMemset(ptrDevV2, 0, size) );
	HANDLE_ERROR( cudaMemset(ptrDevResult, 0, size) );
	//
	HANDLE_ERROR( cudaMemcpy(ptrDevV1, v1, size, cudaMemcpyHostToDevice) );
	HANDLE_ERROR( cudaMemcpy(ptrDevV2, v2, size, cudaMemcpyHostToDevice) );

	dim3 dg(4, 4, 1);
	dim3 db(4, 8, 1);
#ifdef DEBUG
	Device::checkDimError(dg, db);
	Device::checkDimOptimiser(dg, db);
#endif

	add<<<dg,db>>>(ptrDevV1, ptrDevV2, n, ptrDevResult); // asynchronous
	Device::checkKernelError("erreur kernel");

	HANDLE_ERROR( cudaMemcpy(vResult, ptrDevResult, size, cudaMemcpyDeviceToHost) ); // barrière de synchronisation
	for(int i = 0; i < n; i++) {
		std::cout << vResult[i] << "|";
	}
	std::cout << std::endl;
}

__host__ void fillArray(float* ptrArray, int n, int start, int pas) {
	for(int i = 0; i < n; i++) {
		ptrArray[i] = start;
		start += pas;
	}
}

__global__ void add(float* ptrDevV1, float* ptrDevV2, int n, float* ptrDevResult) {
	const int NB_THREAD = Indice2D::nbThread();
	const int TID = Indice2D::tid();

	int s = TID;
	while(s < n) {
		ptrDevResult[s] = work(ptrDevV1[s], ptrDevV2[s]);
		s += NB_THREAD;
	}
}

__device__ float work(float v1, float v2) {
	return v1 + v2;
}
