#include <stdlib.h>
#include <stdio.h>
#include "Device.h"
#include "Indice1D.h"
#include "reduction.h"
#include "cudaTools.h"

static __global__ void kernel(uint* ptrImageDevGM, size_t sizeImage, uint* ptrHistogrammeDevGM, size_t sizeHistogramme)
{
	const uint TID = Indice1D::tid();
	const uint NB_THREAD = Indice1D::nbThread();

	uint s = TID;
	while (s < sizeImage)
	{
		// work >>>>
		uint value = ptrImageDevGM[s];
		atomicAdd(&ptrHistogrammeDevGM[value], 1);
		// <<<< end work

		s += NB_THREAD;
	}
}

__host__ void hist_cuda_gm(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE, const int DG, const int DB)
{
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
	uint* ptrImageDevGM = NULL;
	HANDLE_ERROR(cudaMalloc(&ptrImageDevGM, DATA_SIZE_BYTE));
	HANDLE_ERROR(cudaMemcpy(ptrImageDevGM, data, DATA_SIZE_BYTE, cudaMemcpyHostToDevice));

	// Histogramme en GRAM
	uint* ptrHistogrammeDevGM = NULL;
	size_t sizeHistogramme = sizeof(int) * (HIST_SIZE);
	HANDLE_ERROR(cudaMalloc(&ptrHistogrammeDevGM, sizeHistogramme));
	HANDLE_ERROR(cudaMemset(ptrHistogrammeDevGM, 0, sizeHistogramme));

	// call kernel
	kernel<<<dg,db>>>(ptrImageDevGM, DATA_SIZE, ptrHistogrammeDevGM, HIST_SIZE);
	Device::checkKernelError("Kernel error: kernel cuda GM");
	Device::synchronize();

	// R��cup��ration du r��sultat
	HANDLE_ERROR(cudaMemcpy(hist, ptrHistogrammeDevGM, HIST_SIZE_BYTE, cudaMemcpyDeviceToHost)); // barri��re de synchronisation

	// Lib��ration de la m��moire
	HANDLE_ERROR(cudaFree(ptrImageDevGM));
	HANDLE_ERROR(cudaFree(ptrHistogrammeDevGM));
}
