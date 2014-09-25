#ifndef DOMAINE_H_
#define DOMAINE_H_

#include "Point.h"
#include "Interval.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GRAPH Domaine
    {
    public:
	Domaine(double x1, double y1, double x2, double y2);
	Domaine(Point p1, Point p2);
	Domaine(Interval intervalX, Interval intervalY);

	void setIntervalX(Interval interval);
	void setIntervalY(Interval interval);

	inline Interval getIntervalX() const
	    {
	    return intervalX;
	    }

	inline Interval getIntervalY() const
	    {
	    return intervalY;
	    }

	inline double getX1() const
	    {
	    return intervalX.getMin();
	    }

	inline double getX2() const
	    {
	    return intervalX.getMax();
	    }

	inline double getY1() const
	    {
	    return intervalY.getMin();
	    }

	inline double getY2() const
	    {
	    return intervalY.getMax();
	    }

	Point gravity() const;

	Domaine combine(Domaine domaine) const;

    private:
	Interval intervalX;
	Interval intervalY;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
