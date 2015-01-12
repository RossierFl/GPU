#ifndef PRIMITIVE_VISITOR_H
#define PRIMITIVE_VISITOR_H

#include "envGLImage.h"
#include "TextRenderer_A.h"

class Graphic2Ds;
class Line2Ds;
class Rect2Ds;
class WiredRect2Ds;
class Text2Ds;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GLIMAGE PrimitiveVisitors_I
    {
    public:

	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/


	virtual ~PrimitiveVisitors_I()
	    {
	    //Nothing
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

	virtual void visite(Graphic2Ds* graphic2D)=0;

	virtual void visite(Line2Ds* ptrLine2D)=0;

	virtual void visite(Rect2Ds* ptrRect2D)=0;

	virtual void visite(WiredRect2Ds* ptrWiredRect2Ds)=0;

	virtual void visite(Text2Ds* ptrTexte2D)=0;

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
