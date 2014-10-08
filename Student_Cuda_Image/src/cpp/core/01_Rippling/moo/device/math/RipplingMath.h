#ifndef RIPPLING_MATH_H_
#define RIPPLING_MATH_H_

#include <math.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RipplingMath
{

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

public:

	__device__
	RipplingMath(int w, int h)
	{
		this->dim2 = w / 2;
	}

	__device__
	RipplingMath(const RipplingMath& source)
	{
		// TODO
	}

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

public:

	/**
	 * x=pixelI
	 * y=pixelJ
	 */
	__device__
	void color(int i, int j, float t, uchar4& color)
	{
		// Debug (a mettre en commentaire)
//		{
//			unsigned char levelGris = 128; //in [0.255]  (debug image)
//			color.x = levelGris;
//			color.y = levelGris;
//			color.z = levelGris;
//		}

		// Vrai problem
		{
			float ptrResult = 0.0;
			dxy(i,j,&ptrResult);
			double num = cos(ptrResult/10.0-(t/7.0));
			float denom = ptrResult/10.0+1.0;
			double finalResult = 128+127*num/denom;
			color.x = finalResult;
			color.y = finalResult;
			color.z = finalResult;
		}

		color.w = 255; // opaque
	}

private:

	__device__
	void dxy(int i, int j, float* ptrResult) // par exmple
	{
		*ptrResult = sqrt(pow(i-dim2,2)+pow(j-dim2,2));
	}

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

private:

	// Tools
	double dim2; //=dim/2


};

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
