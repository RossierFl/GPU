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
	 * Fonction appelé a chaque fois que glut n'a rien à faire dans la mainLoop.
	 * CaD s'il n'y a pas d'évenents utilisateur (souris,clavier,joystick,repaint,etc...)
	 * La fonction animationStep de ImageMOO est appelé ici
	 */
	void idleFunc();

	GLImages_A* getPtrGLImage();

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
