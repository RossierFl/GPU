#ifndef MANDELBROTJULIAPROVIDER_H_
#define MANDELBROTJULIAPROVIDER_H_

#include "MandelbrotJulia.h"
#include "ImageFonctionel.h"

class MandelbrotJuliaProvider {

	public:

		static MandelbrotJulia* create();
		static ImageFonctionel* createGL();
};

#endif
