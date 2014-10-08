#include <iostream>
#include <assert.h>
#include <omp.h>
#include <math.h>

#include "VagueImage.h"
#include "MathTools.h"
#include "StringTools.h"
#include "OmpTools.h"
#include "IndiceTools.h"

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

VagueImage::VagueImage(unsigned int w, unsigned int h, float dt) :
	ImageMOOs_A(w, h)
    {
    this->ptrVagueMOO=new VagueMOO(w,h,dt);
    }

VagueImage::~VagueImage(void)
    {
    delete ptrVagueMOO;
    }

/*--------------------------------------*\
 |*		Override		*|
 \*-------------------------------------*/

/**
 * Override : call periodicly by the api
 */
void VagueImage::fillImageGL(uchar4* ptrTabPixels, int w, int h)
    {
    ptrVagueMOO->process(ptrTabPixels,w,h);
    }

/**
 * Override : call periodicly by the api
 */
void VagueImage::animationStep(bool& isNeedUpdateView)
    {
    ptrVagueMOO->animationStep();
    }

/**
 * Override call periodicly by the api
 */
void VagueImage::paintPrimitives(Graphic2Ds& graphic2D)
    {
    const Font_A* ptrFont = graphic2D.getFont(TIMES_ROMAN_24);

    float r = 1;
    float g = 0;
    float b = 0;
    graphic2D.setColorRGB(r, g, b);

    // Top
	{
	float t=ptrVagueMOO->getT();
	float dt=ptrVagueMOO->getDT();

	string message = "t= " + StringTools::toString(t) + " dt=" + StringTools::toString(dt);
	graphic2D.drawTitleTop(message, ptrFont);
	}

    // Bottom
	{
	graphic2D.drawTitleBottom("API Image : Vague OMP", ptrFont);
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

