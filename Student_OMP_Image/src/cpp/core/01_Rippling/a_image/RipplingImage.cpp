#include <iostream>
#include <assert.h>
#include <omp.h>
#include <math.h>

#include "MathTools.h"
#include "RipplingImage.h"
#include "StringTools.h"
#include "OmpTools.h"

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

RipplingImage::RipplingImage(unsigned int w, unsigned int h, float dt) :
	ImageMOOs_A(w, h)
    {
    assert(w==h); // Image carrer

    this->ptrRipplingMOO=new RipplingMOO(w,h,dt);
    }

RipplingImage::~RipplingImage(void)
    {
    delete ptrRipplingMOO;
    }

/*--------------------------------------*\
 |*		Override		*|
 \*-------------------------------------*/

/**
 * Override
 * call periodicly by the api
 */
void RipplingImage::fillImageGL(uchar4* ptrTabPixels, int w, int h)
    {
    ptrRipplingMOO->process(ptrTabPixels,w,h);
    }

/**
 * Override
 * call periodicly by the api
 */
void RipplingImage::animationStep(bool& isNeedUpdateView)
    {
    ptrRipplingMOO->animationStep();
    }

/**
 * Override
 * call periodicly by the api
 */
void RipplingImage::paintPrimitives(Graphic2Ds& graphic2D)
    {
    const Font_A* ptrFont = graphic2D.getFont(TIMES_ROMAN_24);

    float r = 1;
    float g = 0;
    float b = 0;
    graphic2D.setColorRGB(r, g, b);

    // Top
	{
	float t=ptrRipplingMOO->getT();

	string message = "Emmanuel Dafflon - Rippling OMP t= " + StringTools::toString(t);
	graphic2D.drawTitleTop(message, ptrFont);
	}

    // Bottom
	{
	graphic2D.drawTitleBottom("Rippling OMP", ptrFont);
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
