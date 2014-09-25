#ifndef CURVEDISCRET_H_
#define CURVEDISCRET_H_

#include "Polylines.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GRAPH CurveDiscret : public Polylines
    {
    public:

	CurveDiscret(Title title, Apparance apparance, shared_array<float> tabValues, int nbPoints);

	virtual ~CurveDiscret();

	void setTabValues(shared_array<float> tabValues);

    private :

	static shared_array<Point> toTabPoint(shared_array<float> tabValues, int nbPoints);
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
