#ifndef POINT_H_
#define POINT_H_
#include "envGraph.h"
#include "Definitions.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GRAPH Point
    {
    public:
	Point(float x = 0.0, float y = 0.0);
	~Point();
	void set(float x, float y);
	void setX(float x);
	void setY(float y);

	inline float getX() const
	    {
	    return x;
	    }
	inline float getY() const
	    {
	    return y;
	    }

	void zero();

    private:
	float x;
	float y;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
