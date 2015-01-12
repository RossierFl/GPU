#ifndef GRAPH_OBSERVER_I_H_
#define GRAPH_OBSERVER_I_H_

#include "envGraph.h"
#include "Figure.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GRAPH GraphObserver_I
    {
    public:

	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/

	virtual ~GraphObserver_I()
	    {
	    }

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	virtual void onFigureAdd(Figure* ptrFigure)=0;

	virtual void onFigureRemove(Figure* ptrFigure)=0;

	virtual void update()=0;

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
