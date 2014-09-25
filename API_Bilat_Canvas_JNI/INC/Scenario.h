#ifndef SCENARIO_H_
#define SCENARIO_H_

#include "envCanvasJNI.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Un scénario - Un CanvasNative
 *
 * getCanvasNativeID doit être redefinie avec un canvasNativeID valide.
 */
class CBI_CANVAS_JNI Scenario
    {
    public:

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

	Scenario();

	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/

	virtual ~Scenario();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/**
	 * Doit être appelé après avoir construit le scénario
	 * MyScenario* ptrMyScenario=new MyScenario();
	 * ptrMyScenario->registry();
	 */
	void registry();


	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/


	/**
	 * Il faut retourner impérativement le canvasNativeID d'un CanvasNative précèdement instancié.
	 */
	virtual int getCanvasNativeID()=0;

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
