#include <iostream>
#include <assert.h>
#include <math.h>

#include "MathTools.h"
#include "StringTools.h"

#include "Rippling0Image.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern void launchKernelRippling0(uchar4* ptrDevPixels, int w, int h, float t);

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

Rippling0Image::Rippling0Image(unsigned int w, unsigned int h, float dt) :
	ImageMOOs_A(w, h)
    {
    assert(getW() == getH()); // image carrer

	    // Input
    this->dt = dt;

    // Tools
    this->t = 0;
    }

Rippling0Image::~Rippling0Image(void)
    {
    // rien
    }

/*--------------------------------------*\
 |*		Redefinition		*|
 \*-------------------------------------*/

/**
 * Call automaticly by the api
 */
void Rippling0Image::animationStep(bool& isNeedUpdateView) // Override
    {
    this->t += dt;
    isNeedUpdateView = true; // true par default
    }

/**
 * Call automaticly by the api
 */
void Rippling0Image::fillImageGL(uchar4* ptrDevImageGL, int w, int h) // Override
    {
    launchKernelRippling0(ptrDevImageGL, w, h, t);
    }

/**
 * Call automaticly by the api
 */
void Rippling0Image::paintPrimitives(Graphic2Ds& graphic2D) // Override
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
	graphic2D.drawTitleBottom("Rippling warmup CUDA", ptrFont);
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
