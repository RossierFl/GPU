#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "GLUTImageViewers.h"

#include "Device.h"
#include "cudaTools.h"

#include "Rippling0Provider.h"
#include "RipplingProvider.h"
#include "MandelbrotJuliaProvider.h"
#include "MandelbrotJuliaProviderMultiGPU.h"

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainGL(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainGL(void)
    {
    Rippling0Image* ptrRippling0 = Rippling0Provider::createGL();
    Image* ptrRippling = RipplingProvider::createGL();
    // TODO : Insert  autres Images ...
    //ImageFonctionel* ptrMandelbrotJulia = MandelbrotJuliaProvider::createGL();

    ImageFonctionel* ptrMandelbrotJuliaMultiGPU =  MandelbrotJuliaProviderMultiGPU::createGL();


    bool isAnimation = true;
    bool isSelection = true;

   // GLUTImageViewers rippling0Viewer(ptrRippling0, isAnimation, isSelection, 0, 0);
  //  GLUTImageViewers ripplingViewer(ptrRippling, isAnimation, isSelection, 10, 10);
    // TODO : Insert here autres ImageViewers ...
    //GLUTImageViewers mandelbrotJuliaViewer(ptrMandelbrotJulia, isAnimation, isSelection, 0, 0);

    GLUTImageViewers mandelbrotJuliaViewerMultiGPU(ptrMandelbrotJuliaMultiGPU, isAnimation, isSelection, 0, 0);

    GLUTImageViewers::runALL(); // Bloquant, Tant qu'une fenetre est ouverte

    // destruction
	{
	delete ptrRippling0;
	delete ptrRippling;
	delete ptrMandelbrotJuliaMultiGPU;
	//delete ptrMandelbrotJulia;

	ptrRippling0 = NULL;
	ptrRippling = NULL;
	ptrMandelbrotJuliaMultiGPU=NULL;
	//ptrMandelbrotJulia = NULL;
	}

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

