#ifndef VARIATEUR_I_H_
#define VARIATEUR_I_H_

#include "IntervalI_CPU.h"

using namespace cpu;

/**
 * I pour Int
 */
class VariateurI
    {
    public:

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

	VariateurI(const IntervalI& range, int dt);
	VariateurI();
	virtual ~VariateurI();


	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	int varierAndGet();
	int get();

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	int tMin;
	int tMax;
	int dt;

	// tools
	int t;
	bool isCroisssantPhase;

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
