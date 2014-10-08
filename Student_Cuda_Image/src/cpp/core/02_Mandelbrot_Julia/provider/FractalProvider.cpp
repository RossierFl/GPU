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
    int dw = 16 * 80; // =32*30=960
    int dh = 16 * 60; // =32*30=960

    float dt = 1;
    double julia = true;
    int nMin = 30;
    int nMax=100;
    double cx = -0.745;
    double cy = 0.1;
    double xMin = -1.7;
    double yMin = -1;
    double xMax = 1.7;
    double yMax = 1;
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
