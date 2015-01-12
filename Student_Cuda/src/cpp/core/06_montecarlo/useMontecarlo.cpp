#include <iostream>
#include <limits.h>

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern bool isMontecarlo_Ok(long n, float xMin, float xMax, int m);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useMontecarlo(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/



/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/



bool useMontecarlo(void)
    {
    cout << endl << "[Montecarlo]" << endl;

    bool isOk = true;

    long n = 6000000;
    float xMin = 0.0;
    float xMax = 2.0;
    int m = 1;
    isOk&= isMontecarlo_Ok(n, xMin, xMax, m);

    return isOk;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

