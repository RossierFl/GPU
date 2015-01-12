#include <iostream>
#include <stdlib.h>
#include "PiHost.h"
#include "ProduitScalaireHost.h"
#include "HistogrammeHost.h"
#include "montecarloHost.h"


using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern bool useHello(void);
extern void useAdd();

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
    bool isOk = true;
    //isOk &= useHello();
    //useAdd();
   // PiHost::MyCalculatePI();
 //   ProduitScalaireHost::MyCalculateProduitScalaire();
  //  HistogrammeHost::MyCalculateHistogramme();

    MontecarloHost::myCalculateMontecarlo();
   // cout << "\nisOK = " << isOk << endl;
  //  cout << "\nEnd : mainCore" << endl;

    return isOk ? EXIT_SUCCESS : EXIT_FAILURE;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

