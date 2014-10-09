#ifndef Fractal_MOO_H_
#define Fractal_MOO_H_

#include "cudaType.h"

class FractalMOO {

	public:

		FractalMOO(unsigned int w, unsigned int h, unsigned int n);
		virtual ~FractalMOO(void);

		void process(uchar4* ptrTabPixels, int w, int h);
		void animationStep();

	private:

		void entrelacementOMP(uchar4* ptrTabPixels); 	// Code entrainement Cuda
		void forAutoOMP(uchar4* ptrTabPixels); 		// Code naturel et direct OMP, plus performsnt

	private:

		// Inputs
		unsigned int w;
		unsigned int h;
		unsigned int n;

		// Tools
		bool isEntrelacement;

};

#endif

