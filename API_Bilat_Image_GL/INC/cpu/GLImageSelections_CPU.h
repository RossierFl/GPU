#ifndef GLIMAGE_SELECTIONS_CPU_H
#define GLIMAGE_SELECTIONS_CPU_H

#include "GLImages_CPU.h"
#include "DomaineEcran_CPU.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace cpu
    {
    class CBI_GLIMAGE GLImageSelections: public cpu::GLImages
	{
	public:
	    /*--------------------------------------*\
	     |*		Constructor		    *|
	     \*-------------------------------------*/

	    GLImageSelections(cpu::ImageMOOs_A* ptrImageMOO, bool isAnimationEnable = true);

	    /*--------------------------------------*\
	     |*		Destructor		    *|
	     \*-------------------------------------*/

	    virtual ~GLImageSelections();

	    /*--------------------------------------*\
	     |*		Methodes		    *|
	     \*-------------------------------------*/

	protected:

	    /**
	     * then selection is performed with the mouse, 3 arguments :
	     *	1) selected domaine in frame coordinate
	     *	2) dx is the screen width in pixLa clel
	     *	3) dy is the screen height in pixel
	     **/
	    virtual void selectionPerformed(cpu::DomaineEcran& domaine, int dx, int dy);

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

	private:

	    void drawSelection();

	    /*--------------------------------------*\
	     |*		Get			     *|
	     \*-------------------------------------*/

	protected:

	    cpu::DomaineEcran getCurrentDomaineSelection() const;

	    /*--------------------------------------*\
	     |*		Attributs		    *|
	     \*-------------------------------------*/

	private:

	    //Inputs
	    cpu::DomaineEcran domaineSelection;

	    //Tools
	    bool isSelectionEnable;
	    float ratio; //ration de la taille de la s�lection proportionnel � l'image
	};
    }

#endif
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

