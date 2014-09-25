#ifndef VARIATEUR_F_H_
#define VARIATEUR_F_H_

#include "IntervalF_CPU.h"

using namespace cpu;

/**
 * F pour float
 */
class VariateurF
    {
    public:

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

	VariateurF(const IntervalF& range, float dt);
	VariateurF();
	virtual ~VariateurF();


	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	double varierAndGet();
	double get();

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	float tMin;
	float tMax;
	float dt;

	// tools
	float t;
	bool isCroisssantPhase;

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
