#ifndef POLYLINES_H_
#define POLYLINES_H_

#include "CurveParametric.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GRAPH Polylines: public CurveParametric
    {
    public:
	Polylines(Title title, Apparance apparance, shared_array<Point> tabPoint, int nbPoints);

	virtual ~Polylines();

	virtual Domaine computeDomaine(const Domaine& graphDomaine) const;

	void setTabPoint(shared_array<Point> tabPoint);

	/**
	 * Override
	 * Return the input Polylines tabPoints.
	 */
	virtual shared_array<Point> getTabPoints() const;

	virtual inline int getNbPoints() const
	    {
	    return nbPoints;
	    }

	virtual Interval getIntervalLanda() const;

	/**
	 * landa in intervalLand
	 */
	virtual float x(double landa) const;

	/**
	 * landa in intervalLand
	 */
	virtual float y(double landa) const;

    private:
	shared_array<Point> tabPoint;
	int nbPoints;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
