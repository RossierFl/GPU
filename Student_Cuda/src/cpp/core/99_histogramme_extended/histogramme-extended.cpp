#define DEBUG 1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include "tools.h"
#include "Chronos.h"

extern void hist_sequential(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE);
extern void hist_omp_entrelacer_tabpromotion(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE);
extern void hist_omp_entrelacer_critical_withouttab(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE);
extern void hist_omp_entrelacer_critical_withtab(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE);
extern void hist_omp_entrelacer_atomic_withouttab(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE);
extern void hist_omp_entrelacer_atomic_withtab(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE);
extern void hist_omp_for_critical_withouttab(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE);
extern void hist_omp_for_atomic_withouttab(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE);
extern void hist_omp_for_tabpromotion(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE);
extern void hist_cuda_gm(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE, const int DG, const int DB);
extern void hist_cuda_sm(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE, const int DG, const int DB);
extern void hist_cuda_zerocopy(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE, const int DG, const int DB);

typedef void (*hist_function_omp) (int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE);
typedef void (*hist_function_cuda) (int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE, const int DG, const int DB);

typedef struct hist_function_meta {
	void* function;
	string function_name;
	bool is_cuda;
	int dg;
	int db;
} hist_function_meta;

typedef struct test_run_meta {
	int data_size;
	int min_value;
	int max_value;
	int* data;
	int* valid_hist;
} test_run_meta;

void histogramme_extended() {

	Chronos chrono_all;
	chrono_all.start();

	const int NB_ITERATIONS = 10;

	// Registrer functions
	// @formatter:off
	hist_function_meta registred_hist_functions[] = {
		{ (void*) &hist_sequential, "hist_sequential", false },
		{ (void*) &hist_omp_entrelacer_tabpromotion, "hist_omp_entrelacer_tabpromotion", false },
		{ (void*) &hist_omp_entrelacer_critical_withouttab, "hist_omp_entrelacer_critical_withouttab", false },
		{ (void*) &hist_omp_entrelacer_critical_withtab, "hist_omp_entrelacer_critical_withtab", false },
		{ (void*) &hist_omp_entrelacer_atomic_withouttab, "hist_omp_entrelacer_atomic_withouttab", false },
		{ (void*) &hist_omp_entrelacer_atomic_withtab, "hist_omp_entrelacer_atomic_withtab", false },
		{ (void*) &hist_omp_for_critical_withouttab, "hist_omp_for_critical_withouttab", false },
		{ (void*) &hist_omp_for_atomic_withouttab, "hist_omp_for_atomic_withouttab", false },
		{ (void*) &hist_omp_for_tabpromotion, "hist_omp_for_tabpromotion", false },
		// { (void*) &hist_omp_reduction, "hist_omp_reduction" },

		{ (void*) &hist_cuda_gm, "hist_cuda_gm", true, 1, 1 },
		{ (void*) &hist_cuda_gm, "hist_cuda_gm", true, 16, 32 },
		{ (void*) &hist_cuda_gm, "hist_cuda_gm", true, 16, 64 },
		{ (void*) &hist_cuda_gm, "hist_cuda_gm", true, 16, 192 },
		{ (void*) &hist_cuda_gm, "hist_cuda_gm", true, 16, 256 },
		{ (void*) &hist_cuda_gm, "hist_cuda_gm", true, 16, 384 },
		{ (void*) &hist_cuda_gm, "hist_cuda_gm", true, 16, 512 },
		{ (void*) &hist_cuda_gm, "hist_cuda_gm", true, 16, 768 },

		{ (void*) &hist_cuda_sm, "hist_cuda_sm", true, 1, 1 },
		{ (void*) &hist_cuda_sm, "hist_cuda_sm", true, 16, 32 },
		{ (void*) &hist_cuda_sm, "hist_cuda_sm", true, 16, 64 },
		{ (void*) &hist_cuda_sm, "hist_cuda_sm", true, 16, 192 },
		{ (void*) &hist_cuda_sm, "hist_cuda_sm", true, 16, 256 },
		{ (void*) &hist_cuda_sm, "hist_cuda_sm", true, 16, 384 },
		{ (void*) &hist_cuda_sm, "hist_cuda_sm", true, 16, 512 },
		{ (void*) &hist_cuda_sm, "hist_cuda_sm", true, 16, 768 },

		{ (void*) &hist_cuda_zerocopy, "hist_cuda_zerocopy", true, 16, 768 }
	};
	int registred_hist_functions_length = 26;
	// @formatter:on

	// Register runs
	test_run_meta test_runs[] = {
		{ 2000, 0, 5, NULL, NULL },
		{ 200000000, 0, 5, NULL, NULL },
		{ 2000, 0, 200, NULL, NULL },
		{ 200000000, 0, 200, NULL, NULL }
	};
	int test_runs_length = 4;
	for(int r = 0; r < test_runs_length; r++) {
		std::cout << "Generating data[" << (r+1) << "/" << test_runs_length << "]..." << std::endl;

		std::cout << " > Generating..." << std::endl;
		test_runs[r].data = new int[test_runs[r].data_size];
		generateData(test_runs[r].data, test_runs[r].data_size, test_runs[r].min_value, test_runs[r].max_value);

		std::cout << " > Swapping..." << std::endl;
		swap(test_runs[r].data, test_runs[r].data_size);

		std::cout << " > Generating valid histogram..." << std::endl;
		test_runs[r].valid_hist = new int[test_runs[r].data_size];
		hist_sequential(test_runs[r].data, test_runs[r].valid_hist, test_runs[r].data_size, test_runs[r].min_value, test_runs[r].max_value);

		std::cout << " > Finished." << std::endl;
	}

	// Header
	std::cout << std::endl;
	std::cout << "NB_ITERATIONS=" << NB_ITERATIONS << std::endl;
	for(int r = 0; r < test_runs_length; r++) {

		test_run_meta test_run = test_runs[r];
		int data_size = test_run.data_size;
		int min_value = test_run.min_value;
		int max_value = test_run.max_value;
		int hist_size = max_value - min_value + 1;

		std::ostringstream os;
		os << ";time AVG[size=" << data_size << ", min=" << min_value << ", max=" << max_value << "]";
		std::cout << os.str().c_str();
	}

	// Compute
	for(int i = 0; i < registred_hist_functions_length; i++) {
		hist_function_meta registred_hist_function = registred_hist_functions[i];
		hist_function_cuda fcuda = NULL;
		hist_function_omp fomp = NULL;

		if(registred_hist_function.is_cuda) {
			fcuda = (hist_function_cuda) registred_hist_function.function;
		} else {
			fomp = (hist_function_omp) registred_hist_function.function;
		}

		string fname = registred_hist_function.function_name;
		if(registred_hist_function.is_cuda) {
			fname += "[dg=";
			fname += boost::lexical_cast<std::string>(registred_hist_function.dg);
			fname += ",db=";
			fname += boost::lexical_cast<std::string>(registred_hist_function.db);
			fname += "]";
		}
		std::cout << std::endl;
		std::cout << fname;

		// Compute histogrammes for each registred runs
		for(int r = 0; r < test_runs_length; r++) {

			double time = 0;

			for(int k = 0 ; k < NB_ITERATIONS ; k++) {
				test_run_meta test_run = test_runs[r];
				int* data = test_run.data;
				int* valid_hist = test_run.valid_hist;
				int data_size = test_run.data_size;
				int min_value = test_run.min_value;
				int max_value = test_run.max_value;
				int hist_size = max_value - min_value + 1;
				int hist_size_bytes = hist_size * sizeof(int);
				int* hist_result = new int[hist_size];
				memset(hist_result, 0, hist_size_bytes);

				/* Compute histogram */
				Chronos chrono;
				chrono.start();
				if(registred_hist_function.is_cuda) {
					fcuda(data, hist_result, data_size, min_value, max_value, registred_hist_function.dg, registred_hist_function.db);
				} else {
					fomp(data, hist_result, data_size, min_value, max_value);
				}
				chrono.stop();
				time += chrono.getDeltaTime();

				/* Check */
				bool valid = check_histogramme(hist_result, valid_hist, hist_size);
				assert(valid && "Histogram not valid");

				delete[] hist_result;
			}

			std::cout << ";" << (time / NB_ITERATIONS);
		}
	}

	// Lib��ration m��moire
	for(int r = 0; r < test_runs_length; r++) {
		delete[] test_runs[r].data;
		delete[] test_runs[r].valid_hist;
	}

	chrono_all.stop();
	std::cout << std::endl << std::endl;
	chrono_all.print("Time needed for entire process: ");
}
