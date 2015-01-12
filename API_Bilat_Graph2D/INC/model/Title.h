#ifndef TITLE_H_
#define TITLE_H_

#include "envGraph.h"
#include "FontLoader_A.h"
#include "Color.h"
#include <string>
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GRAPH Title
    {
    public:
	Title(string texte, string fontname);

	/**
	 * FontType possible :
	 * 	BITMAP_13,
	 * 	BITMAP_15,
	 * 	TIMES_ROMAN_10,
	 * 	TIMES_ROMAN_24,
	 * 	HELVETICA_10,
	 * 	HELVETICA_12,
	 * 	HELVETICA_18
	 */
	Title(string texte, FontType fontType = HELVETICA_12);

	void setTexte(string texte);
	void setFontName(string fontname);
	void setFontType(FontType fontType);

	string getTexte() const
	    {
	    return texte;
	    }

	string getFontName() const
	    {
	    return fontname;
	    }

	FontType getFontType() const
	    {
	    return fontType;
	    }

    private:
	string texte;
	string fontname;
	FontType fontType;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
