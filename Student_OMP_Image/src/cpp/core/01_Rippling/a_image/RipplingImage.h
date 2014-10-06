#ifndef RIPPLING_IMAGE_H_
#define RIPPLING_IMAGE_H_

#include "ImageMOOs_A.h"
#include "RipplingMOO.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RipplingImage: public ImageMOOs_A
    {

	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	RipplingImage(unsigned int w, unsigned int h, float dt = 1);
	virtual ~RipplingImage(void);

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    protected:

	/*----------------*\
	|*  Override	  *|
	\*---------------*/

	/**
	 * Override, call periodicly by the api
	 */
	virtual void fillImageGL(uchar4* ptrTabPixels, int w, int h);

	/**
	 * Override, call periodicly by the api
	 */
	virtual void animationStep(bool& isNeedUpdateView);

	/**
	 * Override, call periodicly by the api
	 */
	virtual void paintPrimitives(Graphic2Ds& graphic2D);



	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:

	// Tools
	RipplingMOO* ptrRipplingMOO;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
