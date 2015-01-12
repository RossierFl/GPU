#ifndef GLPOLYLINES_H_
#define GLPOLYLINES_H_

#include "GLFigure.h"
#include "CurveParametric.h"
#include "VertexBufferObject.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GRAPH GLCurveParametric: public GLFigure
    {
    public:
	GLCurveParametric(CurveParametric* ptrPolyline);
	virtual ~GLCurveParametric();

	CurveParametric* getPolyline() const;

	void init(Panel_A &panel);
	void reshape(Panel_A &panel, const Viewport &viewport);
	void display(Panel_A &panel);
	void release(Panel_A &panel);
    protected:
	void updateGL(Panel_A &panel,const Domaine &domaineGraph);
    private:

	// OpenGL
	VertexBufferObject* vboVertex;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
