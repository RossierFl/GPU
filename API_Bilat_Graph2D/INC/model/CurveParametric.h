#ifndef CURVE_PARAMETRIC_H
#define CURVE_PARAMETRIC_H

#include "Figure.h"
#include "Point.h"
#include "Interval.h"
#include <memory>

#include "shared_array.h"
//#include <boost/shared_array.hpp>
//using boost::shared_array;

//in c++14 = std::shared_ptr<int> sp( new int[10], std::default_delete<int[]>() );

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Courbe de param�tre landa
 */
class CBI_GRAPH CurveParametric: public Figure
    {
    public:
	CurveParametric(Title title, Apparance apparance);

	virtual ~CurveParametric();

	virtual Domaine computeDomaine(const Domaine& graphDomaine) const;

	virtual void accept(FigureVisitor_I* ptrVisitor);

	/**
	 * Return a new TabPoints of size getNbPoints()
	 * Delete car pas trouver d'equivalence a boost dans la stl
	 */
	virtual  shared_array<Point> getTabPoints() const;

	virtual int getNbPoints() const = 0;

	virtual Interval getIntervalLanda() const =0;

	/**
	 * landa in intervalLand
	 */
	virtual float x(double landa) const=0;


	/**
	 * landa in intervalLand
	 */
	virtual float y(double landa) const=0;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
