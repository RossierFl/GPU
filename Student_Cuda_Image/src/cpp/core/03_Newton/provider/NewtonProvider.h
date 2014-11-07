#ifndef NEWTONPROVIDER_H_
#define NEWTONPROVIDER_H_

#include "Newton.h"
#include "ImageFonctionel.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class NewtonProvider
    {
	/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
    public:

	static Newton* create(void);
	static ImageFonctionel* createGL(void);


    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
