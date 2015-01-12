#ifndef GLGRAPHRUNNABLE_H_
#define GLGRAPHRUNNABLE_H_
#include "envGraph.h"
#include "Panel_A.h"
#include "Viewport.h"
#include "GLFigure.h"
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GRAPH GLGraphRunnable
    {
    public:
	virtual ~GLGraphRunnable()
	    {
	    }
	virtual void run(Panel_A &panel)=0;
    };

/**
 * Free GLResources
 * delete ptrGLFigure
 */
class CBI_GRAPH GLGraphRelease: public GLGraphRunnable
    {
    public:
	GLGraphRelease(GLFigure* ptrGLFigure);
	virtual ~GLGraphRelease();
	virtual void run(Panel_A &panel);
    private:
	GLFigure* ptrGLFigure;
    };

/**
 * Initialize GLFigure
 * call reshape GLFigure with given viewport
 */
class CBI_GRAPH GLGraphInit: public GLGraphRunnable
    {
    public:
	GLGraphInit(GLFigure* ptrGLFigure, Viewport* ptrViewport);
	virtual ~GLGraphInit();
	virtual void run(Panel_A &panel);
    private:
	GLFigure* ptrGLFigure;
	Viewport* ptrViewport;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
