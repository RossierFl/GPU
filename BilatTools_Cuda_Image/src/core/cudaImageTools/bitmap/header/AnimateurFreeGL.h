#ifndef ANIMATEUR_FREE_GL_H_
#define ANIMATEUR_FREE_GL_H_

#include "Animable_I.h"

using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class AnimateurFreeGL
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
	AnimateurFreeGL(Animable_I* ptrAnimable,int nbIteration=1000);
	virtual ~AnimateurFreeGL(void);

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
	Animable_I* ptrAnimable;

	// Tools

	// Output
	int fps;
	float timeElapseS;

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

