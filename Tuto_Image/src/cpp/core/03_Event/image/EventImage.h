#ifndef EVENT_IMAGE_H_
#define EVENT_IMAGE_H_

#include "ImageMOOs_A.h"
#include "MathTools.h"
#include "SimpleKeyListener.h"
#include "SimpleMouseListener.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class EventImage: public ImageMOOs_A
    {

	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	EventImage(unsigned int w, unsigned int h);
	virtual ~EventImage(void);

	/*--------------------------------------*\
	 |*		Methode			*|
	 \*-------------------------------------*/

    protected:

	/*--------------------------------------*\
	|*		Override		*|
	 \*-------------------------------------*/

	/**
	 * Override, call periodicly by the api
	 */
	virtual void fillImageGL(uchar4* ptrTabPixels, int w, int h);

	/**
	 * Override, call periodicly by the api
	 */
	virtual void animationStep(bool& isNeedUpdateView);

	/**
	 * Override, call by the api at each "draw"
	 */
	virtual void paintPrimitives(Graphic2Ds& graphic2D);

    private:

	void control(void);

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	double dt;

	// Tools
	double t;
	SimpleKeyListener* ptrKeyListener;
	SimpleMouseListener* ptrMouseListener;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 /*----------------------------------------------------------------------*/
