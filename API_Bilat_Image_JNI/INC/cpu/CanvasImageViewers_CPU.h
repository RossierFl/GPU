#ifndef CanvasImageViewers_CPU_H_
#define CanvasImageViewers_CPU_H_

#include "envImageJNI.h"
#include "CanvasImageViewers_A.h"

#include "GLImages_CPU.h"
#include "GLImageSelections_CPU.h"
#include "GLImageFonctionelSelections_CPU.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace cpu
    {

    class CBI_IMAGE_JNI CanvasImageViewers : public CanvasImageViewers_A
	{
	public:

	    /*--------------------------------------*\
	     |*		Constructor		    *|
	     \*-------------------------------------*/

	    CanvasImageViewers(cpu::ImageMOOs_A* ptrImageMOO, bool useAnimation = false, bool useSelection = false);

	    CanvasImageViewers(cpu::ImageFonctionelMOOs_A* ptrImageFonctionel, bool useAnimation = false, bool useSelection = true);


	};
    }

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
