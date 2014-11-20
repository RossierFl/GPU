#ifndef REDUCTION_H_
#define REDUCTION_H_

#include <stdio.h>

static __device__ void initTabSM(float* tabSM, int n, int value);
static __device__ void reduceIntraBlock(float* tabSM, const int nTabSM);
static __device__ void ecrasement(float* tabSM, const int m);
static __device__ void reduceInterBlock(float* tabSM, float* tabGM);
static __device__ void debugTabSM(float* tabSM, int nTabSM, char* message);
static __device__ void debugTabGM(float* tabGM, int nTabGM, char* message);

__device__ void debugTabGM(float* tabGM, int nTabGM, char* message) {
	const unsigned int TID = Indice1D::tid();
	__syncthreads();
	if (TID == 0) {
		printf("--- %s ---\n", message);
		for (unsigned int i = 0; i < nTabGM; i++) {
			printf("tabGM[%d] = %f\n", i, tabGM[i]);
		}
	}
}

__device__ void debugTabSM(float* tabSM, int nTabSM, char* message) {
	const unsigned int TID_LOCAL = Indice1D::tidLocal();
	__syncthreads();
	if (TID_LOCAL == 0) {
		printf("--- %s ---\n", message);
		for (unsigned int i = 0; i < nTabSM; i++) {
			printf("tabSM[%d] = %f\n", i, tabSM[i]);
		}
	}
}

__device__ void initTabSM(float* tabSM, int nTabSM, int value) {
	const int NB_THREAD_LOCAL = Indice1D::nbThreadBlock();
	int s = Indice1D::tidLocal();
	while (s < nTabSM) {
		tabSM[s] = value;
		s += NB_THREAD_LOCAL;
	}
}

__device__ void reduceIntraBlock(float* tabSM, const int nTabSM) {
	int m = nTabSM / 2;
	while (m > 0) {
		ecrasement(tabSM, m);
		m /= 2;
		__syncthreads();
	}
}

__device__ void ecrasement(float* tabSM, const int m) {
	const int NB_THREAD_LOCAL = Indice1D::nbThreadBlock();
	const int TID_LOCAL = Indice1D::tidLocal();
	int s = TID_LOCAL;
	while (s < m) {
		tabSM[s] += tabSM[s + m];
		s += NB_THREAD_LOCAL;
	}
}

__device__ void reduceInterBlock(float* tabSM, float* tabGM) {
	if (threadIdx.x == 0) {
		// add the reduction of this block to the final result
		atomicAdd(tabGM, tabSM[0]);
	}
}

#endif
