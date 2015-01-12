#ifndef LINEH_H_
#define LINEH_H_
#include "Segment.h"
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GRAPH LineH : public Segment
    {
    public:
	/**
	 * Create a Horiztonal segment from coordinates A=(x1, y), B=(x2, y)
	 */
	LineH(Title title, Apparance apparance, float y,float x1,float x2);
	virtual ~LineH();

	void setY(float y);
	void setX(float x1,float x2);
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
