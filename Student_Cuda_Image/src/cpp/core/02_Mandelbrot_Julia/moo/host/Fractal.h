#ifndef Fractal_H_
#define Fractal_H_

#include "cudaTools.h"
#include "AnimableFonctionel_I.h"
#include "MathTools.h"
#include "VariateurI.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Fractal: public AnimableFonctionel_I {
		/*--------------------------------------*\
	|*		Constructor		*|
		 \*-------------------------------------*/

	public:

		Fractal(int w, int h, float dt, int n, float x1, float y1, float x2, float y2);
		virtual ~Fractal();

		/*--------------------------------------*\
	 |*		Methodes		*|
		 \*-------------------------------------*/

	public:

		/*----------------*\
	|*  Override	  *|
		 \*---------------*/

		virtual void runGPU(uchar4* ptrDevPixels, DomaineMath& domaineMath);
		virtual void animationStep();

		virtual float getT();
		virtual int getW();
		virtual int getH();
		virtual DomaineMath* getDomaineMathInit();

		virtual string getTitle();

	private:

		/*--------------------------------------*\
	 |*		Attributs		*|
		 \*-------------------------------------*/

	private:

		// Inputs
		int w;
		int h;
		int n;
		float x1;
		float y1;
		float x2;
		float y2;

		// Tools
		dim3 dg;
		dim3 db;
		DomaineMath* domaineMath;
		VariateurI variateur;

		//Outputs
		string title;
};

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
