#include <iostream>

#include "EventImage.h"


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

EventImage::EventImage(unsigned int w, unsigned int h) :
	ImageMOOs_A(w, h)
    {
    control();
    }

EventImage::~EventImage(void)
    {
    delete ptrKeyListener;
    delete ptrMouseListener;
    }

/*--------------------------------------*\
 |*		Override		*|
 \*-------------------------------------*/


/**
 * Override
 * call periodicly by the api
 */
void EventImage::fillImageGL(uchar4* ptrTabPixels, int w, int h)
    {
    // vide
    }

/**
 * Override
 * call periodicly by the api
 */
void EventImage::animationStep(bool& isNeedUpdateView)
    {
    // rien
    }

/**
 * Override
 * call periodicly by the api
 */
void EventImage::paintPrimitives(Graphic2Ds& graphic2D)
    {
    const Font_A* ptrFont = graphic2D.getFont(TIMES_ROMAN_24);

    float r = 1;
    float g = 0;
    float b = 0;
    graphic2D.setColorRGB(r, g, b);

    // Bottom
	{
	graphic2D.drawTitleBottom("API Image : Click on the windows, and look message in the console", ptrFont);
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void EventImage::control(void)
    {
    this->ptrKeyListener = new SimpleKeyListener();
    this->ptrMouseListener = new SimpleMouseListener();

    setKeyListener(ptrKeyListener);
    setMouseListener(ptrMouseListener);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

