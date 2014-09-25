#ifndef EVENT_IMAGE_H_
#define EVENT_IMAGE_H_

#include "Event.h"
#include "ImageFonctionel.h"
#include "SimpleKeyListener.h"
#include "SimpleMouseListener.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class EventImage: public ImageFonctionel
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:


	EventImage(Event* ptrEvent);


	virtual ~EventImage(void);

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    private:

	   void control(void);

	/*--------------------------------------*\
		|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Tools
	SimpleKeyListener* ptrKeyListener;
	SimpleMouseListener* ptrMouseListener;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
