#include <iostream>
#include <stdlib.h>

using std::cout;
using std::endl;

extern bool usePI();
//extern bool useHello();
//extern void useAdd();

int mainCore() {
	bool isOk = true;
	isOk &= usePI();

	cout << "\nisOK = " << isOk << endl;
	cout << "\nEnd : mainCore" << endl;
	return isOk ? EXIT_SUCCESS : EXIT_FAILURE;
}

