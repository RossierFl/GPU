#include <iostream>
#include <assert.h>
#include <math.h>

#include "MathTools.h"
#include "Vague0Image.h"
#include "StringTools.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern void launchKernelVague0(uchar4* ptrDevPixels, int w, int h, float t);

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

Vague0Image::Vague0Image(unsigned int w, unsigned int h, float dt) :
	ImageMOOs_A(w, h)
    {
    assert(getW() == getH()); // image carrer

	    // Input
    this->dt = dt;

    // Tools
    this->t = 0;
    }

Vague0Image::~Vague0Image(void)
    {
    // rien
    }

/*--------------------------------------*\
 |*		Override		*|
 \*-------------------------------------*/

/**
 * Override
 * Call automaticly by the api
 */
void Vague0Image::animationStep(bool& isNeedUpdateView)
    {
    this->t += dt;
    isNeedUpdateView = true; // true par default
    }

/**
 * Override
 * Call automaticly by the api
 */
void Vague0Image::fillImageGL(uchar4* ptrDevImageGL, int w, int h)
    {
    launchKernelVague0(ptrDevImageGL, w, h, t);
    }

/**
 * Override
 * Call automaticly by the api
 */
void Vague0Image::paintPrimitives(Graphic2Ds& graphic2D)
    {
    const Font_A* ptrFont = graphic2D.getFont(TIMES_ROMAN_24);

    float r = 1;
    float g = 0;
    float b = 0;

    graphic2D.setColorRGB(r, g, b);

    // top
	{
	string message = "t = " + StringTools::toString(t);
	graphic2D.drawTitleTop(message, ptrFont);
	}

    // bottom
	{
	graphic2D.drawTitleBottom("[API Image Cuda] : VagueImage warmup CUDA", ptrFont);
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
