#ifndef DOMAINE_ECRAN_GPU_H
#define DOMAINE_ECRAN_GPU_H

#include "envGLImageCudas.h"
#include <string>
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace gpu
    {
    class CBI_GLIMAGE_CUDA DomaineEcran
	{

	    /*--------------------------------------*\
	     |*		Constructor		    *|
	     \*-------------------------------------*/

	public:

	    __host__ __device__ DomaineEcran(int x, int y, int dx, int dy) :
		    x0(x), y0(y), dx(dx), dy(dy)
		{

		}

	    __host__ __device__ DomaineEcran() : x0(0),y0(0),dx(1),dy(1)
		{

		}

	    /*--------------------------------------*\
	     |*		Methodes		    *|
	     \*-------------------------------------*/

	public:

	    __host__ string toString();

	    /*-------------------------------------*\
	     |*		Attributs		   *|
	     \*------------------------------------*/

	public:

	    //Input
	    int x0;
	    int y0;
	    int dx;
	    int dy;
	};
    }
#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

