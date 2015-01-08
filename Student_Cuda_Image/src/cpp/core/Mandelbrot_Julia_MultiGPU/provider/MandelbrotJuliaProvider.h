#ifndef MANDELBROT_JULIA_PROVIDER_H_
#define MANDELBROT_JULIA_PROVIDER_H_

#include "MandelbrotJulia.h"
#include "ImageFonctionel.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotJuliaProvider
    {
    public:

	static MandelbrotJulia* create(void);
	static ImageFonctionel* createGL(void);


    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

