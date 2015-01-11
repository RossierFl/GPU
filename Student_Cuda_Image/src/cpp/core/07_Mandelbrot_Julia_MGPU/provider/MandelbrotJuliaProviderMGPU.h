#ifndef MANDELBROTJULIAPROVIDERMGPU_H_
#define MANDELBROTJULIAPROVIDERMGPU_H_

#include "MandelbrotJuliaMGPU.h"
#include "ImageFonctionel.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotJuliaProviderMGPU
    {
    public:

	static MandelbrotJuliaMGPU* create(void);
	static ImageFonctionel* createGL(void);


    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

