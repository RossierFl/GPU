#ifndef RAYTRACINGPROVIDER_H_
#define RAYTRACINGPROVIDER_H_

#include "RayTracing.h"
#include "Image.h"


class RayTracingProvider
    {
    public:

	static RayTracing* create(void);
	static Image* createGL(void);

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
