#ifndef RIPPLING_IMAGE_H_
#define RIPPLING_IMAGE_H_

#include "ImageMOOs_A.h"
#include "FractalMOO.h"

class FractalImage: public ImageMOOs_A {

	public:

		FractalImage(unsigned int w, unsigned int h, unsigned int n);
		virtual ~FractalImage(void);

	protected:

		/**
		 * Override, call periodicly by the api
		 */
		virtual void fillImageGL(uchar4* ptrTabPixels, int w, int h);

		/**
		 * Override, call periodicly by the api
		 */
		virtual void animationStep(bool& isNeedUpdateView);

		/**
		 * Override, call periodicly by the api
		 */
		virtual void paintPrimitives(Graphic2Ds& graphic2D);

	private:

		// Tools
		FractalMOO* ptrFractalMOO;
};

#endif
