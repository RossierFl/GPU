#ifndef GLIMAGE_FONCTIONEL_SELECTIONS_CPU_H
#define GLIMAGE_FONCTIONEL_SELECTIONS_CPU_H

#include "GLImageSelections_CPU.h"
#include "ImageFonctionelMOOs_A_CPU.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace cpu
    {
    class CBI_GLIMAGE GLImageFonctionelSelections: public cpu::GLImageSelections
	{

	    /*--------------------------------------*\
	     |*		Constructor		    *|
	     \*-------------------------------------*/

	public:

	    GLImageFonctionelSelections(cpu::ImageFonctionelMOOs_A *ptrImageFonctionel, bool isAnimationEnable = true);

	    /*--------------------------------------*\
	     |*		Destructor		    *|
	     \*-------------------------------------*/

	public:

	    virtual ~GLImageFonctionelSelections();

	    /*--------------------------------------*\
	     |*		Methodes		    *|
	     \*-------------------------------------*/

	public:

	    /**
	     * surcharge
	     */
	    virtual void onKeyPressed(const KeyEvent &event);

	protected:

	    /**
	     * Callback for square selection with mouse
	     * Then selection is performed with the mouse, 3 arguments :
	     *	1) selected domaine in frame coordinate
	     *	2) dx is the screen width in pixel
	     *	3) dy is the screen height in pixel
	     **/
	    virtual void selectionPerformed(cpu::DomaineEcran& domaine, int dx, int dy);

	    /*--------------------------------------*\
	     |*		Get			*|
	     \*-------------------------------------*/

	    cpu::ImageFonctionelMOOs_A* getPtrImageFonctionelSelectionMOO();

	};
    }

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
