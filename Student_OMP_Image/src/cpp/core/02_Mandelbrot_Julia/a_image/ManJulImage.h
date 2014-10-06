#ifndef MANJULIMAGE_H_
#define MANJULIMAGE_H_

#include "ImageFonctionelMOOs_A.h"
#include "ManJulMOO.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class ManJulImage: public ImageFonctionelMOOs_A
    {
	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	ManJulImage(unsigned int w, unsigned int h, float dt, int n, int isJulia,
		double c1, double c2,double x1,double y1,double x2,double y2);
	virtual ~ManJulImage(void);

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
	ManJulMOO* ptrManJulMoo;


    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
