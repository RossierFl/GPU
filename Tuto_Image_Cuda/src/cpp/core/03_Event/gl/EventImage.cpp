#include <iostream>

#include "EventImage.h"
#include "SimpleKeyListener.h"
#include "SimpleMouseListener.h"

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

EventImage::EventImage(Event* ptrEvent) :
	ImageFonctionel(ptrEvent)
    {
    control();
    }

EventImage::~EventImage(void)
    {
    delete ptrKeyListener;
    delete ptrMouseListener;
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

