#ifndef GRAPHIC2DS_H
#define GRAPHIC2DS_H

#include "envGLImage.h"
#include "Panel_A.h"
#include "Font_A.h"
#include "Color3f.h"
#include "Primitives_A.h"

#include <string>
#include <queue>

using std::queue;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GLIMAGE Graphic2Ds
    {
    public:

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

	Graphic2Ds(int width, int height);

	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/

	virtual ~Graphic2Ds();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

	/*--------------*\
	 |*	User	*|
	 \*-------------*/

    public:

	void setColor(Colorf colorf);

	void setColorRGB(float r01, float g01, float b01, float a01 = 1.0f);

	void setColorHSB(float h01, float s01, float b01, float a01 = 1.0f);

	void drawLigne(int x1, int y1, int x2, int y2);

	void drawVerticalLigne(int x, int y, int height);

	void drawHorizontalLigne(int x, int y, int width);

	void drawWiredRect2D(int x, int y, int width, int height);

	void drawRect2D(int x, int y, int width, int height);

	void drawText(int x, int y, string texte, const Font_A* font);

	void drawTitleTop(string texte, const Font_A* font);

	void drawTitleMiddle(string texte, const Font_A* font);

	void drawTitleBottom(string texte, const Font_A* font);

	const Font_A* getFont(string fontname);

	const Font_A* getFont(FontType type = HELVETICA_12);

	int texteWidth(string texte, const Font_A* font);

	int texteHeight(string texte, const Font_A* font);

	/*--------------*\
	|*  Developer	*|
	 \*--------------*/

	unsigned int getSize();

	bool isEmpty();

	void reshape(int width, int height);

	void startPainPrimitive(Panel_A &ptrPanel);

	void drawPrimitive(Primitives_A* primitive);

	Primitives_A* popPrimitive();

	Colorf popColor();

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/
    private:

	// Inputs
	int width;
	int height;
	Panel_A* ptrPanel;

	// Tools
	Colorf currentColor;
	queue<Colorf> queueColors;
	queue<Primitives_A*> queuePrimitives;

	int frameWidth;
	int frameHeight;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

