#ifndef RAYTRACINGPROVIDER_H_
#define RAYTRACINGPROVIDER_H_

#include "RayTracing.h"
//#include "ImageFonctionel.h"
#include "Image.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class RayTracingProvider
    {
	/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
    public:

	static RayTracing* create(void);
	static Image* createGL(void);

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
