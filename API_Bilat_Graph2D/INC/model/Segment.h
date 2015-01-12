#ifndef SEGMENT_H_
#define SEGMENT_H_

#define OFFSET_A 0
#define OFFSET_B 1

#include "Polylines.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Segment AB
 */
class CBI_GRAPH Segment : public Polylines
    {
    public:
	Segment(Title title, Apparance apparance,Point a,Point b);
	virtual ~Segment();

	Point getA() const;
	Point getB() const;

	void setA(Point a);
	void setB(Point b);
	void setAB(Point a,Point b);

    protected :
	static shared_array<Point> createTabPoint(Point a,Point b);
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
