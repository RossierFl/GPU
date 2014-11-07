#include <iostream>
#include <assert.h>
#include <omp.h>
#include <math.h>

#include "MathTools.h"
#include "FractalImage.h"
#include "StringTools.h"
#include "OmpTools.h"
#include "IndiceTools.h"
#include "ColorTools.h"
#include "ImageFonctionelMOOs_A.h"

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

FractalImage::FractalImage(unsigned int w, unsigned int h, unsigned int nMin, unsigned int nMax, double cx, double cyi, bool isJulia, double x0, double x1, double y0, double y1) :
	ImageFonctionelMOOs_A(w, h, DomaineMath(x0,y0,x1,y1))
    {
    this->ptrFractalMOO=new FractalMOO(w,h,nMin,nMax,cx,cyi,isJulia);

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
 * call periodicly by the api
 */
void FractalImage::fillImageGL(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath)
    {
    ptrFractalMOO->process(ptrTabPixels,w,h, domaineMath);
    }

/**
 * Override
 * call periodicly by the api
 */
void FractalImage::animationStep(bool& isNeedUpdateView)
    {
    ptrFractalMOO->animationStep();
    }

/**
 * Override
 * call periodicly by the api
 */
void FractalImage::paintPrimitives(Graphic2Ds& graphic2D)
    {
    const Font_A* ptrFont = graphic2D.getFont(TIMES_ROMAN_24);

    float r = 1;
    float g = 1;
    float b = 1;
    graphic2D.setColorRGB(r, g, b);

    // Top
	{
	float t=ptrFractalMOO->getT();

	string message = "Emmanuel Dafflon - Fractal OMP t= " + StringTools::toString(t);
	graphic2D.drawTitleTop(message, ptrFont);
	}

    // Bottom
	{
	graphic2D.drawTitleBottom("Fractal OMP", ptrFont);
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
