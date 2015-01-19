
#include <stdio.h>
#include <assert.h>

void hist_sequential(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE)
{

	assert(MIN_VALUE < MAX_VALUE);

	for (uint i = 0; i < DATA_SIZE; i++)
	{
		int val = data[i];
		uint index = val - MIN_VALUE;
		hist[index]++;
	}
}