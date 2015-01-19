#include <stdio.h>
#include <assert.h>

void hist_omp_entrelacer_critical_withouttab(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE)
{

	assert(MIN_VALUE < MAX_VALUE);
	assert(DATA_SIZE > 0);

	const int NB_THREADS = OmpTools::setAndGetNaturalGranularity();

	// Compute histogramme
#pragma omp parallel
	{
		//
		const int TID = OmpTools::getTid();
		int s = TID;
		while (s < DATA_SIZE)
		{
			int val = data[i];
			uint index = val - MIN_VALUE;
#pragma omp critical(section)
			{
				hist[index]++;
			}

			s += NBTHREADS;
		}
	}
}