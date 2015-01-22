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

void run_on_device(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE, const int DG, const int DB) {
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
	int* ptrImageDevGM = NULL;
	HANDLE_ERROR(cudaMalloc(&ptrImageDevGM, DATA_SIZE_BYTE));
	HANDLE_ERROR(cudaMemcpy(ptrImageDevGM, data, DATA_SIZE_BYTE, cudaMemcpyHostToDevice));

	// Histogramme en GRAM
	int* ptrHistogrammeDevGM = NULL;
	size_t sizeHistogramme = sizeof(int) * (HIST_SIZE);
	HANDLE_ERROR(cudaMalloc(&ptrHistogrammeDevGM, sizeHistogramme));
	HANDLE_ERROR(cudaMemset(ptrHistogrammeDevGM, 0, sizeHistogramme));

	// call kernel
	kernel<<<dg,db,HIST_SIZE_BYTE>>>(ptrImageDevGM, DATA_SIZE, ptrHistogrammeDevGM, HIST_SIZE);
	Device::checkKernelError("Kernel error: kernel cuda MultiGPU");
	Device::synchronize();

	// Recuperation du resultat
	HANDLE_ERROR(cudaMemcpy(hist, ptrHistogrammeDevGM, HIST_SIZE_BYTE, cudaMemcpyDeviceToHost)); // barriere de synchronisation

	// Liberation de la memoire
	HANDLE_ERROR(cudaFree(ptrImageDevGM));
	HANDLE_ERROR(cudaFree(ptrHistogrammeDevGM));
}

void hist_cuda_multigpu(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE, const int DG, const int DB) {

	const uint NB_GPU = Device::getDeviceCount();
	const uint HIST_SIZE = MAX_VALUE - MIN_VALUE + 1;
	const uint HIST_SIZE_BYTES = HIST_SIZE * sizeof(int);

	/* Compute steps for each GPU */
	uint remainingH = DATA_SIZE;
	uint start = 0;
	const uint stepH = DATA_SIZE / NB_GPU;
	uint steps[NB_GPU];
	uint starts[NB_GPU];
	for (int device = 0; device < NB_GPU; device++) {
		starts[device] = start;
		if (device == NB_GPU - 1) {
			steps[device] = remainingH;
		} else {
			steps[device] = stepH;
		}
		remainingH -= steps[device];
		start += steps[device];
	}

	/* Processing */
#pragma omp parallel for
	for (int device = 0; device < NB_GPU; device++) {
		// set current device
		cudaSetDevice(device);

		int* local_hist = new int[HIST_SIZE];
		memset(local_hist, 0, HIST_SIZE_BYTES);
		run_on_device(data + starts[device], local_hist, steps[device], MIN_VALUE, MAX_VALUE, DG, DB);

#pragma omp critical(section)
		{
			for(int i = 0; i < HIST_SIZE; i++) {
				hist[i] += local_hist[i];
			}
		}
	}

	// reset current device
	cudaSetDevice(0);
}
