#ifndef COLORS_H_
#define COLORS_H_

#include "envGraph.h"
#include "Definitions.h"
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/



class CBI_GRAPH Color
    {
    public:

	Color(uchar r = 0, uchar g = 0, uchar b = 0, uchar a = 255);
	//Color(const Color &source);//inutil car que des type simple, le compilo copie bit a bit les attributs

	inline uchar getRed() const
	    {
	    return r;
	    }

	inline uchar getGreen() const
	    {
	    return g;
	    }

	inline uchar getBlue() const
	    {
	    return b;
	    }

	inline uchar getAlpha() const
	    {
	    return a;
	    }

    public:
	static const Color RED;
	static const Color BLUE;
	static const Color GREEN;

	static const Color WHITE;
	static const Color BLACK;
	static const Color GRAY;

	static const Color YELLOW;
	static const Color CYAN;
	static const Color MAGANTA;
	static const Color ORANGE;
	static const Color LIME;
	static const Color PINK;
	static const Color PURPLE;

    private:
	uchar r;
	uchar g;
	uchar b;
	uchar a;

    };

#endif




/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
