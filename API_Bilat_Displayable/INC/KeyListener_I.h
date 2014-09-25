#ifndef KEY_LISTENER_I_H
#define KEY_LISTENER_I_H

#include "KeyEvent.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_DISPLAYABLE KeyListener_I
    {
    public:
	virtual ~KeyListener_I()
	    {
	    // Nothing
	    }

	virtual void onKeyPressed(const KeyEvent& event)=0;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
