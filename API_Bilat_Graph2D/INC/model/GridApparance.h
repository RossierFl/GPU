#ifndef GRIDAPPARANCE_H_
#define GRIDAPPARANCE_H_
#include "envGraph.h"
#include "Color.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GRAPH GridApparance
    {
    public:
	GridApparance(int nbrsLinesX=0,int nbrsLinesY=0,Color lineColor=Color::GRAY);

	void setColor(Color lineColor);
	void setNbLinesX(int nbLinesX);
	void setNbLinesY(int nbLinesY);
	void setGrid(int nbLinesX,int nbLinesY);

	inline Color getColor() const {
	    return lineColor;
	}

	inline int getNbLinesX() const {
	    return nbrLinesX;
	}

	inline int getNbLinesY() const {
	    return nbrLinesY;
	}

    private :
	Color lineColor;
	int nbrLinesX;
	int nbrLinesY;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
