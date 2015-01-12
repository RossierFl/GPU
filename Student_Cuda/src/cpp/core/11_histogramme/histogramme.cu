#include "AleaTools.h"
#include "Device.h"
#include <stdio.h>
#include <limits.h>
#include "cudaTools.h"
#include "Indice1D.h"
#include "reduction.h"
#include <assert.h>

#define WIDTH 2000
#define HEIGHT 2000
#define SIZE (WIDTH * HEIGHT)
#define MIN 0 /* SHOULD BE 0 ! */
#define MAX 255
#define NB_POSSIBLE_VALUE (MAX - MIN + 1)

// #define DEBUG 1

static __host__ void swap(uint* image, const uint IMAGE_SIZE);
static __host__ void fillImage(uint* image, const uint IMAGE_SIZE);
__host__ bool useHistogramme();
static __host__ bool checkHistogramme(uint* image, const uint IMAGE_SIZE, uint* hist);
static __global__ void hist(uint* ptrImageDevGM, size_t sizeImage, uint* ptrHistogrammeDevGM, size_t sizeHistogramme);

static __host__ void swap(uint* image, const uint IMAGE_SIZE)
{
	AleaTools r;
	for(int i = 0; i < IMAGE_SIZE * 10; i++)
	{
		int a = r.uniformeAB(0, IMAGE_SIZE - 1);
		int b = r.uniformeAB(0, IMAGE_SIZE - 1);

		uint tempA = image[a];
		uint tempB = image[b];

		image[a] = tempB;
		image[b] = tempA;
	}
}

static __host__ void fillImage(uint* image, const uint IMAGE_SIZE)
{
	// rempli
	uint* itr = image;
	for(uint i = 0; i < IMAGE_SIZE; i++)
	{
		*itr = (i * 11) % (NB_POSSIBLE_VALUE);
		itr++;
	}

	swap(image, IMAGE_SIZE);
}

static __global__ void hist(uint* ptrImageDevGM, size_t sizeImageByte, uint* ptrHistogrammeDevGM, size_t sizeHistogrammeByte)
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

static __host__ bool checkHistogramme(uint* image, const uint IMAGE_SIZE, uint* hist)
{
	bool valid = true;

	// init empty histogramme
	uint counts[NB_POSSIBLE_VALUE];
	for(int i = 0; i < NB_POSSIBLE_VALUE; i++)
	{
		counts[i] = 0;
	}

	// construct histogramme on CPU
	for(int i = 0; i < SIZE; i++)
	{
		uint v = *(image + i);
		counts[v]++;
	}

	// compare results
	uint sum2 = 0;
	for(int i = 0; i < NB_POSSIBLE_VALUE; i++)
	{
		sum2 += counts[i];
		if(counts[i] != hist[i])
		{
			valid = false;
			printf("ERROR ! : counts[%d] = %d but hist[%d] = %d\n", i, counts[i], i, hist[i]);
		}
	}

	if(sum2 != IMAGE_SIZE) {
		valid = false;
		printf("sum2 = %d\n", sum2);
	}

	return valid;
}

__host__ bool useHistogramme() {

	printf("\n[Histogramme]\n");
	printf("Image size: %dx%d (%d samples)\n", WIDTH, HEIGHT, SIZE);
	printf("Min value: %d\n", MIN);
	printf("Max value: %d\n", MAX);

	// Parameters
	uint nThreadPerBlock = 16;
	uint nBlockPerMP = 32;
	dim3 dg(nBlockPerMP, 1, 1); // TODO to optimize
	dim3 db(nThreadPerBlock, 1, 1); // TODO to optimize
#ifdef DEBUG
	Device::checkDimError(dg, db);
	Device::checkDimOptimiser(dg, db);
#endif

	// Image
	size_t sizeImage = sizeof(uint) * SIZE;
	uint* ptrImageRAM = new uint[SIZE];
	fillImage(ptrImageRAM, SIZE);

	// Image en GRAM
	uint* ptrImageDevGM = NULL;
	HANDLE_ERROR(cudaMalloc(&ptrImageDevGM, sizeImage));
	HANDLE_ERROR(cudaMemcpy(ptrImageDevGM, ptrImageRAM, sizeImage, cudaMemcpyHostToDevice));

	// Histogramme en RAM
	uint* ptrHistogrammeRAM = new uint[NB_POSSIBLE_VALUE];

	// Histogramme en GRAM
	uint* ptrHistogrammeDevGM = NULL;
	size_t sizeHistogramme = sizeof(uint) * (NB_POSSIBLE_VALUE);
	HANDLE_ERROR(cudaMalloc(&ptrHistogrammeDevGM, sizeHistogramme));
	HANDLE_ERROR(cudaMemset(ptrHistogrammeDevGM, 0, sizeHistogramme));

	// call kernel
	hist<<<dg,db,sizeHistogramme>>>(ptrImageDevGM, sizeImage, ptrHistogrammeDevGM, sizeHistogramme);
	Device::checkKernelError("Kernel error: hist");
	Device::synchronize();

	// Récupération du résultat
	HANDLE_ERROR(cudaMemcpy(ptrHistogrammeRAM, ptrHistogrammeDevGM, sizeHistogramme, cudaMemcpyDeviceToHost)); // barrière de synchronisation

	// Libération de la mémoire
	HANDLE_ERROR(cudaFree(ptrHistogrammeDevGM));

	// Affichage du résultat
	uint sum = 0;
	for (uint i = MIN; i <= MAX; i++) {
		sum += ptrHistogrammeRAM[i];
#ifdef DEBUG
		printf("hist(%d) = %d\n", i, ptrHistogrammeRAM[i]);
#endif
	}

	bool isOk = checkHistogramme(ptrImageRAM, SIZE, ptrHistogrammeRAM);
	printf("isOk = %d\n", isOk);

	return isOk;
}
