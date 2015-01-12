#ifndef GLUT_WINDOW_IMAGE_H
#define GLUT_WINDOW_IMAGE_H

#include "envImage_FreeGlut.h"

#include "GLUTWindow.h"
#include "GLImages_A.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_IMAGE_FREE_GLUT GLUTWindowImage : public GLUTWindow
    {
    public:
	GLUTWindowImage(GLImages_A* ptrGLImage,string title, int pxFrame = 0, int pyFrame = 0);

	virtual ~GLUTWindowImage();

	/**
	 * Fonction appel� a chaque fois que glut n'a rien � faire dans la mainLoop.
	 * CaD s'il n'y a pas d'�venents utilisateur (souris,clavier,joystick,repaint,etc...)
	 * La fonction animationStep de ImageMOO est appel� ici
	 */
	void idleFunc();

	GLImages_A* getPtrGLImage();

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
