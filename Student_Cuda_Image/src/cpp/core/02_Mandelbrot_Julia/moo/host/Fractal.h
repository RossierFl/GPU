#ifndef Fractal_H_
#define Fractal_H_

#include "cudaTools.h"
#include "AnimableFonctionel_I.h"
#include "MathTools.h"
#include "VariateurF.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Fractal : public AnimableFonctionel_I {
		/*--------------------------------------*\
	|*		Constructor		*|
		 \*-------------------------------------*/

	public:

		Fractal(int w, int h, float dt, int n, double x1, double y1, double x2, double y2);
		virtual ~Fractal();

		/*--------------------------------------*\
	 |*		Methodes		*|
		 \*-------------------------------------*/

	public:

		/*----------------*\
	|*  Override	  *|
		 \*---------------*/

		void runGPU(uchar4* ptrDevPixels, const DomaineMath& domaineMath);
		virtual void animationStep();

		 float getT();
		 int getW();
		 int getH();
		 DomaineMath* getDomaineMathInit();

		 string getTitle();

	private:

		/*--------------------------------------*\
	 |*		Attributs		*|
		 \*-------------------------------------*/

	private:

		// Inputs
		int w;
		int h;
		int n;

		// Tools
		dim3 dg;
		dim3 db;
		DomaineMath* domaineMath;
		VariateurF variateur;

		//Outputs
		string title;
		float t;
};

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
