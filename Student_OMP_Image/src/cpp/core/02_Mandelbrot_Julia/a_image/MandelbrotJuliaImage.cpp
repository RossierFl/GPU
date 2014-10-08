#include <iostream>
#include <math.h>

#include "MandelbrotJuliaImage.h"
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
MandelbrotJuliaImage::MandelbrotJuliaImage(unsigned int w, unsigned int h, float dt, int n, double xMin,double xMax,double yMin,double yMax,bool isJulia,double cX=0,double cY=0) :
	ImageFonctionelMOOs_A(w, h, cpu::DomaineMath(xMin,yMin,xMax, yMax))
    {
    //Tools
    this->ptrMandelbrotJuliaMOO=new MandelbrotJuliaMOO(w,h,dt,n,isJulia,cX,cY);

    setEnableDomaineOverlay(true);
    }

MandelbrotJuliaImage::~MandelbrotJuliaImage(void)
    {
    delete ptrMandelbrotJuliaMOO;
    }

/*--------------------------------------*\
 |*		Override		*|
 \*-------------------------------------*/

/**
 * Override
 * Called automatically by the API
 */
void MandelbrotJuliaImage::fillImageGL(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath)
    {
    ptrMandelbrotJuliaMOO->process(ptrTabPixels,  w,  h,domaineMath);
    }

/**
 * Override
 * call periodicly by the api
 */
void MandelbrotJuliaImage::animationStep(bool& isNeedUpdateView)
    {
    ptrMandelbrotJuliaMOO->animationStep();
    }

/**
 * Override
 * call periodicly by the api
 */
void MandelbrotJuliaImage::paintPrimitives(Graphic2Ds& graphic2D)
    {
    const Font_A* ptrFont = graphic2D.getFont(TIMES_ROMAN_24);

    float r = 0;
    float g = 0;
    float b = 0;
    graphic2D.setColorRGB(r, g, b);

    // Top
	{
	float t=ptrMandelbrotJuliaMOO->getT();
	int n=ptrMandelbrotJuliaMOO->getN();

	string message = "t = " + StringTools::toString(t) + "  n = " + StringTools::toString(n);
	graphic2D.drawTitleTop(message, ptrFont);
	}

    // Bottom
	{
	graphic2D.drawTitleBottom("[API Image Fonctionelle] : MandelbrotJulia zoomable OMP", ptrFont);
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

