
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
	for(int i = 0; i < DATA_SIZE * 10; i++)
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

	int* itr = data;
	for(int i = 0; i < DATA_SIZE; i++)
	{
		*itr = MIN_VALUE + ((i * 11) % (MAX_VALUE - MIN_VALUE));
		itr++;
	}

	swap(data, DATA_SIZE);
}

#endif
