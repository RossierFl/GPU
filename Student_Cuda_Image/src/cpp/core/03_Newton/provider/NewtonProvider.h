#ifndef NEWTONPROVIDER_H_
#define NEWTONPROVIDER_H_

#include "Newton.h"
#include "ImageFonctionel.h"

/*----------------------------------------------------------------------*\
|*			Declaration 												*|
\*----------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Public							*|
\*--------------------------------------*/

class NewtonProvider
{
public:

	static Newton* createMOO();

	static ImageFonctionel* createGL();

};

#endif

