#ifndef RIPPLING_0_IMAGE_H_
#define RIPPLING_0_IMAGE_H_

#include "ImageMOOs_A.h"
#include "MathTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Rippling0Image: public ImageMOOs_A
    {
	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	Rippling0Image(unsigned int w, unsigned int h, float dt = 2 * PI / 10);
	virtual ~Rippling0Image(void);

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	/*----------------*\
	|*  Override	  *|
	 \*---------------*/

	/**
	 * Override, call periodicly by the api
	 */
	void fillImageGL(uchar4* ptrDevImageGL, int w, int h);

	/**
	 * Override, call periodicly by the api
	 */
	void animationStep(bool& isNeedUpdateView);

	/**
	 * Override, call periodicly by the api
	 */
	void paintPrimitives(Graphic2Ds& graphic2D);

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:

	// Input
	double dt;

	// Tools
	double t;

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
