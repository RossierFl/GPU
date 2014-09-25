#include <iostream>
#include <assert.h>
#include <math.h>

#include "Image.h"
#include "StringTools.h"
#include "MathTools.h"

using std::cout;
using std::endl;

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

Image::Image(Animable_I* ptrAnimable,ColorRGB_01* ptrColorTitreRGB) :
	ImageMOOs_A(ptrAnimable->getW(), ptrAnimable->getH())
    {
    this->ptrAnimable = ptrAnimable;
    this->ptrColorTitreRGB=ptrColorTitreRGB;
    }

Image::~Image(void)
    {
    delete ptrAnimable;
    }

/**
 * Override
 */
void Image::animationStep(bool& isNeedUpdateView)
    {
    // cout << "[CBI] : Image : animationStep" <<endl;

    ptrAnimable->animationStep();
    isNeedUpdateView = true; // true par default
    }

/**
 * Override
 */
void Image::fillImageGL(uchar4* ptrDevImageGL, int w, int h)
    {
    // cout << "[CBI] : Image : fillImageGL" <<endl;

    ptrAnimable->runGPU(ptrDevImageGL);
    }

/**
 * Override
 */
void Image::paintPrimitives(Graphic2Ds& graphic2D) // redefinition
    {
    const Font_A* ptrfont = graphic2D.getFont(TIMES_ROMAN_24);

    float r = ptrColorTitreRGB->r;
    float g = ptrColorTitreRGB->g;
    float b = ptrColorTitreRGB->b;
    graphic2D.setColorRGB(r, g, b);

    // top
	{
	float t = ptrAnimable->getT();
	string message = "t = " + StringTools::toString(t);
	graphic2D.drawTitleTop(message, ptrfont);
	}

    // bottom
	{
	string title = ptrAnimable->getTitle();
	graphic2D.drawTitleBottom(title, ptrfont);
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
