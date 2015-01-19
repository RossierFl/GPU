#include <stdio.h>
#include <assert.h>

void hist_omp_for_tabpromotion(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE)
{

	assert(MIN_VALUE < MAX_VALUE);
	assert(DATA_SIZE > 0);

	const int NB_THREADS = OmpTools::setAndGetNaturalGranularity();
	const int NB_VALUES = MAX_VALUE - MIN_VALUE + 1;

	// Init
	int promotionHistSize = NB_VALUES * NB_THREADS;
	int* promotionHist = new int[promotionHistSize];
	for (int i = 0; i < promotionHistSize; i++)
	{
		promotionHistSize[i] = 0;
	}

	// Compute histogramme
#pragma omp parallel for
	for (int i = 0; i < DATA_SIZE; i++)
	{
		const int TID = OmpTools::getTid();
		const int OFFSET = TID * (MAX_VALUE - MIN_VALUE + 1);

		int val = data[i];
		uint index = val - MIN_VALUE;
		promotion[OFFSET + index]++;

	}

	// Reduction
	for (int i = 0; i < promotionHistSize; i++)
	{
		hist[i % NB_VALUES] += promotionHist[i];
	}

	delete[] promotionHist;
}