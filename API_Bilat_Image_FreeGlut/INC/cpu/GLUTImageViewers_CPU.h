#ifndef GLUT_IMAGE_VIEWERS_GPU_H
#define GLUT_IMAGE_VIEWERS_CPU_H

#include "envImage_FreeGlut.h"
#include "GLUTImageViewers_A.h"
#include "GLUTWindowImage.h"
#include "ImageMOOs_I.h"

//cpu
#include "GLImageFonctionelSelections_CPU.h"
#include "ImageFonctionelMOOs_A_CPU.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace cpu
    {
    class CBI_IMAGE_FREE_GLUT GLUTImageViewers: public GLUTImageViewers_A
	{

	    /*--------------------------------------*\
	     |*		Constructor		    *|
	     \*-------------------------------------*/

	public:

	    GLUTImageViewers(cpu::ImageMOOs_A* ptrImageMOO, bool useAnimation = false, bool useSelection = false, int pxFrame = 0, int pyFrame = 0);

	    GLUTImageViewers(cpu::ImageFonctionelMOOs_A* ptrImageFonctionel, bool useAnimation = false, bool useSelection = true, int pxFrame = 0, int pyFrame =
		    0);

	};

    }

#endif
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

