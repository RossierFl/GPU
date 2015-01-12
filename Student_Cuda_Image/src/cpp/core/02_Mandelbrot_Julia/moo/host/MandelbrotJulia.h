#ifndef MANDELBROTJULIA_H_
#define MANDELBROTJULIA_H_

#include "cudaTools.h"
#include "AnimableFonctionel_I.h"
#include "MathTools.h"
#include "VariateurF.h"

class MandelbrotJulia: public AnimableFonctionel_I {

	public:

		MandelbrotJulia(bool isJulia, bool isMultiGPU, int w, int h, float dt, int n, float c1, float c2, float x1, float x2, float y1, float y2);
		virtual ~MandelbrotJulia();

		/**
		 * Override
		 * Call periodicly by the API
		 */
		virtual void animationStep();

		void runGPU(uchar4* ptrDevPixels, const DomaineMath& domaineMath); // Override

		/*
		 * Animation parameters
		 */
		float getT(); // Override
		int getW(); // Override
		int getH(); // Override
		DomaineMath* getDomaineMathInit(); // Override
		string getTitle(); // Override

	private:

		// Inputs
		bool isJulia;
		bool isMultiGPU;
		int w;
		int h;
		int n;
		float c1;
		float c2;

		// Tools
		dim3 dg;
		dim3 db;
		float t; // para animation
		VariateurF variateurAnimation; // varier t
		DomaineMath* ptrDomaineMathInit;

		//Outputs
		string title;
};

#endif
