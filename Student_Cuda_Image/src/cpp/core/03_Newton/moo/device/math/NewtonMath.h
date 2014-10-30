#ifndef NEWTONMATH_H_
#define NEWTONMATH_H_

#include <math.h>

#include "CalibreurF.h"
#include "ColorTools.h"

#define NOIR 0
#define GRIS 1;
#define BLANC 2;
#define NOT_CONVERGE_ERROR 3;

/*----------------------------------------------------------------------*\
|*			Declaration 												*|
\*----------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Public							*|
\*--------------------------------------*/

/*--------------------------------------*\
|*		Private							*|
\*--------------------------------------*/

typedef struct ResultStructure
{
	float x1;
	float x2;
} Result;


class NewtonMath
{

/*--------------------------------------*\
|*		Constructor						*|
\*--------------------------------------*/

public:

	__device__ NewtonMath(int n)
	{
		this->n = n;
		xa.x1 = 1.0;
		xa.x2 = 0.0;
		xb.x1 = -0.5;
		xb.x2 = sqrt(3) / 2;
		xc.x1 = -0.5;
		xc.x2 = -sqrt(3) / 2;
	}

	__device__ virtual ~NewtonMath()
	{
	}

/*--------------------------------------*\
|*		Methods							*|
\*--------------------------------------*/

private:

	__device__ inline float normSquare(float x1, float x2)
	{
		return x1 * x1 + x2 * x2;
	}

	__device__ inline float f1(float x1, float x2)
	{
		return (x1 * x1 * x1) - (3 * x1 * (x2 * x2)) - 1;
	}

	__device__ inline float f2(float x1, float x2)
	{
		return (x2 * x2 * x2) - (3 * x2 * (x1 * x1));
	}

	__device__ inline void jacobienne(float x1, float x2, float* matrix)
	{
		matrix[0] = 3 * x1 * x1 - 3 * x2 * x2;
		matrix[1] = -6 * x1 * x2;
		matrix[2] = -6 * x2 * x1;
		matrix[3] = 3 * x2 * x2 - 3 * x1 * x1;
	}

	__device__ inline float det(float* matrix)
	{
		return (matrix[0] * matrix[3]) - (matrix[1] * matrix[2]);
	}

	__device__ inline void inverse(float* matrix)
	{
		float det = det(matrix);
		float aCopy = matrix[0];
		float bCopy = matrix[1];
		float cCopy = matrix[2];
		float dCopy = matrix[3];
		matrix[0] = dCopy / det;
		matrix[1] = -bCopy / det;
		matrix[2] = -cCopy / det;
		matrix[3] = aCopy / det;
	}

	__device__ inline void matrixVectorMult(float* matrix, float x1, float x2, float* solX1, float* solX2)
	{
		*solX1 = matrix[0] * x1 + matrix[1] * x2;
		*solX2 = matrix[2] * x1 + matrix[3] * x2;
	}

	__device__ int indiceArret(float x1, float x2, float epsilonx, float epsilonf, float epsilonxstar)
	{
		float crtX1 = x1;
		float crtX2 = x2;

		float nextX1;
		float nextX2;
		float solX1;
		float solX2;
		int i = 0;
		const int CONVERGE_LIMIT = 200;
		float jacobienne[4];
		while (i < CONVERGE_LIMIT)
		{
			// Compute the jacobienne
			jacobienne(crtX1, crtX2, jacobienne);

			// Inverse the jacobienne
			inverse(jacobienne);

			float f1 = f1(crtX1, crtX2);
			float f2 = f2(crtX1, crtX2);
			matrixVectorMult(jacobienne, f1, f2, &solX1, &solX2);
			nextX1 = crtX1 - solX1;
			nextX2 = crtX2 - solX2;

			// Current X is near solution a, b or c
			if (normSquare(crtX1 - xa.x1, crtX2 - xa.x2) / normSquare(xa.x1, xa.x2) < epsilonxstar)
			{
				return NOIR;
			}
			else if (normSquare(crtX1 - xb.x1, crtX2 - xb.x2) / normSquare(xb.x1, xb.x2) < epsilonxstar)
			{
				return GRIS;
			}
			else if (normSquare(crtX1 - xc.x1, crtX2 - xc.x1) / normSquare(xc.x1, xc.x2) < epsilonxstar)
			{
				return BLANC;
			}

			// iteration doesn't move enough OR solution is good enough
			if (normSquare(crtX1 - nextX1, crtX2 - nextX2) / normSquare(nextX1, nextX2) < epsilonx ||
				normSquare(f1(crtX1, crtX2) - f1(nextX1, nextX2), f2(crtX1, crtX2) - f2(nextX1, nextX2)) / normSquare(f1(nextX1, nextX2), f2(nextX1, nextX2)) < epsilonf)
			{
				float diffA = normSquare(nextX1 - xa.x1, nextX2 - xa.x2) / normSquare(xa.x1, xa.x2);
				float diffB = normSquare(nextX1 - xb.x1, nextX2 - xb.x2) / normSquare(xb.x1, xb.x2);
				float diffC = normSquare(nextX1 - xc.x1, nextX2 - xc.x2) / normSquare(xc.x1, xc.x2);

				if (diffA < diffB)
				{
					if (diffA < diffC)
						return NOIR; // near xa
					else
						return BLANC; // near xc
				}
				else if (diffB < diffC)
					return GRIS; // near xb
				else
					return BLANC; // near xc
			}
			crtX1 = nextX1;
			crtX2 = nextX2;
			i++;
		}
		return NOT_CONVERGE_ERROR;
	}

public:

	__device__ void colorXY(uchar4* ptrColor, float x, float y, float epsilonx, float epsilonf, float epsilonxstar)
	{
		int color = indiceArret(x, y, epsilonx, epsilonf, epsilonxstar);
		if (color == NOIR)
		{
			ptrColor->x = 0;
			ptrColor->y = 0;
			ptrColor->z = 0;
		}
		else if (color == GRIS)
		{
			ptrColor->x = 211;
			ptrColor->y = 211;
			ptrColor->z = 211;
		}
		else if (color == BLANC)
		{
			ptrColor->x = 255;
			ptrColor->y = 255;
			ptrColor->z = 255;
		}
		else if (color == NOT_CONVERGE_ERROR)
		{
			// orange
			ptrColor->x = 255;
			ptrColor->y = 165;
			ptrColor->z = 0;
		}

		ptrColor->w = 255; // opaque
	}

/*--------------------------------------*\
|*		Attributs						*|
\*--------------------------------------*/

protected:

	// Input
	int n;

	// Tools
	Result xa;
	Result xb;
	Result xc;
};


#endif