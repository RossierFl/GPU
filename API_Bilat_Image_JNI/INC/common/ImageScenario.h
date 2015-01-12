#ifndef IMAGESCENARIO_H_
#define IMAGESCENARIO_H_

#include "envImageJNI.h"
#include "Scenario.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_IMAGE_JNI ImageScenario : public Scenario
    {
    public:
	ImageScenario(int w, int h) : w(w),h(h)
	    {

	    }

	virtual ~ImageScenario()
	    {
	    //because getCanvasNativeID is virtual
	    }

	virtual int getCanvasNativeID()=0;

    protected:
	int w;
	int h;

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
