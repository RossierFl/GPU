#ifndef GLGRAPH_H_
#define GLGRAPH_H_
#include "envGraph.h"
#include "Displayable_A.h"
#include "Viewport.h"
#include "GraphObserver_I.h"
#include "FigureVisitor.h"
#include "Graph.h"
#include "CurveParametric.h"
#include "CurveAnalytic.h"

#include "GLFigure.h"
#include "GLGraphRunnable.h"

#include <map>
using std::map;

#include <queue>
using std::queue;

#include <mutex>
#include <atomic>
//#include <boost/thread/mutex.hpp>
//#include <boost/atomic.hpp>

using std::mutex;
using std::atomic;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GRAPH GLGraph: public GraphObserver_I, public Displayable_A, public FigureVisitor_I
    {
    public:
	GLGraph(Graph* ptrGraph);

	virtual ~GLGraph();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

	/**
	 * Override
	 */
	void init(Panel_A &panel);

	/**
	 * Override
	 */
	void reshape(Panel_A &panel, int w, int h);

	/**
	 * Override
	 */
	void display(Panel_A &panel);

	/**
	 * Override
	 */
	void release(Panel_A &panel);

	/**
	 * Override
	 */
	void onFigureAdd(Figure* ptrFigure);

	/**
	 * Override
	 */
	void onFigureRemove(Figure* ptrFigure);

	/**
	 * Override
	 */
	void update();

	/**
	 * Override
	 * visit create the right GLPolylines
	 */
	virtual void visit(CurveParametric* ptrPolylines);

	/**
	 * Override
	 * visit create the right GLCurve
	 */
	virtual void visit(CurveAnalytic* ptrCurve);

    private:
	void computeViewports(Panel_A &panel);

	int computeTitleHeight(Panel_A &panel);

	void drawGraph(Panel_A &panel);

	void drawTitle(Panel_A &panel);

	void drawLegend(Panel_A &panel);

	void drawGraphCadre(Panel_A &panel);

	void drawGraphGrid(Panel_A &panel);

	void processQueue(Panel_A &panel);

	void updateGL(Panel_A &panel);

	const Font_A* loadFont(FontLoader_A* ptrFontLoader, Title* ptrTitle);

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/

    public:

	Viewport getPanelViewport() const;

	Viewport getGraphViewport() const;

	Viewport getTitleViewport() const;

	Graph* getGraph() const;

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:
	// Inputs
	Graph* ptrGraph;

	// Tools
	atomic<bool> isNeedUpdate;
	map<Figure*, GLFigure*> mapFigureGL;
	queue<GLGraphRunnable*> queueGLGraphRunnable;
	Viewport viewportPanel; //in pixel
	Viewport viewportGraph; //in pixel
	Viewport viewportTitle; //in pixel

	//Thread safe
	mutex mutexQueue;
	mutex mutexMapFigure;

	static const int LEFT_MARGIN;
	static const int RIGHT_MARGIN;
	static const int TOP_MARGIN;
	static const int BOTTOM_MARGIN;
	static const int GRAPH_MARGIN;
	static const float TITLE_V_SPACING;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
