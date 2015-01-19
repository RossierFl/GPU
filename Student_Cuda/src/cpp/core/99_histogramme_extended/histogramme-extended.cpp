#define DEBUG 1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <string>
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
extern void hist_omp_reduction(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE);
extern void hist_cuda_gm(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE);
extern void hist_cuda_sm(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE);

typedef void (*hist_function) (int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE);
typedef struct hist_function_meta {
	hist_function function;
	string function_name;
} hist_function_meta;

typedef struct test_run_meta {
	int data_size;
	int min_value;
	int max_value;
	int* data;
} test_run_meta;

void histogramme_extended() {
	// Registrer functions
	// @formatter:off
	hist_function_meta registred_hist_functions[] = {
		{ &hist_sequential, "hist_sequential" },
		{ &hist_omp_entrelacer_tabpromotion, "hist_omp_entrelacer_tabpromotion" },
		{ &hist_omp_entrelacer_critical_withouttab, "hist_omp_entrelacer_critical_withouttab" },
		{ &hist_omp_entrelacer_critical_withtab, "hist_omp_entrelacer_critical_withtab" },
		{ &hist_omp_entrelacer_atomic_withouttab, "hist_omp_entrelacer_atomic_withouttab" },
		{ &hist_omp_entrelacer_atomic_withtab, "hist_omp_entrelacer_atomic_withtab" },
		{ &hist_omp_for_critical_withouttab, "hist_omp_for_critical_withouttab" },
		{ &hist_omp_for_atomic_withouttab, "hist_omp_for_atomic_withouttab" },
		{ &hist_omp_for_tabpromotion, "hist_omp_for_tabpromotion" },
		//{ &hist_omp_reduction, "hist_omp_reduction" },
		{ &hist_cuda_gm, "hist_cuda_gm" },
		{ &hist_cuda_sm, "hist_cuda_sm" }
	};
	int registred_hist_functions_length = 11;
	// @formatter:on

	// Register runs
	test_run_meta test_runs[] = {
		{ 2000, 0, 5, NULL },
		{ 20000000, 0, 5, NULL },
		{ 2000, 0, 200, NULL },
		{ 20000000, 0, 200, NULL }
	};
	int test_runs_length = 4;
	for(int r = 0; r < test_runs_length; r++) {
		std::cout << "Generating data[" << (r+1) << "/" << test_runs_length << "]..." << std::endl;
		test_runs[r].data = new int[test_runs[r].data_size];
		generateData(test_runs[r].data, test_runs[r].data_size, test_runs[r].min_value, test_runs[r].max_value);
	}

	// Header
	std::cout << std::endl;
	for(int r = 0; r < test_runs_length; r++) {

		test_run_meta test_run = test_runs[r];
		int data_size = test_run.data_size;
		int min_value = test_run.min_value;
		int max_value = test_run.max_value;
		int hist_size = max_value - min_value + 1;

		std::ostringstream os;
		os << ";[size=" << data_size << ", min=" << min_value << ", max=" << max_value << "]";
		std::cout << os.str().c_str();
	}

	// Compute
	for(int i = 0; i < registred_hist_functions_length; i++) {
		hist_function f = registred_hist_functions[i].function;
		string fname = registred_hist_functions[i].function_name;
		std::cout << std::endl;
		std::cout << fname;

		int found = fname.find("cuda");
		if (found == std::string::npos)
			continue;

		// Compute histogrammes for each registred runs
		for(int r = 0; r < test_runs_length; r++) {

			test_run_meta test_run = test_runs[r];
			int* data = test_run.data;
			int data_size = test_run.data_size;
			int min_value = test_run.min_value;
			int max_value = test_run.max_value;
			int hist_size = max_value - min_value + 1;
			int hist_size_bytes = hist_size * sizeof(int);
			int* hist_result = new int[hist_size];
			memset(hist_result, 0, hist_size_bytes);

			Chronos chrono;
			f(data, hist_result, data_size, min_value, max_value);
			chrono.stop();
			//std::ostringstream os;
			//os << "time for run[size=" << data_size << ", min=" << min_value << ", max=" << max_value << "] : " << chrono.getDeltaTime();
			std::cout << ";" << chrono.getDeltaTime();

			delete[] hist_result;
		}
	}

	// Libération mémoire
	for(int r = 0; r < test_runs_length; r++) {
		delete[] test_runs[r].data;
	}
}
