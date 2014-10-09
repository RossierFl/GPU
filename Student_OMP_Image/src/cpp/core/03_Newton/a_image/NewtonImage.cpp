#include <iostream>
#include <math.h>

#include "NewtonImage.h"
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
NewtonImage::NewtonImage(unsigned int w, unsigned int h, float dt, int n) :
	ImageFonctionelMOOs_A(w, h, DomaineMath(0, 0, 2 * PI, 2 * PI))
    {
    //Tools
    this->ptrNewtonMOO=new NewtonMOO(w,h,dt,n);

    setEnableDomaineOverlay(true);
    }

NewtonImage::~NewtonImage(void)
    {
    delete ptrNewtonMOO;
    }

/*--------------------------------------*\
 |*		Override		*|
 \*-------------------------------------*/

/**
 * Override
 * Called automatically by the API
 */
void NewtonImage::fillImageGL(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath)
    {
    ptrNewtonMOO->process(ptrTabPixels,  w,  h,domaineMath);
    }

/**
 * Override
 * call periodicly by the api
 */
void NewtonImage::animationStep(bool& isNeedUpdateView)
    {
    ptrNewtonMOO->animationStep();
    }

/**
 * Override
 * call periodicly by the api
 */
void NewtonImage::paintPrimitives(Graphic2Ds& graphic2D)
    {
    const Font_A* ptrFont = graphic2D.getFont(TIMES_ROMAN_24);

    float r = 0;
    float g = 0;
    float b = 0;
    graphic2D.setColorRGB(r, g, b);

    // Top
	{
	float t=ptrNewtonMOO->getT();
	int n=ptrNewtonMOO->getN();

	string message = "t = " + StringTools::toString(t) + "  n = " + StringTools::toString(n);
	graphic2D.drawTitleTop(message, ptrFont);
	}

    // Bottom
	{
	graphic2D.drawTitleBottom("[API Image Fonctionelle] : Newton zoomable OMP", ptrFont);
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

