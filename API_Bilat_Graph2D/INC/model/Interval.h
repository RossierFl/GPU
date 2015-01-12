#ifndef INTERVAL_H_
#define INTERVAL_H_
#include "envGraph.h"
#include "Definitions.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GRAPH Interval
    {
    public:
	Interval(double min, double max);

	void setMin(double min);
	void setMax(double max);

	double delta() const;
	double deltaAbs() const;

	inline double getMin() const
	    {
	    return min;
	    }

	inline double getMax() const
	    {
	    return max;
	    }

    private:
	double min;
	double max;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
