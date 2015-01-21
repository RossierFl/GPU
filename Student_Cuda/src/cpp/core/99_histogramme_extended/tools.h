
#ifndef TOOLS_H
#define TOOLS_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "AleaTools.h"

static void swap(int* image, const uint DATA_SIZE);
static void generateData(int* data, const uint DATA_SIZE);

static void swap(int* data, const uint DATA_SIZE)
{
	AleaTools r;
	for(int i = 0; i < DATA_SIZE; i++)
	{
		int a = r.uniformeAB(0, DATA_SIZE - 1);
		int b = r.uniformeAB(0, DATA_SIZE - 1);

		uint tempA = data[a];
		uint tempB = data[b];

		data[a] = tempB;
		data[b] = tempA;
	}
}

static void generateData(int* data, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE)
{
	assert(MIN_VALUE < MAX_VALUE);

	const uint M = MAX_VALUE - MIN_VALUE;

//#pragma omp parallel for
	for(int i = 0; i < DATA_SIZE; i++)
	{
		data[i] = MIN_VALUE + ((i * 11) % M);
	}
}

static bool check_histogramme(int* hist, int* valid_hist, const uint HIST_SIZE)
{
	for(int i = 0; i < HIST_SIZE; i++) {
		if(hist[i] != valid_hist[i]) {
			return false;
		}
	}

	return true;
}

#endif
