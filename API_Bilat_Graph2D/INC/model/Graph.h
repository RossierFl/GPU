#ifndef GRAPH_H_
#define GRAPH_H_
#include "envGraph.h"
#include "GridApparance.h"
#include "Figure.h"
#include "GraphObserver_I.h"

#include <vector>
using std::vector;

#include <mutex>
//#include <boost/thread/mutex.hpp>
using std::mutex;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GRAPH Graph
    {
    public:
	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

	Graph(Title title, Domaine domaine, Apparance apparance);

	/**
	 * L'intervalY du domaine du graph est calcul� automatiquement.
	 */
	Graph(Title title, Interval intervalX, Apparance apparance);

	Graph(Title title);

	/**
	 * Graph with title fontType TIMES_ROMAN_24
	 */
	Graph(string title);

	Graph();

    private:

	Graph(const Graph& src);

	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/

    public:
	virtual ~Graph();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void add(Figure* ptrFigure);

	void remove(Figure* ptrFigure);

	void attach(GraphObserver_I* observer);

	void detach(GraphObserver_I* observer);

	void notifyAddFigure(Figure* ptrFigure);

	void notifyRemoveFigure(Figure* ptrFigure);

	void update();
	/**
	 * return true if need repaint
	 */
	virtual bool animationStep();

    private :

	void computeDomaine();

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/

    public :

	/*
	 * getistFigures fourni une copie du vector de figure
	 */
	vector<Figure*> getListFigures() const;

	Figure* getFigure(int i);

	GridApparance* getGridApparance() const;

	Apparance* getApparance() const;

	Title* getTitle() const;

	Domaine* getDomaine() const;

	int getFigureSize() const;

	/*--------------------------------------*\
	 |*		Set			*|
	 \*-------------------------------------*/

	void setApparance(Apparance apparance);

	/**
	 * set Title with fontType TIMES_ROMAN_24
	 */
	void setTitle(string title);

	void setTitle(Title title);

	void setDomaine(Domaine domaine);

	void setIntervalX(Interval intervalX);

	void setGridApparance(GridApparance gridApparance);

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	Title* title;
	Domaine* domaine;
	Apparance* apparance;
	bool isIntervalYAuto;

	// Tools
	GridApparance* gridApparance;
	vector<Figure*> listFigures;
	vector<GraphObserver_I*> listObserver;
	mutex mutexListObserver;
	mutex mutexListFigures;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
