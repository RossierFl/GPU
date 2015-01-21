#include <stdlib.h>
#include <stdio.h>
#include "Device.h"
#include "Indice1D.h"
#include "reduction.h"
#include "cudaTools.h"

static __global__ void kernel(int* ptrImageDevGM, size_t sizeImage, int* ptrHistogrammeDevGM, size_t sizeHistogramme)
{
	// @formatter:off
	extern __shared__ uint tabSM[];// 1 instance per block !
	// @formatter:on

	initTabSM(tabSM, sizeHistogramme, 0);

	const uint TID = Indice1D::tid();
	const uint TID_LOCAL = Indice1D::tidLocal();
	const uint NB_THREAD = Indice1D::nbThread();
	const uint NB_THREAD_LOCAL = Indice1D::nbThreadBlock();

	uint s = TID;
	while(s < sizeImage)
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
	while(s < sizeHistogramme)
	{
		// work >>>>
		atomicAdd(&ptrHistogrammeDevGM[s], tabSM[s]);
		// <<<< end work
		s += NB_THREAD_LOCAL;
	}
}

__host__ void hist_cuda_zerocopy(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE, const int DG, const int DB)
{
	//HANDLE_ERROR(cudaSetDevice(0));
	//HANDLE_ERROR(cudaSetDeviceFlags(cudaDeviceMapHost));
	//HANDLE_ERROR(cudaSetDevice(0));

	// Image
	const size_t DATA_SIZE_BYTE = sizeof(int) * DATA_SIZE;
	const uint HIST_SIZE = MAX_VALUE - MIN_VALUE + 1;
	const size_t HIST_SIZE_BYTE = sizeof(int) * HIST_SIZE;

	// Parameters
	uint nThreadPerBlock = DB; // TODO to optimize
	uint nBlockPerMP = DG; // TODO to optimize
	dim3 dg(nBlockPerMP, 1, 1);
	dim3 db(nThreadPerBlock, 1, 1);
#ifdef DEBUG
	Device::checkDimError(dg, db);
	Device::checkDimOptimiser(dg, db);
#endif

	// Image en GRAM
	int* ptrDataZeroCopyMem = NULL;
	HANDLE_ERROR(cudaHostAlloc(&ptrDataZeroCopyMem, DATA_SIZE_BYTE, cudaHostAllocDefault));
	memcpy(ptrDataZeroCopyMem, data, DATA_SIZE_BYTE);
	int* ptrImageDevGM = NULL;
	HANDLE_ERROR(cudaHostGetDevicePointer(&ptrImageDevGM, ptrDataZeroCopyMem, 0));

	// Histogramme en GRAM
	int* ptrHistogrammeDevGM = NULL;
	size_t sizeHistogramme = sizeof(int) * (HIST_SIZE);
	HANDLE_ERROR(cudaMalloc(&ptrHistogrammeDevGM, sizeHistogramme));
	HANDLE_ERROR(cudaMemset(ptrHistogrammeDevGM, 0, sizeHistogramme));

	// call kernel
	kernel<<<dg,db,HIST_SIZE_BYTE>>>(ptrImageDevGM, DATA_SIZE, ptrHistogrammeDevGM, HIST_SIZE);
	Device::checkKernelError("Kernel error: kernel cuda ZCMEM");
	Device::synchronize();

	// Recuperation du resultat
	HANDLE_ERROR(cudaMemcpy(hist, ptrHistogrammeDevGM, HIST_SIZE_BYTE, cudaMemcpyDeviceToHost)); // barri������re de synchronisation

	// Liberation de la memoire
	HANDLE_ERROR(cudaFreeHost(ptrDataZeroCopyMem));
	//HANDLE_ERROR(cudaFree(ptrImageDevGM));
	HANDLE_ERROR(cudaFree(ptrHistogrammeDevGM));
}
