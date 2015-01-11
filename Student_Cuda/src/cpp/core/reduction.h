#ifndef REDUCTION_H_
#define REDUCTION_H_

#include <stdio.h>

/* ------------------------------------------------------------------- */

static __device__ double atomicAdd(double* address, double val);

template<typename T>
static __device__ void initTabSM(T* tabSM, int n, int value);

template<typename T>
static __device__ void reduceIntraBlock(T* tabSM, const int nTabSM);

template<typename T>
static __device__ void ecrasement(T* tabSM, const int m);

static __device__ void reduceInterBlock(float* tabSM, float* tabGM);
static __device__ void reduceInterBlock(double* tabSM, double* tabGM);

template<typename T>
static __device__ void debugTabSM(T* tabSM, int nTabSM, char* message);

template<typename T>
static __device__ void debugTabGM(T* tabGM, int nTabGM, char* message);

/* ------------------------------------------------------------------- */

template<typename T>
__device__ void debugTabGM(T* tabGM, int nTabGM, char* message) {
	const unsigned int TID = Indice1D::tid();
	__syncthreads();
	if (TID == 0) {
		printf("--- %s ---\n", message);
		for (unsigned int i = 0; i < nTabGM; i++) {
			printf("tabGM[%d] = %f\n", i, tabGM[i]);
		}
	}
}
template<typename T>
__device__ void debugTabSM(T* tabSM, int nTabSM, char* message) {
	const unsigned int TID_LOCAL = Indice1D::tidLocal();
	__syncthreads();
	if (TID_LOCAL == 0) {
		printf("--- %s ---\n", message);
		for (unsigned int i = 0; i < nTabSM; i++) {
			printf("tabSM[%d] = %f\n", i, tabSM[i]);
		}
	}
}

template<typename T>
__device__ void initTabSM(T* tabSM, int nTabSM, int value) {
	const int NB_THREAD_LOCAL = Indice1D::nbThreadBlock();
	int s = Indice1D::tidLocal();
	while (s < nTabSM) {
		tabSM[s] = value;
		s += NB_THREAD_LOCAL;
	}
}

template<typename T>
__device__ void reduceIntraBlock(T* tabSM, const int nTabSM) {
	int m = nTabSM / 2;
	while (m > 0) {
		ecrasement(tabSM, m);
		m /= 2;
		__syncthreads();
	}
}

template<typename T>
__device__ void ecrasement(T* tabSM, const int m) {
	const int NB_THREAD_LOCAL = Indice1D::nbThreadBlock();
	const int TID_LOCAL = Indice1D::tidLocal();
	int s = TID_LOCAL;
	while (s < m) {
		tabSM[s] += tabSM[s + m];
		s += NB_THREAD_LOCAL;
	}
}

__device__
double atomicAdd(double* address, double val) {
	unsigned long long int* address_as_ull = (unsigned long long int*) address;
	unsigned long long int old = *address_as_ull, assumed;
	do {
		assumed = old;
		old = atomicCAS(address_as_ull, assumed, __double_as_longlong(val + __longlong_as_double(assumed)));
		// Note: uses integer comparison to avoid hang in case of NaN (since NaN != NaN)
	} while (assumed != old);
	return __longlong_as_double(old);
}

__device__
void reduceInterBlock(double* tabSM, double* tabGM) {
	if (threadIdx.x == 0) {
		// add the reduction of this block to the final result
		atomicAdd(tabGM, tabSM[0]);
	}
}

__device__
void reduceInterBlock(float* tabSM, float* tabGM) {
	if (threadIdx.x == 0) {
		// add the reduction of this block to the final result
		atomicAdd(tabGM, tabSM[0]);
	}
}

#endif
