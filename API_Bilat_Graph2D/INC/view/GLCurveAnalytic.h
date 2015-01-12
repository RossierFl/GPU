#ifndef GLCURVE_H_
#define GLCURVE_H_

#include "GLFigure.h"
#include "CurveAnalytic.h"
#include "VertexBufferObject.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GRAPH GLCurveAnalytic: public GLFigure
    {
    public:
	GLCurveAnalytic(CurveAnalytic* ptrCurve, Domaine* ptrGraphDomaine);
	virtual ~GLCurveAnalytic();

	CurveAnalytic* getCurve() const;

	void init(Panel_A &panel);
	void reshape(Panel_A &panel, const Viewport &viewport);
	void display(Panel_A &panel);
	void release(Panel_A &panel);
	void updateGL(Panel_A &panel,const Domaine &domaineGraph);
    protected:
	void fillTabPoint(Point* ptrTabPoint,int nbPoint);
    private:
	// Inputs
	Domaine* ptrGraphDomaine;

	// Tools
	unsigned int nbPoint;

	// OpenGL
	VertexBufferObject* vboVertex;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
