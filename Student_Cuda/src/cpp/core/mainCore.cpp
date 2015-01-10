#include <iostream>
#include <stdlib.h>


using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern bool useHello(void);
extern bool useSaucisson(void);
extern void use(void);
extern void isPiGPU_Ok(void);
extern bool useScalarProduct(void);
extern bool useHistogram(void);
extern bool useMontecarlo(void);
extern bool useMontecarloMulti(void);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainCore();

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/



/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainCore()
    {
    /*bool isOK = true;
    isOk &= useHello();
    use();*/

    /*bool isOK = true;
    isOK = useSaucisson();*/

    /*bool isOK = true;
    isOK = useScalarProduct();*/

    /*bool isOK = true;
    isOK = useHistogram();*/

    /*bool isOK = true;
    isOK = useMontecarlo();*/
    bool isOK = true;
    isOK = useMontecarloMulti();

    cout << "\nisOK = " << isOK << endl;
    cout << "\nEnd : mainCore" << endl;

    return isOK ? EXIT_SUCCESS : EXIT_FAILURE;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

