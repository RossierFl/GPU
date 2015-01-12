#ifndef GLUT_IMAGE_VIEWERS_GPU_H
#define GLUT_IMAGE_VIEWERS_GPU_H

#include "envImageFreeGlutCuda.h"
#include "GLUTImageViewers_A.h"

//gpu
#include "GLImageFonctionelSelections_GPU.h"
#include "ImageFonctionelMOOs_A_GPU.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace gpu
    {
    class CBI_IMAGE_FREE_GLUT_CUDA GLUTImageViewers: public GLUTImageViewers_A
	{

	    /*--------------------------------------*\
	     |*		Constructor		    *|
	     \*-------------------------------------*/

	public:

	    GLUTImageViewers(gpu::ImageMOOs_A* ptrImageMOO, bool useAnimation = false, bool useSelection = false, int pxFrame = 0, int pyFrame = 0);

	    GLUTImageViewers(gpu::ImageFonctionelMOOs_A* ptrImageFonctionel, bool useAnimation = false, bool useSelection = true, int pxFrame = 0, int pyFrame = 0);


	};
    }
#endif
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

