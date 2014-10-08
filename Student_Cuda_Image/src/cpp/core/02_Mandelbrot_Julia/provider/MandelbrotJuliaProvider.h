#ifndef MANDELBROTJULIAPROVIDER_H_
#define MANDELBROTJULIAPROVIDER_H_

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

