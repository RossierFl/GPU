#include <iostream>
#include <math.h>

#include "FractalImage.h"
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
FractalImage::FractalImage(unsigned int w, unsigned int h, bool julia, int n, double xMin, double yMin, double xMax, double yMax,double cx,double cy) :
	ImageFonctionelMOOs_A(w, h, DomaineMath(xMin,yMin,xMax,yMax))
    {
    //Tools
    this->ptrFractalMOO=new FractalMOO(w,h,n, julia,cx,cy);

    setEnableDomaineOverlay(true);
    }

FractalImage::~FractalImage(void)
    {
    delete ptrFractalMOO;
    }

/*--------------------------------------*\
 |*		Override		*|
 \*-------------------------------------*/

/**
 * Override
 * Called automatically by the API
 */
void FractalImage::fillImageGL(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath)
    {
    ptrFractalMOO->process(ptrTabPixels,  w,  h,domaineMath);
    }

/**
 * Override
 * call periodicly by the api
 */
void FractalImage::animationStep(bool& isNeedUpdateView)
    {
    //ptrFractalMOO->animationStep();
    }

/**
 * Override
 * call periodicly by the api
 */
void FractalImage::paintPrimitives(Graphic2Ds& graphic2D)
    {
    const Font_A* ptrFont = graphic2D.getFont(TIMES_ROMAN_24);

    float r = 0;
    float g = 0;
    float b = 0;
    graphic2D.setColorRGB(r, g, b);

    // Top
	{
	//float t=ptrFractalMOO->getT();
	int n=ptrFractalMOO->getN();

	string message = "n = " + StringTools::toString(n);
	graphic2D.drawTitleTop(message, ptrFont);
	}

    // Bottom
	{
	graphic2D.drawTitleBottom("[API Image Fonctionelle] : Damier zoomable OMP", ptrFont);
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

