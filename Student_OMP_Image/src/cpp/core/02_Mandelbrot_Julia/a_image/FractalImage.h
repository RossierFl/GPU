#ifndef FRACTAL_IMAGE_H_
#define FRACTAL_IMAGE_H_

#include "ImageFonctionelMOOs_A.h"
#include "FractalMOO.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class FractalImage: public ImageFonctionelMOOs_A
    {
	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

  FractalImage(unsigned int w, unsigned int h, bool julia, int n, double xMin, double yMin, double xMax, double yMax,double cx,double cy);
	virtual ~FractalImage(void);

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
	virtual void fillImageGL(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath);

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

    protected:

	// Tools
	FractalMOO* ptrFractalMOO;


    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
