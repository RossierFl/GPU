#ifndef FRACTAL_PROVIDER_MULTI_H_
#define FRACTAL_PROVIDER_MULTI_H_

#include "FractalMulti.h"
#include "ImageFonctionel.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class FractalProviderMulti
    {
    public:

	static FractalMulti* create(void);
	static ImageFonctionel* createGL(void);


    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

