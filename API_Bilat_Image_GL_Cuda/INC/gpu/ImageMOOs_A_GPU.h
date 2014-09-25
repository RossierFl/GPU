#ifndef IMAGE_CUDA_MOOS_A_H
#define IMAGE_CUDA_MOOS_A_H

#include "builtin_types.h" //for cuda uchar4

#include "envGLImageCudas.h"
#include "ImageMOOs_I.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace gpu
    {
    class CBI_GLIMAGE_CUDA ImageMOOs_A: public ImageMOOs_I
	{
	public:

	    /*--------------------------------------*\
	     |*		Constructor		    *|
	     \*-------------------------------------*/

	    ImageMOOs_A(unsigned int w, unsigned int h);

	    /*--------------------------------------*\
	     |*		Destructor		    *|
	     \*-------------------------------------*/

	    virtual ~ImageMOOs_A();

	    /*--------------------------------------*\
	     |*		Methodes		    *|
	     \*-------------------------------------*/

	public:

	    virtual void fillImageGL(uchar4* ptrDevImageGL, int w, int h)=0; //ptrDevImageGL zone memoire commune OpenGL et Cuda

	    /**
	     * Override
	     * A redefinir par l'utilisateur
	     */
	    virtual void animationStep(bool& isNeedUpdateView);

	    /**
	     * Override
	     * A redefinir par l'utilisateur
	     */
	    virtual void paintPrimitives(Graphic2Ds& ptrGraphic2D);

	    /*--------------------------------------*\
	     |*		Get			    *|
	     \*-------------------------------------*/

	public:

	    /**
	     * Recuperation des pixels de l'image coter CPU
	     * call fillImageGL
	     *
	     * Instanciation :
	     *
	     *	unsigned char* ptrTabPixel=new unsigned char[w*h]
	     *
	     * Pour liberer la memoire :
	     *
	     * 	delete[] ptrTabPixel;
	     */
	    unsigned char* getPtrTabPixels();
	};
    }

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
