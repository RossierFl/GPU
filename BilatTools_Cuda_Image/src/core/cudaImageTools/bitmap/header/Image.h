#ifndef IMAGE_H_
#define IMAGE_H_

#include "ImageMOOs_A.h"
#include "MathTools.h"
#include "ColorRGB_01.h"

#include "Animable_I.h"



/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Image: public ImageMOOs_A
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	\*-------------------------------------*/

    public:

	/**
	 * ptrColorRGB : color all titre
	 */
	Image(Animable_I* ptrAnimable, ColorRGB_01* ptrColorTitreRGB = new ColorRGB_01(1, 0, 0));

	/**
	 * Warning :delete ptrAnimable
	 */
	virtual ~Image(void);

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void fillImageGL(uchar4* ptrDevImageGL, int w, int h); // override
	void animationStep(bool& isNeedUpdateView); // override
	void paintPrimitives(Graphic2Ds& graphic2D); // override

	/*--------------------------------------*\
	|*		Attributs		*|
	\*-------------------------------------*/

    private:

	// Input
	Animable_I* ptrAnimable;
	ColorRGB_01* ptrColorTitreRGB;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
