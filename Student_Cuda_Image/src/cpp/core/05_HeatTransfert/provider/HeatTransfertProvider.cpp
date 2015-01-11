#include "HeatTransfertProvider.h"
#include "MathTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-----------------*\
 |*	static	   *|
 \*----------------*/

HeatTransfert* HeatTransfertProvider::create()
    {
    int dw = 800; // =32*30=960
    int dh = 800; // =32*30=960
    float k = 0.25;

    /*double c1 = -0.12;
    double c2 = 0.85;

    double x1 = -2.0;
    double y1 = -2.0;
    double x2 = 2.0;
    double y2 = 2.0;

    // animation para
    float dt = (100.0-30.0)/400.0;

    float epsilonx = 1.0e-3;
    float epsilonf = 1.0e-3;
    float epsilonxstar = 1.0e-3;*/
    printf("create\n");
    HeatTransfert* transert = new HeatTransfert(dw, dh,k);
    printf("createDone\n");
    return transert;
    }

Image* HeatTransfertProvider::createGL(void)
    {
    printf("createGL\n");
    ColorRGB_01* ptrColorTitre=new ColorRGB_01(0,0,0);
    Image* ptrReturn = new Image(create(),ptrColorTitre); // both ptr destroy by destructor of ImageFonctionel
    printf("createGLDone\n");
    return ptrReturn;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
