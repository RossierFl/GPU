#include <iostream>
#include <assert.h>
#include <omp.h>
#include <math.h>

#include "MathTools.h"
#include "FractalImage.h"
#include "StringTools.h"
#include "OmpTools.h"

using std::cout;
using std::endl;
using std::string;

FractalImage::FractalImage(unsigned int w, unsigned int h, unsigned int n) :
		ImageMOOs_A(w, h) {
	this->ptrFractalMOO = new FractalMOO(w, h, n);
}

FractalImage::~FractalImage(void) {
	delete ptrFractalMOO;
}

void FractalImage::fillImageGL(uchar4* ptrTabPixels, int w, int h) {
	ptrFractalMOO->process(ptrTabPixels, w, h);
}

void FractalImage::animationStep(bool& isNeedUpdateView) {
	ptrFractalMOO->animationStep();
}

void FractalImage::paintPrimitives(Graphic2Ds& graphic2D) {
	const Font_A* ptrFont = graphic2D.getFont(TIMES_ROMAN_24);

	float r = 1;
	float g = 0;
	float b = 0;
	graphic2D.setColorRGB(r, g, b);

	// Top
	{
		//
	}

	// Bottom
	{
		graphic2D.drawTitleBottom("Fractal OMP", ptrFont);
	}
}
