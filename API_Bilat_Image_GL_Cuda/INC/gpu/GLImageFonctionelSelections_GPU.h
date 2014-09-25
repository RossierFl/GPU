#ifndef GLIMAGE_FONCTIONEL_SELECTIONS_GPU_H
#define GLIMAGE_FONCTIONEL_SELECTIONS_GPU_H

#include "GLImageSelections_GPU.h"
#include "ImageFonctionelMOOs_A_GPU.h"

#define BACK_SPACE 8 //code ascii for Backspace

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace gpu
    {

    class CBI_GLIMAGE_CUDA GLImageFonctionelSelections: public gpu::GLImageSelections
	{
	public:

	    /*--------------------------------------*\
	     |*		Constructor		    *|
	     \*-------------------------------------*/

	    GLImageFonctionelSelections(gpu::ImageFonctionelMOOs_A* ptrImageCudaFonctionelMOO, bool isAnimationEnable = true);

	    virtual ~GLImageFonctionelSelections();

	    /*--------------------------------------*\
	 |*		Get			*|
	     \*-------------------------------------*/

	public:

	    gpu::ImageFonctionelMOOs_A* getPtrImageCudaFonctionelMOO();

	public:

	    /**
	     * Override
	     * then selection is performed with the mouse, 3 arguments :
	     *	1) selected domaine in frame coordinate
	     *	2) dx is the screen width in pixel
	     *	3) dy is the screen height in pixel
	     **/
	    virtual void selectionPerformed(const gpu::DomaineEcran& domaine, int dx, int dy);

	    /**
	     * Override
	     */
	    virtual void onKeyPressed(const KeyEvent &event);

	};
    }

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

