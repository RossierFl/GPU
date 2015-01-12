#ifndef RECT_2DS_H
#define RECT_2DS_H

#include "Primitives_A.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GLIMAGE Rect2Ds: public Primitives_A
    {
    public:

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

	/*
	 * (x,y) coin superieur gauche
	 */
	Rect2Ds(int x, int y, int width, int height);

	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/

	virtual ~Rect2Ds();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/**
	 * Override
	 */
	virtual void accept(PrimitiveVisitors_I &visitor);

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/

	inline int getX()
	    {
	    return x;
	    }

	inline int getY()
	    {
	    return y;
	    }

	inline int getWidth()
	    {
	    return width;
	    }

	inline int getHeight()
	    {
	    return height;
	    }

	/*--------------------------------------*\
	 |*		Set			*|
	 \*-------------------------------------*/

	void setXY(int x, int y);
	void setSize(int width, int height);

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    public:

	//Input
	int x;
	int y;
	int width;
	int height;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
