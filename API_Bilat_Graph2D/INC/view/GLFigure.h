#ifndef GLFIGURE_H_
#define GLFIGURE_H_
#include "envGraph.h"
#include "Viewport.h"
#include "Figure.h"
#include "Panel_A.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GRAPH GLFigure
    {
    public:
	GLFigure(Figure* ptrFigure);
	virtual ~GLFigure();

	virtual void init(Panel_A &panel);
	virtual void reshape(Panel_A &panel, const Viewport &viewport)=0;
	virtual void display(Panel_A &panel)=0;
	virtual void release(Panel_A &panel)=0;

	Figure* getFigure() const;

	/**
	 * Will update the courbe after repaint
	 */
	virtual void updateGL(Panel_A &panel,const Domaine &domaineGraph)=0;
    protected:
	Figure* ptrFigure;
	bool isInit;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
