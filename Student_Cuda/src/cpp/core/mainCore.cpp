#include <iostream>
#include <stdlib.h>

using std::cout;
using std::endl;

//extern bool useHello();
//extern void useAdd();
//extern bool usePI();
//extern bool useMontecarlo();
extern void useHistogramme();


int mainCore() {
	bool isOk = true;
	//isOk &= usePI();
	//isOk &= useMontecarlo();
	useHistogramme();

	cout << "\nisOK = " << isOk << endl;
	cout << "\nEnd : mainCore" << endl;
	return isOk ? EXIT_SUCCESS : EXIT_FAILURE;
}

