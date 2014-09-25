#include <iostream>
#include <math.h>

#include "DamierImage.h"
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
 * DomaineMaths(0, 0, 2 * PI, 2 * PI) : par exemple, why not celui là!
 */
DamierImage::DamierImage(unsigned int w, unsigned int h, float dt, int n) :
	ImageFonctionelMOOs_A(w, h, DomaineMath(0, 0, 2 * PI, 2 * PI))
    {
    //Tools
    this->ptrDamierMOO=new DamierMOO(w,h,dt,n);

    setEnableDomaineOverlay(true);
    }

DamierImage::~DamierImage(void)
    {
    delete ptrDamierMOO;
    }

/*--------------------------------------*\
 |*		Override		*|
 \*-------------------------------------*/

/**
 * Override
 * Called automatically by the API
 */
void DamierImage::fillImageGL(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath)
    {
    ptrDamierMOO->process(ptrTabPixels,  w,  h,domaineMath);
    }

/**
 * Override
 * call periodicly by the api
 */
void DamierImage::animationStep(bool& isNeedUpdateView)
    {
    ptrDamierMOO->animationStep();
    }

/**
 * Override
 * call periodicly by the api
 */
void DamierImage::paintPrimitives(Graphic2Ds& graphic2D)
    {
    const Font_A* ptrFont = graphic2D.getFont(TIMES_ROMAN_24);

    float r = 0;
    float g = 0;
    float b = 0;
    graphic2D.setColorRGB(r, g, b);

    // Top
	{
	float t=ptrDamierMOO->getT();
	int n=ptrDamierMOO->getN();

	string message = "t = " + StringTools::toString(t) + "  n = " + StringTools::toString(n);
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

