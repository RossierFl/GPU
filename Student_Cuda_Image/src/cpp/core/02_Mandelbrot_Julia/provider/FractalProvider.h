#ifndef Fractal_PROVIDER_H_
#define Fractal_PROVIDER_H_

#include "Fractal.h"
#include "ImageFonctionel.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class FractalProvider {
	public:

		static Fractal* create(void);
		static ImageFonctionel* createGL(void);

};

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

