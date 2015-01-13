#include "MandelbrotJuliaProvider.h"
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

MandelbrotJulia* MandelbrotJuliaProvider::create()
    {
    int dw = 16 * 60; // =32*30=960
    int dh = 16 * 60; // =32*30=960

    int n = 102;

    double c1 = -0.12;
    double c2 = 0.85;

    double x1 = -1.3968;
    double y1 = -0.03362;
    double x2 = -1.3578;
    double y2 = 0.0013973;

    // animation para
    float dt = (100.0-30.0)/400.0;

    int isJulia = 1;

    if(isJulia == 0)
	{
	x1 = -1.3968;
	y1 = -0.03362;
	x2 = -1.3578;
	y2 = 0.0013973;
	return new MandelbrotJulia(dw, dh, dt, n, isJulia,c1,c2,x1,y1,x2,y2);
	}
    else
	{
	x1 = -1.3;
	y1 = -1.4;
	x2 = 1.3;
	y2 = 1.4;
	return new MandelbrotJulia(dw, dh, dt, n, isJulia,c1,c2,x1,y1,x2,y2);
	}

    return new MandelbrotJulia(dw, dh, dt, n, isJulia,c1,c2,x1,y1,x2,y2);
    }

ImageFonctionel* MandelbrotJuliaProvider::createGL(void)
    {
    ColorRGB_01* ptrColorTitre=new ColorRGB_01(0,0,0);

    return new ImageFonctionel(create(),ptrColorTitre); // both ptr destroy by destructor of ImageFonctionel
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
