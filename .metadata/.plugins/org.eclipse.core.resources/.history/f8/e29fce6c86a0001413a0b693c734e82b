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

	float dt = 0.9;

	double x1 = -2.0;
	double y1 = -2.0;
	double x2 = 2.0;
	double y2 = 2.0;

	float epsilonX= 0.004;
	float epsilonxStart = 0.006;
	float epsilonF = 0.007;

	return new Newton(dw, dh, dt, epsilonX, epsilonF, epsilonxStart, x1, y1, x2, y2);
}

ImageFonctionel* NewtonProvider::createGL()
{
	return new ImageFonctionel(createMOO());
}

