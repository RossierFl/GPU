
#include "AleaTools.h"
#include "Device.h"
#include <stdio.h>
#include <limits.h>
#include "cudaTools.h"
#include "Indice1D.h"
#include "reduction.h"

#define WIDTH 20
#define HEIGHT 20
#define SIZE (WIDTH * HEIGHT)
#define MIN 0
#define MAX 255

#define DEBUG 1

__host__ void swap(uint* image, const uint IMAGE_SIZE);
__host__ void fillImage(uint* image, const uint IMAGE_SIZE);
__host__ void useHistogramme();
__global__ void hist(uint* ptrImageDevGM, size_t sizeImage, uint* ptrHistogrammeDevGM, size_t sizeHistogramme);

__host__ void swap(uint* image, const uint IMAGE_SIZE)
{
	AleaTools r;
	uint a = r.uniformeAB(0, IMAGE_SIZE - 1);
	uint b = r.uniformeAB(0, IMAGE_SIZE - 1);

	uint temp = image[a];
	image[a] = image[b];
	image[b] = temp;
}

__host__ void fillImage(uint* image, const uint IMAGE_SIZE)
{
	// rempli
	for(int i = 0; i < IMAGE_SIZE; i++)
	{
		*image = i % (MAX + 1);
		image++;
	}

	// mélange les données
	for(int i = 0; i < SIZE * 10; i++)
	{
		//swap(image, IMAGE_SIZE);
	}
}

__host__ void useHistogramme()
{
	// Parameters
	uint nThreadPerBlock = 4;
	uint nBlockPerMP = 2;
	dim3 dg(nBlockPerMP, 1, 1); // TODO to optimize
	dim3 db(nThreadPerBlock, 1, 1); // TODO to optimize
	Device::checkDimError(dg, db);
	Device::checkDimOptimiser(dg, db);
#ifdef DEBUG
	printf("Parameters\n");
#endif

	// Image
	size_t sizeImage = sizeof(uint) * SIZE;
	uint* ptrImageRAM = new uint[SIZE];
	fillImage(ptrImageRAM, SIZE);
#ifdef DEBUG
	printf("Fill image\n");
#endif

	// Image en GRAM
	uint* ptrImageDevGM = NULL;
	HANDLE_ERROR(cudaMalloc(&ptrImageDevGM, sizeImage));
	HANDLE_ERROR(cudaMemcpy(ptrImageDevGM, ptrImageRAM, sizeImage, cudaMemcpyHostToDevice));
#ifdef DEBUG
	printf("Image en GRAM\n");
#endif

	// Histogramme en RAM
	uint* ptrHistogrammeRAM = new uint[MAX - MIN + 1];
#ifdef DEBUG
	printf("histogramme en RAM\n");
#endif

	// Histogramme en GRAM
	uint* ptrHistogrammeDevGM = NULL;
	size_t sizeHistogramme = sizeof(uint) * (MAX - MIN + 1);
	HANDLE_ERROR(cudaMalloc(&ptrHistogrammeDevGM, sizeHistogramme));
	HANDLE_ERROR(cudaMemset(ptrHistogrammeDevGM, 0, sizeHistogramme));
#ifdef DEBUG
	printf("histogramme en GRAM\n");
#endif

	// call kernel
	hist<<<dg,db,sizeHistogramme>>>(ptrImageDevGM, sizeImage, ptrHistogrammeDevGM, sizeHistogramme);
	Device::checkKernelError("Kernel error: hist");
#ifdef DEBUG
	printf("Kernel finished\n");
#endif

	// Récupération du résultat
	HANDLE_ERROR(cudaMemcpy(ptrHistogrammeRAM, ptrHistogrammeDevGM, sizeHistogramme, cudaMemcpyDeviceToHost)); // barrière de synchronisation
#ifdef DEBUG
	printf("final histogramme copied\n");
#endif

	// Affichage du résultat
	uint sum = 0;
	for(uint i = MIN; i <= MAX; i++)
	{
		sum += ptrHistogrammeRAM[i];
		printf("hist(%d) = %d\n", i, ptrHistogrammeRAM[i]);
	}
	if(sum == SIZE) printf("OK, sum == SIZE\n");
	else printf("ERROR !!!!!!!!!!, sum != SIZE\n");
}

__global__ void hist(uint* ptrImageDevGM, size_t sizeImageByte, uint* ptrHistogrammeDevGM, size_t sizeHistogrammeByte)
{
	// @formatter:off
	extern __shared__ float tabSM[]; // 1 instance per block !
	// @formatter:on

	initTabSM(tabSM, MAX + 1, 0);

	const uint TID = Indice1D::tid();
	const uint TID_LOCAL = Indice1D::tidLocal();
	const uint NB_THREAD = Indice1D::nbThread();

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
	s = TID;
	while(s < MAX + 1)
	{
		// work >>>>
		atomicAdd(&ptrHistogrammeDevGM[s], tabSM[s]);
		// <<<< end work
		s += NB_THREAD;
	}
}
