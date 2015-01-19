#include <stdio.h>
#include <assert.h>

void hist_omp_for_critical_withouttab(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE)
{

	assert(MIN_VALUE < MAX_VALUE);
	assert(DATA_SIZE > 0);

	// Compute histogramme
#pragma omp parallel for
	for (int i = 0; i < DATA_SIZE; i++)
	{
		int val = data[i];
		uint index = val - MIN_VALUE;

#pragma omp atomic
		promotionHist[index]++;

	}
}