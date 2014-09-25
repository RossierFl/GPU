#ifndef HISTOGRAM_H_
#define HISTOGRAM_H_

#include "Polylines.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GRAPH Histogram: public Polylines
    {
    public:
	/**
	 * Create an histogram with nbrSep+1 bins
	 * @param nbrSep the number of separation.
	 */
	Histogram(Title title, Apparance apparance, shared_array<float> tabvalues, int nbValue,Interval intervalX, int nbrSep);
	virtual ~Histogram();

	void setValue(shared_array<float> tabvalues, int nbValue);

	static int computeNbPoint(int nbrSep);

	void minMaxValues(Interval& minMax);
	void setIntervalGraphX(Interval intervalX);

    protected:
	/**
	 * Compute the histogram
	 */
	void computeHistogram();


	/**
	 * Create the histogram with the points.
	 */
	void computeFigure();

    protected:
	// Inputs
	shared_array<float> tabvalues;
	int nbValue;
	int nbrSep;

	// Tools
	float* tabHistogram;
	Interval intervalGraphX;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
