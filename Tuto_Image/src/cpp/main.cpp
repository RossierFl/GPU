#include <iostream>

#include "GLUTImageViewers.h"

#include "VagueProvider.h"
#include "DamierProvider.h"
#include "EventProvider.h"

#include "MyDisplayableProvider.h"
#include "MyGLUTWindow.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported		*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int main(int argc, char** argv);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static int mainGL(void);


/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int main(int argc, char** argv)
    {
    cout << "main" << endl;

    GLUTImageViewers::init(argc, argv); // call once

    return mainGL(); // Bloquant, Tant qu'une fenetre est ouverte
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

int mainGL(void)
    {
    bool isAnimation = true;
    bool isSelectionEnable = true;

    VagueImage* ptrVague = VagueProvider::create();
    DamierImage* ptrDamier = DamierProvider::create();
    EventImage* ptrEvent = EventProvider::create();

    // ImageViewer
    GLUTImageViewers vagueViewer(ptrVague, isAnimation, false, 0, 0);
    GLUTImageViewers damierViewer(ptrDamier, isAnimation, isSelectionEnable, 40, 40);
    GLUTImageViewers eventViewer(ptrEvent, isAnimation, false, 80, 80);
    // Insert here other ImageViewer ...

    // OpenGLViewer (Advanced)
    Displayable_A* ptrMyDisplayable = MyDisplayableProvider::createGL();
    MyGLUTWindow myGlutWindow(ptrMyDisplayable, "Triangle OpenGL Custom Displayable", 600, 600, 100, 100); // scene OpenGL // (w,h,px,py)

    GLUTImageViewers::runALL();  // Bloquant, Tant qu'une fenetre est ouverte

    // destruction
	{
	delete ptrVague;
	delete ptrDamier;
	delete ptrEvent;

	ptrVague = NULL;
	ptrDamier = NULL;
	ptrEvent = NULL;
	}

    return EXIT_SUCCESS;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

