#include <iostream>
#include <math.h>

#include "ManJulImage.h"
#include "StringTools.h"
#include "OmpTools.h"
#include "MathTools.h"
#include "IndiceTools.h"
#include "ColorTools.h"

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

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

/**
 * DomaineMaths(0, 0, 2 * PI, 2 * PI) : par exemple, why not celui l�!
 */
ManJulImage::ManJulImage(unsigned int w, unsigned int h, float dt, int n, int isJulia,
	double c1, double c2,double x1,double y1,double x2,double y2) :
		ImageFonctionelMOOs_A(w, h, DomaineMath(x1, y1, x2, y2))
    {
    //Tools
    this->ptrManJulMoo=new ManJulMOO(w,h,dt,n,isJulia,c1,c2);

    setEnableDomaineOverlay(true);
    }

ManJulImage::~ManJulImage(void)
    {
    delete ptrManJulMoo;
    }

/*--------------------------------------*\
 |*		Override		*|
 \*-------------------------------------*/

/**
 * Override
 * Called automatically by the API
 */
void ManJulImage::fillImageGL(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath)
    {
    ptrManJulMoo->process(ptrTabPixels,  w,  h,domaineMath);
    }

/**
 * Override
 * call periodicly by the api
 */
void ManJulImage::animationStep(bool& isNeedUpdateView)
    {
    ptrManJulMoo->animationStep();
    }

/**
 * Override
 * call periodicly by the api
 */
void ManJulImage::paintPrimitives(Graphic2Ds& graphic2D)
    {
    const Font_A* ptrFont = graphic2D.getFont(TIMES_ROMAN_24);

    float r = 0;
    float g = 0;
    float b = 0;
    graphic2D.setColorRGB(r, g, b);

    // Top
    {
	float t=ptrManJulMoo->getT();
	int n=ptrManJulMoo->getN();

	string message = "t = " + StringTools::toString(t) + "  n = " + StringTools::toString(n);
	graphic2D.drawTitleTop(message, ptrFont);
    }

    // Bottom
    {
    graphic2D.drawTitleBottom("[API Image Fonctionelle] : Mandelbrot Julia zoomable OMP", ptrFont);
    }
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

