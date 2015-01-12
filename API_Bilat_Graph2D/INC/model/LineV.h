#ifndef LINEV_H_
#define LINEV_H_

#include "Segment.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GRAPH LineV: public Segment
    {
    public:
	/**
	 * Create a vertical segment from coordinates A=(x, y1), B=(x, y2)
	 */
	LineV(Title title, Apparance apparance, float x, float y1, float y2);

	void setX(float x);
	void setY(float y1,float y2);

	virtual ~LineV();
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
