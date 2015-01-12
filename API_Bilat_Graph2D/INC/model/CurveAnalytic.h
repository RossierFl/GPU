#ifndef CURVE_ANALYTIC_H_
#define CURVE_ANALYTIC_H_

#include "Figure.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GRAPH CurveAnalytic: public Figure
    {
    public:
	CurveAnalytic(Title title, Apparance apparance);

	virtual ~CurveAnalytic();

	virtual float f(const float x) const = 0;

	virtual Domaine computeDomaine(const Domaine& graphDomaine) const;

	void accept(FigureVisitor_I* ptrVisitor);
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
