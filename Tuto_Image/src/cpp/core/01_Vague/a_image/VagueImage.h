#ifndef VAGUE_IMAGE_H_
#define VAGUE_IMAGE_H_

#include "ImageMOOs_A.h"
#include "VagueMOO.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class VagueImage: public ImageMOOs_A
    {

	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	VagueImage(unsigned int w, unsigned int h, float dt);
	virtual ~VagueImage(void);

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
	virtual void fillImageGL(uchar4* ptrDevImageGL, int w, int h);

	/**
	 * Override, call periodicly by the api
	 */
	virtual void animationStep(bool& isNeedUpdateView);

	/**
	 * Override, call periodicly by the api
	 */
	virtual void paintPrimitives(Graphic2Ds& graphic2D);

	/*----------------*\
	|*  Private	  *|
	\*---------------*/

    private:


	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:

	// Tools
	VagueMOO* ptrVagueMOO;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 /*----------------------------------------------------------------------*/
