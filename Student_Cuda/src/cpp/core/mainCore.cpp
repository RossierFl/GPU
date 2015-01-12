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


int mainCore() {
	bool isOk = true;

	//isOk &= useScalarProduct();
	isOk &= useHistogramme();
	//isOk &= usePI();
	//isOk &= useMontecarlo();
	//isOk &= useMontecarloMultiGPU();

	cout << "\nisOK = " << isOk << endl;
	cout << "\nEnd : mainCore" << endl;
	return isOk ? EXIT_SUCCESS : EXIT_FAILURE;
}

