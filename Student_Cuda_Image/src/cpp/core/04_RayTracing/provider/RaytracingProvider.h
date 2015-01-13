#ifndef RAYTRACINGPROVIDER_H_
#define RAYTRACINGPROVIDER_H_


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

#include "Raytracing.h"
#include "Image.h"


class RaytracingProvider {
    public:
	static Raytracing* create(void);
	static Image* createGL(void);
};

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
