// #define DEBUG 1
#include "tools.h"

extern void hist_sequential(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE);

extern void hist_omp_entrelacer_tabpromotion(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE);

void histogramme_extended()
{
	const int DATA_SIZE = 2000000;
	const int MIN_VALUE = 0;
	const int MAX_VALUE = 255;
	const int NB_POSSIBLE_VALUES = MAX_VALUE - MIN_VALUE + 1;

	// Generate initial data
	int* data = new int[DATA_SIZE];
	generateData(data, DATA_SIZE, MIN_VALUE, MAX_VALUE);

	// Hists
	int* hist_sequential_result = new int[NB_POSSIBLE_VALUES];
	int* hist_omp_entrelacer_tabpromotion_result = new int[NB_POSSIBLE_VALUES];

	// Compute histogramme
	hist_sequential(data, hist_sequential_result, DATA_SIZE, MIN_VALUE, MAX_VALUE);
	hist_omp_entrelacer_tabpromotion(data, hist_omp_entrelacer_tabpromotion_result, DATA_SIZE, MIN_VALUE, MAX_VALUE);

	// Libération mémoire
	delete[] data;
	delete[] hist_sequential_result;
	delete[] hist_omp_entrelacer_tabpromotion_result;
}