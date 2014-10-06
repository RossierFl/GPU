#include <iostream>

#include "MathTools.h"
#include "GLUTImageViewers.h"

#include "RipplingProvider.h"
#include "ManJulProvider.h"

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

static int run(void);

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

    return run(); // Bloquant, Tant qu'une fenetre est ouverte
    }

int run(void)
    {
    bool isAnimation = true;
    bool isSelectionEnable = false;

    //RipplingImage* ptrRippling = RipplingProvider::create();
    ManJulImage* ptrManJul = ManJulProvider::create();

    //GLUTImageViewers ripplingViewer(ptrRippling, isAnimation, isSelectionEnable, 20, 20);
    GLUTImageViewers manJulViewer(ptrManJul, isAnimation, isSelectionEnable, 20, 20);

    GLUTImageViewers::runALL(); // Bloquant, Tant qu'une fenetre est ouverte

    // destruction
	{
	//delete ptrRippling;
	delete ptrManJul;
	//ptrRippling = NULL;
	ptrManJul = NULL;
	}

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

