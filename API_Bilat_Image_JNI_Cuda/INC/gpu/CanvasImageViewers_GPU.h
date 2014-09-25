#ifndef CANVAS_IMAGE_VIEWERS_GPU_H_
#define CANVAS_IMAGE_VIEWERS_GPU_H_

#include "envImageCudaJNI.h"
#include "CanvasImageViewers_A.h"
#include "GLImages_GPU.h"
#include "GLImageSelections_GPU.h"
#include "GLImageFonctionelSelections_GPU.h"
#include "ImageMOOs_A_GPU.h"
#include "ImageFonctionelMOOs_A_GPU.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace gpu
    {
    class CBI_IMAGE_CUDA_JNI CanvasImageViewers: public CanvasImageViewers_A
	{
	public:
	    /*--------------------------------------*\
	     |*		Constructor		    *|
	     \*-------------------------------------*/


	    CanvasImageViewers(gpu::ImageMOOs_A* ptrImageMOO, bool useAnimation = false, bool useSelection = false);

	    CanvasImageViewers(gpu::ImageFonctionelMOOs_A* ptrImageFonctionel, bool useAnimation = false, bool useSelection = true);

	};
    }
#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
