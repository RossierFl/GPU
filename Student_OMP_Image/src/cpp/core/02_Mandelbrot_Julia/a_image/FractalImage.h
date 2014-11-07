#ifndef FRACTAL_IMAGE_H_
#define FRACTAL_IMAGE_H_

#include "ImageMOOs_A.h"
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

	FractalImage(unsigned int w, unsigned int h, unsigned int nMin, unsigned int nMax, double cx, double cyi, bool isJulia, double x0, double x1, double y0, double y1);
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

    private:
	// Tools
	FractalMOO* ptrFractalMOO;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
