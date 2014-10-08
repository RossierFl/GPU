#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "GLUTImageViewers.h"

#include "Device.h"
#include "cudaTools.h"

#include "Rippling0Provider.h"
#include "RipplingProvider.h"
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
    //Image* ptrRippling = RipplingProvider::createGL();
    ImageFonctionel* ptrImageFonctionel = FractalProvider::createGL();
    // TODO : Insert  autres Images ...

    bool isAnimation = true;
    bool isSelection = true;

    //GLUTImageViewers rippling0Viewer(ptrRippling0, isAnimation, isSelection, 0, 0);
    //GLUTImageViewers ripplingViewer(ptrRippling, isAnimation, isSelection, 10, 10);
    GLUTImageViewers fractalViewer(ptrImageFonctionel, isAnimation, isSelection, 20, 20);
    // TODO : Insert here autres ImageViewers ...

    GLUTImageViewers::runALL(); // Bloquant, Tant qu'une fenetre est ouverte

    // destruction
	{
	//delete ptrRippling0;
	//delete ptrRippling;
	delete ptrImageFonctionel;

	//ptrRippling0 = NULL;
	//ptrRippling = NULL;
	ptrImageFonctionel = NULL;
	}

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

