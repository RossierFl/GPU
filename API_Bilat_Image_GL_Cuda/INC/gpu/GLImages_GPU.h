#ifndef GLIMAGES_GPU_H
#define GLIMAGES_GPU_H

#include "envGLImageCudas.h"
#include "CudaInteropTools.h"
#include "GLImages_A.h"
#include "ImageMOOs_A_GPU.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace gpu
    {

    /**
     * Data plus stocker in Central Memory, mais in GPU memory !
     */
    class CBI_GLIMAGE_CUDA GLImages: public GLImages_A
	{
	public:

	    /*--------------------------------------*\
	     |*		Constructor		    *|
	     \*-------------------------------------*/

	    /**
	     *   (dx,dy)		:  Size of the image
	     *   (pxFrame,pyFrame) 	:  The position of the upper left corner of the frame in screen space.
	     */
	    GLImages(gpu::ImageMOOs_A* ptrImageCudaMOO, bool isAnimationEnable = true);

	    virtual ~GLImages();

	    /*--------------------------------------*\
	     |*		Methodes		    *|
	     \*-------------------------------------*/

	public:

	    virtual void release(Panel_A &panel);

	protected:

	    /**
	     * Override
	     */
	    virtual void createPBO();

	    /**
	     * Override
	     */
	    virtual void fillPBO();

	    /*--------------------------------------*\
	     |*		Get			    *|
	     \*-------------------------------------*/

	public:

	    gpu::ImageMOOs_A* getPtrImageCudaMOO();

	    /*--------------------------------------*\
	     |*		Set			    *|
	     \*-------------------------------------*/

	public:

	    void setStreamToSynchronize(cudaStream_t streamId);

	    /*--------------------------------------*\
	    |*		Attributs		    *|
	     \*-------------------------------------*/

	private:

	    //Inputs
	    gpu::ImageMOOs_A* ptrImageCudaMOO;

	    //Cuda interop
	    cudaGraphicsResource* cudaRessource;
	    cudaStream_t streamToSynchronize;
	};

    }
#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

