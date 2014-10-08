#include <iostream>
#include <stdlib.h>

#include "AnimateurFreeGL.h"
#include "AnimateurFonctionelFreeGL.h"

#include "VagueProvider.h"
#include "DamierProvider.h"
#include "EventProvider.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern int vague0FreeGL(int itmax); // bad technique

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainFreeGL(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainFreeGL(void)
    {
    cout << "\n[FPS] :  Free GL, please wait ..." << endl;

    vague0FreeGL(1000); // bad technique

    Vague* ptrVague = VagueProvider::create(); // good technique
    Damier* ptrDamier = DamierProvider::create();
    Event* ptrEvent = EventProvider::create();

    AnimateurFreeGL vagueFreeGL(ptrVague);
    AnimateurFonctionelFreeGL damierFreeGL(ptrDamier);
    AnimateurFonctionelFreeGL eventFreeGL(ptrEvent);

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

