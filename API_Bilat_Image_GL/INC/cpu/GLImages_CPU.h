#ifndef GLIMAGES_CPU_H
#define GLIMAGES_CPU_H

#include "envGLImage.h"
#include "GLImages_A.h"
#include "ImageMOOs_A_CPU.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace cpu
    {

    class CBI_GLIMAGE GLImages: public GLImages_A
	{
	    /*--------------------------------------*\
	     |*		Constructor		    *|
	     \*-------------------------------------*/
	public:

	    /**
	     * (pxFrame,pyFrame) is the position of the upper left corner of the frame in screen space.
	     */
	    GLImages(cpu::ImageMOOs_A* ptrImageMOO, bool isAnimationEnable = true);

	    /*--------------------------------------*\
	     |*		Destructor		    *|
	     \*-------------------------------------*/
	public :

	    virtual ~GLImages();

	    /*--------------------------------------*\
	     |*		Methodes		    *|
	     \*-------------------------------------*/


	protected:
	    /**
	     * Override
	     */
	    virtual void fillPBO();

	    /*--------------------------------------*\
	     |*		Get			    *|
	     \*-------------------------------------*/

	public:

	    cpu::ImageMOOs_A* getPtrImageMOO();

	    /*--------------------------------------*\
	     |*		Attributs		    *|
	     \*-------------------------------------*/

	private:

	    // Tools
	    cpu::uchar4* ptrTabPixels;

	};
    }
#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

