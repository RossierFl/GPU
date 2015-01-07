#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "GLUTImageViewers.h"

#include "Device.h"
#include "cudaTools.h"

#include "Rippling0Provider.h"
#include "RipplingProvider.h"
#include "FractalProvider.h"
#include "NewtonProvider.h"
#include "RayTracingProvider.h"

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
    ImageFonctionel* ptrFractal = FractalProvider::createGL();
    ImageFonctionel* ptrNewton = NewtonProvider::createGL();
    //ImageFonctionel* ptrRayTracing = ::createGL();
    Image* ptrRayTracing = RayTracingProvider::createGL();

    // TODO : Insert  autres Images ...

    bool isAnimation = true;
    bool isSelection = true;

    //GLUTImageViewers rippling0Viewer(ptrRippling0, isAnimation, isSelection, 0, 0);
    GLUTImageViewers ripplingViewer(ptrRippling, isAnimation, isSelection, 10, 10);
    GLUTImageViewers fractalViewer(ptrFractal,isAnimation,isSelection,20,20);
    GLUTImageViewers newtonViewer(ptrNewton,isAnimation,isSelection,20,20);
    GLUTImageViewers rayTracingViewer(ptrRayTracing,isAnimation,isSelection,20,20);

    // TODO : Insert here autres ImageViewers ...

    GLUTImageViewers::runALL(); // Bloquant, Tant qu'une fenetre est ouverte

    // destruction
	{
	//delete ptrRippling0;
	delete ptrRippling;
	delete ptrFractal;
	delete ptrNewton;
	delete ptrRayTracing;
	//ptrRippling0 = NULL;
	ptrRippling = NULL;
	ptrFractal = NULL;
	ptrNewton = NULL;
	ptrRayTracing=NULL;
	}

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

