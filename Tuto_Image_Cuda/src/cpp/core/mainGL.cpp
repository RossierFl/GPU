#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "GLUTImageViewers_GPU.h"


#include "Device.h"
#include "cudaTools.h"

#include "Vague0Provider.h"
#include "VagueProvider.h"
#include "DamierProvider.h"
#include "EventProvider.h"
#include "MyDisplayableProvider.h"
#include "MyGLUTWindow.h"

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
    Vague0Image* ptrVague0=Vague0Provider::createGL(); //bad technique

    Image* ptrVague=VagueProvider::createGL();
    ImageFonctionel* ptrDamier=DamierProvider::createGL();
    ImageFonctionel* ptrEvent=EventProvider::createGL();
    Displayable_A* ptrMyDisplayable=MyDisplayableProvider::createGL();

    bool isAnimation = true;
    bool isSelection = true;

    // ImageViewer
    GLUTImageViewers vague0Viewer(ptrVague0, isAnimation, false, 0, 0);
    GLUTImageViewers vagueViewer(ptrVague, isAnimation, false, 25,25);
    GLUTImageViewers damierlViewer(ptrDamier, isAnimation, isSelection, 50, 50);
    GLUTImageViewers eventViewer(ptrEvent, isAnimation, isSelection, 75, 75);
    // Insert here other ImageViewer ...

    // OpenGLViewer
    MyGLUTWindow myGlutWindow(ptrMyDisplayable,"Triangle OpenGL, Custom Displayable",600,600,100,100);// scene OpenGL // (w,h,px,py)

    GLUTImageViewers::runALL(); // Bloquant, Tant qu'une fenetre est ouverte

    // destruction
	{
	delete ptrVague0;
	delete ptrVague;
	delete ptrDamier;
	delete ptrEvent;
	delete ptrMyDisplayable;

	ptrVague0 = NULL;
	ptrVague=NULL;
	ptrDamier = NULL;
	ptrEvent = NULL;
	ptrMyDisplayable = NULL;
	}

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/




/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

