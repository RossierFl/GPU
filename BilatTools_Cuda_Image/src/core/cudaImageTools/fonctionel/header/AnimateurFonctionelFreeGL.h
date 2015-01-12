#ifndef ANIMATEUR_FONCTIONEL_FREE_GL_H_
#define ANIMATEUR_FONCTIONEL_FREE_GL_H_

#include "AnimableFonctionel_I.h"

using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class AnimateurFonctionelFreeGL
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	/**
	 * Hyp:
	 * 	(H1) nbIteration suffisamment grand pour que timeElapse soit significatif
	 * 	(H2) ptrAnimable image uchar4
	 */
	AnimateurFonctionelFreeGL(AnimableFonctionel_I* ptrAnimable,int nbIteration=1000);
	virtual ~AnimateurFonctionelFreeGL(void);

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public :

	   int getFps(void);

    private:

	/**
	 * Synchrone, ,return fps
	 */
	int start(void);
	void printStat(void);

    private:

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	int nbIteration;
	AnimableFonctionel_I* ptrAnimable;

	// Tools

	// Output
	int fps;
	float timeElapseS;

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

