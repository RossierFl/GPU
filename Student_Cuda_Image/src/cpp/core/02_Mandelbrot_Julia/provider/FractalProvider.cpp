#include "FractalProvider.h"
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

Fractal* FractalProvider::create()
    {
    int dw = 16 * 60; // =32*30=960
    int dh = 16 * 60; // =32*30=960

    int dt = 1;
    double julia = false;
    int nMin = 40;
    int nMax=300;
    double cx = 0.745;
    double cy = 0.1;
    double xMin = -1.3968;
    double yMin = -0.03362;
    double xMax = -1.3578;
    double yMax = 0.001397;
    //int w, int h, float dt, int n,bool julia,double cx,double cy,double xMin, double xMax, double yMin, double yMax
    return new Fractal(dw, dh, dt, nMin,nMax,julia,cx,cy,xMin,xMax,yMin,yMax);
    }

ImageFonctionel* FractalProvider::createGL(void)
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
