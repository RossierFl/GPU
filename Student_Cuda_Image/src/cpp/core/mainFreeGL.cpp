#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "AnimateurFreeGL.h"
#include "AnimateurFonctionelFreeGL.h"
#include "Device.h"
#include "cudaTools.h"
#include "FractalProvider.h"

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern int rippling0FreeGL(int itmax); // bas technique

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainFreeGL(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainFreeGL(void)
    {
    cout << "\n[FPS] :  Free GL, please wait ..." << endl;

    //rippling0FreeGL(1000); // bad technique
    Fractal* ptrFractal = FractalProvider::create();

    AnimateurFonctionelFreeGL fractalFreeGL(ptrFractal);
    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

