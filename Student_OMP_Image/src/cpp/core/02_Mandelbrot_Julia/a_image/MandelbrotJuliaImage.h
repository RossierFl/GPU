#ifndef MandelbrotJulia_IMAGE_H_
#define MandelbrotJulia_IMAGE_H_

#include "ImageFonctionelMOOs_A.h"
#include "MandelbrotJuliaMOO.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotJuliaImage: public ImageFonctionelMOOs_A
    {
	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	MandelbrotJuliaImage(unsigned int w, unsigned int h, float dt, int n,double xMin,double xMax,double yMin,double yMax,bool isJulia,double cX,double cY);
	virtual ~MandelbrotJuliaImage(void);

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
	MandelbrotJuliaMOO* ptrMandelbrotJuliaMOO;


    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
