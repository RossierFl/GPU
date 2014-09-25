#ifndef GL_PRIMITIVE_DRAWERS_H
#define GL_PRIMITIVE_DRAWERS_H

#include "envGLImage.h"
#include "PrimitiveVisitors_I.h"
#include "TextRenderer_A.h"
#include "Line2Ds.h"
#include "Rect2Ds.h"
#include "Text2Ds.h"
#include "WiredRect2Ds.h"
#include "Graphic2Ds.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GLIMAGE GLPrimitiveDrawers: public PrimitiveVisitors_I

    {
    public:

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

	GLPrimitiveDrawers();

	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/

	virtual ~GLPrimitiveDrawers();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void display(Graphic2Ds* graphic2D, TextRenderer_A* textRenderer);

    private:

	/**
	 * Override
	 */
	virtual void visite(Graphic2Ds* graphic2D);

	/**
	 * Override
	 */
	virtual void visite(Line2Ds* ptrLine2D);

	/**
	 * Override
	 */
	virtual void visite(Rect2Ds* ptrRect2D);

	/**
	 * Override
	 */
	virtual void visite(Text2Ds* ptrTexte2D);

	/**
	 * Override
	 */
	virtual void visite(WiredRect2Ds* ptrWiredRect2D);

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:
	/**
	 * setBy display !
	 */
	TextRenderer_A* ptrTextRenderer;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

