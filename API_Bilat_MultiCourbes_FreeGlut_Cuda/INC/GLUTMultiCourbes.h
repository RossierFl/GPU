#ifndef GLUT_MULTICOURBES_H_
#define GLUT_MULTICOURBES_H_

#include "envBilatMultiCourbeFreeGlut.h"
#include "GLUTWindow.h"
#include "GLMutliCourbes.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_MULTI_COURBES_GLUT GLUTMultiCourbes: public GLUTWindow
    {

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

    public:

	GLUTMultiCourbes(MultiCourbesMOO_A* ptrMultCourbeMOO,string title,string shaderPath, int w, int h, int px=0, int py=0);

	virtual ~GLUTMultiCourbes();

	/*--------------------------------------*\
	 |*		Methode			*|
	 \*-------------------------------------*/

    public:

	/**
	 * Override
	 */
	virtual void idleFunc();

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/

    public:

	MultiCourbesMOO_A* getMultiCourbesMOO();
	GLMutliCourbes* getGLMultiCourbes();


    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
