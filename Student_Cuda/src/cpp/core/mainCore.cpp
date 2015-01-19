#include <iostream>
#include <stdlib.h>

using std::cout;
using std::endl;

extern bool useHello();
extern bool usePI();
extern bool useMontecarlo();
extern bool useMontecarloMultiGPU();
extern bool useHistogramme();
extern bool useScalarProduct();
extern void histogramme_extended();


int mainCore() {
	histogramme_extended();
	return EXIT_SUCCESS;
}

