#include <iostream>
#include <assert.h>
#include <omp.h>
#include <math.h>

#include "MathTools.h"
#include "ConvolutionImage.h"
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

ConvolutionImage::ConvolutionImage(unsigned int w, unsigned int h, float dt) :
	ImageMOOs_A(w, h)
    {
   // assert(w==h); // Image carrer

    this->ptrConvolutionMOO=new ConvolutionMOO(w,h,dt);
    }

ConvolutionImage::~ConvolutionImage(void)
    {
    delete ptrConvolutionMOO;
    }

/*--------------------------------------*\
 |*		Override		*|
 \*-------------------------------------*/

/**
 * Override
 * call periodicly by the api
 */
void ConvolutionImage::fillImageGL(uchar4* ptrTabPixels, int w, int h)
    {
    ptrConvolutionMOO->process(ptrTabPixels,w,h);
    }

/**
 * Override
 * call periodicly by the api
 */
void ConvolutionImage::animationStep(bool& isNeedUpdateView)
    {
    ptrConvolutionMOO->animationStep();
    }

/**
 * Override
 * call periodicly by the api
 */
void ConvolutionImage::paintPrimitives(Graphic2Ds& graphic2D)
    {
    const Font_A* ptrFont = graphic2D.getFont(TIMES_ROMAN_24);

    float r = 1;
    float g = 0;
    float b = 0;
    graphic2D.setColorRGB(r, g, b);

    // Top
	{
	float t=ptrConvolutionMOO->getT();

	string message = "It's up to you!  t= " + StringTools::toString(t);
	graphic2D.drawTitleTop(message, ptrFont);
	}

    // Bottom
	{
	graphic2D.drawTitleBottom("Convolution OMP", ptrFont);
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
