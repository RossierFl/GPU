#include "AleaTools.h"
#include "Device.h"
#include <stdio.h>
#include "cudaTools.h"
#include "Indice1D.h"
#include "reduction.h"

static __global__ void kernel(uint* ptrImageDevGM, size_t sizeImageByte, uint* ptrHistogrammeDevGM, size_t sizeHistogrammeByte)
{
	// @formatter:off
	extern __shared__ uint tabSM[];// 1 instance per block !
	// @formatter:on

	initTabSM(tabSM, NB_POSSIBLE_VALUE, 0);

	const uint TID = Indice1D::tid();
	const uint TID_LOCAL = Indice1D::tidLocal();
	const uint NB_THREAD = Indice1D::nbThread();
	const uint NB_THREAD_LOCAL = Indice1D::nbThreadBlock();

	uint s = TID;
	while(s < SIZE)
	{
		// work >>>>
		uint value = ptrImageDevGM[s];
		atomicAdd(&tabSM[value], 1);
		// <<<< end work

		s += NB_THREAD;
	}

	// synchronization entre les threads du meme bloc
	__syncthreads();

	// merge local hist with global hist
	s = TID_LOCAL;
	while(s < NB_POSSIBLE_VALUE)
	{
		// work >>>>
		atomicAdd(&ptrHistogrammeDevGM[s], tabSM[s]);
		// <<<< end work
		s += NB_THREAD_LOCAL;
	}
}

__host__ void hist_cuda_sm(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE)
{
	printf("\n[Histogramme cuda SM]\n");

	// Image
	const size_t DATA_SIZE_BYTE = sizeof(int) * DATA_SIZE;
	const uint NB_POSSIBLE_VALUE = MAX_VALUE - MIN_VALUE + 1;
	const size_t HIST_SIZE_BYTE = sizeof(int) * NB_POSSIBLE_VALUE;

	// Parameters
	uint nThreadPerBlock = 16; // TODO to optimize
	uint nBlockPerMP = 32; // TODO to optimize
	dim3 dg(nBlockPerMP, 1, 1);
	dim3 db(nThreadPerBlock, 1, 1);
#ifdef DEBUG
	Device::checkDimError(dg, db);
	Device::checkDimOptimiser(dg, db);
#endif

	// Image en GRAM
	uint* ptrImageDevGM = NULL;
	HANDLE_ERROR(cudaMalloc(&ptrImageDevGM, DATA_SIZE_BYTE));
	HANDLE_ERROR(cudaMemcpy(ptrImageDevGM, data, DATA_SIZE_BYTE, cudaMemcpyHostToDevice));

	// Histogramme en GRAM
	uint* ptrHistogrammeDevGM = NULL;
	size_t sizeHistogramme = sizeof(uint) * (NB_POSSIBLE_VALUE);
	HANDLE_ERROR(cudaMalloc(&ptrHistogrammeDevGM, sizeHistogramme));
	HANDLE_ERROR(cudaMemset(ptrHistogrammeDevGM, 0, sizeHistogramme));

	// call kernel
	kernel<<<dg,db,HIST_SIZE_BYTE>>>(ptrImageDevGM, DATA_SIZE, ptrHistogrammeDevGM, NB_POSSIBLE_VALUE);
	Device::checkKernelError("Kernel error: kernel cuda SM");
	Device::synchronize();

	// Récupération du résultat
	HANDLE_ERROR(cudaMemcpy(hist, ptrHistogrammeDevGM, HIST_SIZE_BYTE, cudaMemcpyDeviceToHost)); // barrière de synchronisation

	// Libération de la mémoire
	HANDLE_ERROR(cudaFree(ptrImageDevGM));
	HANDLE_ERROR(cudaFree(ptrHistogrammeDevGM));
}