#ifndef FIGURE_H_
#define FIGURE_H_

#include "envGraph.h"
#include "Title.h"
#include "Domaine.h"
#include "Apparance.h"

//#include "FigureVisitor.h"
class FigureVisitor_I;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GRAPH Figure
    {
    public:
	Figure(Title title,Apparance apparance);
	virtual ~Figure();

	Apparance* getApparance() const;

	Title* getTitle() const;

	virtual Domaine computeDomaine(const Domaine& graphDomaine) const =0;

	virtual void accept(FigureVisitor_I* ptrVisitor) =0;

	/**
	 * Call animationStep of all stored Figures and the update
	 */
	virtual void animationStep();

	bool isAnimationEnable();

	void setAnimationEnable(bool isEnable);

    private :
	Title* ptrTitle;
	Apparance* ptrApparance;
	bool animationEnable;

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
