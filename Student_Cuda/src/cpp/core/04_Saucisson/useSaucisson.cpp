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

//extern bool helloCuda(void);
extern bool isSaucisson_Ok(int n);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useSaucisson(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/



/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/



bool useSaucisson(void)
    {
    cout << endl << "[Hello]" << endl;

    bool isOk = true;

    //isOk&= helloCuda();
    int n = 10000;
    isOk&= isSaucisson_Ok(n);

    return true;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

