#ifndef IMAGE_MOOS_A_CPU_H
#define IMAGE_MOOS_A_CPU_H

#include "envGLImage.h"
#include "cudaType_CPU.h"
#include "ImageMOOs_I.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace cpu
    {
    class CBI_GLIMAGE ImageMOOs_A: public ImageMOOs_I
	{
	public:

	    /*--------------------------------------*\
	    |*		Constructor		    *|
	     \*-------------------------------------*/

	    ImageMOOs_A(unsigned int m, unsigned int n);

	    ImageMOOs_A(const cpu::ImageMOOs_A &imageSource);

	    /*--------------------------------------*\
	     |*		Destructor		    *|
	     \*-------------------------------------*/

	    virtual ~ImageMOOs_A();

	    /*--------------------------------------*\
	     |*		Methodes		    *|
	     \*-------------------------------------*/

	    virtual void fillImageGL(cpu::uchar4* ptrTabPixels, int w, int h)=0;

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

	};

    }
#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
