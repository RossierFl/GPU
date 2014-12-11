#ifndef HistogrammeHOST_H_
#define HistogrammeHOST_H_

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class HistogrammeHost
    {
    public:
	HistogrammeHost();
	virtual ~HistogrammeHost();
	static void MyCalculateHistogramme();
	static bool isGoodHistogramme(int histogramme[],int sizeTableValues);
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
