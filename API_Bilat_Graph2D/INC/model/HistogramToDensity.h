#ifndef HISTOGRAMTODENSITY_H_
#define HISTOGRAMTODENSITY_H_

#include "Histogram.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GRAPH HistogramToDensity: public Histogram
    {
    public:
	HistogramToDensity(Title title, Apparance apparance, shared_array<float> tabvalues, int nbValue,Interval intervalX, int nbrSep, float maxDensityAnalytiqueY);
	virtual ~HistogramToDensity();

	void setMaxDensityAnalytiqueY(float maxDensityAnalytiqueY);
	float getMaxDensityAnalytiqueY() const;

	/*--------------------------------------*\
	 |*		Surcharge		*|
	 \*-------------------------------------*/

	void setValue(shared_array<float> tabvalues, int nbValue);
	virtual Domaine computeDomaine(const Domaine& graphDomaine) const;

    private:
	float computeFactor();
	void correctionDensity();
    private:
	float factor;
	float maxDensityAnalytiqueY;
	float maxHistogram;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
