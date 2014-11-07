#ifndef RIPPLING_0_PROVIDER_H_
#define RIPPLING_0_PROVIDER_H_


#include "Rippling0Image.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Rippling0Provider
    {
    public:

	static Rippling0Image* createGL(void)
	    {
	     float dt = 2*PI/1000; // animation para

	    int dw = 16 * 60; // =32*30=960
	    int dh = 16 * 60; // =32*30=960

	    return new Rippling0Image(dw, dh, dt);
	    }

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

