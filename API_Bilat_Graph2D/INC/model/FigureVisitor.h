#ifndef FIGUREVISITOR_I_H_
#define FIGUREVISITOR_I_H_

#include "envGraph.h"
#include "CurveParametric.h"
#include "CurveAnalytic.h"
//class CurveParametric;
//class CurveAnalytic;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GRAPH FigureVisitor_I
    {
    public:

	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/

	virtual ~FigureVisitor_I()
	    {
	    }

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

	virtual void visit(CurveParametric* ptrPolylines)=0;

	virtual void visit(CurveAnalytic* ptrCurve)=0;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
