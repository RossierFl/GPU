#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "GLUTImageViewers.h"

#include "Device.h"
#include "cudaTools.h"

#include "Rippling0Provider.h"
#include "RipplingProvider.h"
#include "MandelbrotJuliaProvider.h"
#include "MandelbrotJuliaProviderMGPU.h"
#include "NewtonProvider.h"
#include "RaytracingProvider.h"
#include "ConvolutionProvider.h"
#include "HeatTransfertProvider.h"

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
    //Rippling0Image* ptrRippling0 = Rippling0Provider::createGL();
    Image* ptrRippling = RipplingProvider::createGL();
    Image* ptrRay = RaytracingProvider::createGL();
    Image* ptrHeatTransfert = HeatTransfertProvider::createGL();
    Image* ptrConvolution = ConvolutionProvider::createGL();
    ImageFonctionel* ptrMandelbrot = MandelbrotJuliaProvider::createGL();
    ImageFonctionel* ptrMandelbrotMGPU = MandelbrotJuliaProviderMGPU::createGL();
    ImageFonctionel* ptrNewton = NewtonProvider::createGL();

    bool isAnimation = true;
    bool isSelection = true;

    //GLUTImageViewers rippling0Viewer(ptrRippling0, isAnimation, isSelection, 0, 0);
    //GLUTImageViewers ripplingViewer(ptrRippling, isAnimation, isSelection, 10, 10);
    //GLUTImageViewers mandelBrotViewer(ptrMandelbrot,isAnimation,isSelection,10,10);
    //GLUTImageViewers mandelBrotMGPUViewer(ptrMandelbrotMGPU,isAnimation,isSelection,10,10);
    //GLUTImageViewers newtonViewer(ptrNewton,isAnimation,isSelection,10,10);
    //GLUTImageViewers rayViewer(ptrRay,isAnimation,isSelection,10,10);
    GLUTImageViewers heatViewer(ptrHeatTransfert,isAnimation,isSelection,10,10);
    //GLUTImageViewers convolViewer(ptrConvolution,isAnimation,isSelection,10,10);
    // TODO : Insert here autres ImageViewers ...

    GLUTImageViewers::runALL(); // Bloquant, Tant qu'une fenetre est ouverte

    // destruction
	{
	//delete ptrRippling0;
	delete ptrRippling;
	delete ptrMandelbrot;
	delete ptrMandelbrotMGPU;
	delete ptrNewton;
	delete ptrRay;
	delete ptrHeatTransfert;
	delete ptrConvolution;

	//ptrRippling0 = NULL;
	ptrRippling = NULL;
	ptrMandelbrot = NULL;
	ptrMandelbrotMGPU = NULL;
	ptrNewton = NULL;
	ptrRay = NULL;
	ptrHeatTransfert = NULL;
	ptrConvolution = NULL;
	}

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

