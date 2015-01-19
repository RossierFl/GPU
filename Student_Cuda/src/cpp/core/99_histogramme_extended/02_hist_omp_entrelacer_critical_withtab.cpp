#include <stdio.h>
#include <assert.h>

void hist_omp_entrelacer_critical_withtab(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE)
{

	assert(MIN_VALUE < MAX_VALUE);
	assert(DATA_SIZE > 0);

	const int NB_THREADS = OmpTools::setAndGetNaturalGranularity();
	const int NB_VALUES = MAX_VALUE - MIN_VALUE + 1;

	// Compute histogramme
#pragma omp parallel
	{
		// Init internal thread tab
		int* promotionHist = new int[NB_VALUES];
		for (int i = 0; i < NB_VALUES; i++)
		{
			promotionHist[i] = 0;
		}

		//
		const int TID = OmpTools::getTid();
		int s = TID;
		while (s < DATA_SIZE)
		{
			int val = data[i];
			uint index = val - MIN_VALUE;
			promotionHist[index]++;

			s += NBTHREADS;
		}

		// Reduction
		for (int i = 0; i < NB_VALUES; i++)
		{
#pragma omp critical(section)
			{
				hist[i] += promotionHist[i];
			}
		}

		delete[] promotionHist;
	}
}