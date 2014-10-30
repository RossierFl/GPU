#include "NewtonProvider.h"
#include "MathTools.h"

/*----------------------------------------------------------------------*\
|*			Declaration 												*|
\*----------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Imported					 	*|
\*--------------------------------------*/

/*--------------------------------------*\
|*		Public							*|
\*--------------------------------------*/

/*--------------------------------------*\
|*		Private							*|
\*--------------------------------------*/

/*----------------------------------------------------------------------*\
|*			Implementation 												*|
\*----------------------------------------------------------------------*/

Newton* NewtonProvider::createMOO()
{
	int dw = 16 * 60; // =32*30=960
	int dh = 16 * 60; // =32*30=960

	int n = 102;
	float dt = 0.15;

	double x1 = -2.0;
	double y1 = -2.0;
	double x2 = 2.0;
	double y2 = 2.0;

	float epsilonx = 0.01;
	float epsilonxstar = 0.01;
	float epsilonf = 0.01;

	return new Newton(dw, dh, dt, n, epsilonx, epsilonf, epsilonxstar, x1, y1, x2, y2);
}

ImageFonctionel* NewtonProvider::createGL()
{
	return new ImageFonctionel(createMOO());
}

