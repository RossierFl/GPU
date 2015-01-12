#ifndef GLIMAGE_SELECTIONS_GPU_H
#define GLIMAGE_SELECTIONS_GPU_H

#include "envGLImageCudas.h"
#include "GLImages_GPU.h"
#include "DomaineEcran_GPU.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace gpu
    {
    class CBI_GLIMAGE_CUDA GLImageSelections: public gpu::GLImages
	{

	    /*--------------------------------------*\
	    |*		Constructor		    *|
	     \*-------------------------------------*/

	public:

	    GLImageSelections(gpu::ImageMOOs_A* ptrImageCudaMOO, bool isAnimationEnable = true);

	    virtual ~GLImageSelections();

	    /*--------------------------------------*\
	     |*		Methodes		    *|
	     \*-------------------------------------*/

	public:

	    /**
	     * Override
	     */
	    virtual void display(Panel_A &panel);

	    /**
	     * Override
	     */
	    virtual void onMouseMoved(const MouseEvent &event);

	    /**
	     * Override
	     */
	    virtual void onMousePressed(const MouseEvent &event);

	    /**
	     * Override
	     */
	    virtual void onMouseReleased(const MouseEvent &event);

	protected:

	    /**
	     * Ovveride
	     * then selection is performed with the mouse, 3 arguments :
	     *	1) selected domaine in frame coordinate
	     *	2) dx is the screen width in pixLa clel
	     *	3) dy is the screen height in pixel
	     **/
	    virtual void selectionPerformed(const gpu::DomaineEcran& domaineEcran, int dx, int dy);

	    /*--------------------------------------*\
	     |*		Get			    *|
	     \*-------------------------------------*/

	    gpu::DomaineEcran getCurrentDomaineSelection() const;

	private:
	    void drawSelection();

	    /*-------------------------------------*\
	     |*		Attributs		   *|
	     \*------------------------------------*/
	private:

	    //Input
	    gpu::DomaineEcran domaineSelection;

	    //Tools
	    bool isSelectionEnable;
	    float ratio; //ration de la taille de la selection proportionnel � l'image
	};
    }

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

