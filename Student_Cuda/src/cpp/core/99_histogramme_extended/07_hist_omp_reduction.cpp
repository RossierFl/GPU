#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void hist_omp_reduction(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE)
{
	assert(false && "not working");
	/*assert(MIN_VALUE < MAX_VALUE);
	assert(DATA_SIZE > 0);

	#pragma omp parallel for reduction(+:hist)
	for (uint i = 0; i < DATA_SIZE; i++)
	{
		int val = data[i];
		uint index = val - MIN_VALUE;
		hist[index] += 1;
	}*/
}
