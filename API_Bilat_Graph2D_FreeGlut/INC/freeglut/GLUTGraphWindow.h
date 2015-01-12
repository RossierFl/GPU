#ifndef GLUT_GRAPHWINDOW_H_
#define GLUT_GRAPHWINDOW_H_
#include "envGraphFreeGlut.h"
#include "GLUTWindow.h"
#include "GLGraph.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Encapsulate Graph in a GLUTWindow with animation managment (idleFunc)
 */
class CBI_GRAPH_FREE_GLUT GLUTGraphWindow: public GLUTWindow
    {
    public:
	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

	GLUTGraphWindow(Graph* ptrGraph, string title, int width, int height, int pxFrame = 0, int pyFrame = 0);

	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/

	virtual ~GLUTGraphWindow();

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/

	Graph* getGraph();

	GLGraph* getGLGraph();

	/*--------------------------------------*\
	 |*		Surcharge		*|
	 \*-------------------------------------*/

	/**
	 * Call periodicaly by FreeGlut
	 */
	virtual void idleFunc();

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
