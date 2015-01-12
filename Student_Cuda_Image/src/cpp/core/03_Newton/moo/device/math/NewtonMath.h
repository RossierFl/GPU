#ifndef NEWTONMATH_H_
#define NEWTONMATH_H_

#include <math.h>



/*----------------------------------------------------------------------*\
|*			Declaration 												*|
 \*----------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Public							*|
 \*--------------------------------------*/

/*--------------------------------------*\
|*		Private							*|
 \*--------------------------------------*/



class NewtonMath
    {

	/*--------------------------------------*\
|*		Constructor						*|
	 \*--------------------------------------*/

    public:

	__device__ NewtonMath(int n)
	    {
	    this->n = n;
	    xa[0] = 1.0;
	    xa[1] = 0.0;
	    xb[0] = -0.5;
	    xb[1] = sqrt(3.0) / 2;
	    xc[0] = -0.5;
	    xc[1] = -sqrt(3.0) / 2;
	    }

	__device__      virtual ~NewtonMath()
	    {
	    }

	/*--------------------------------------*\
|*		Methods							*|
	 \*--------------------------------------*/

    private:

	__device__
	 float normSquare(float x1, float x2)
	    {
	    return x1 * x1 + x2 * x2;
	    }

	__device__
		 float f(float x1, float x2,float* result)
		    {
			result[0]=(x1 * x1 * x1) - (3 * x1 * (x2 * x2)) - 1;
			result[1]=(x2 * x2 * x2) - (3 * x2 * (x1 * x1));
		    }



	// Jacobienne
	__device__
	 void fJacobienne(float x1, float x2, float* matrix)
	    {
	    matrix[0] = 3 * x1 * x1 - 3 * x2 * x2;
	    matrix[1] = -6 * x1 * x2;
	    matrix[2] = -6 * x2 * x1;
	    matrix[3] = 3 * x2 * x2 - 3 * x1 * x1;
	    }


	//Determinant
	__device__
	 float det(float* matrix)
	    {
	    return (matrix[0] * matrix[3]) - (matrix[1] * matrix[2]);
	    }

	//Inversion de matrice
	__device__
	 void inverseMatix(float* matrix)
	    {
	    float determinant = det(matrix);
	    float aCopy = matrix[0];
	    float bCopy = matrix[1];
	    float cCopy = matrix[2];
	    float dCopy = matrix[3];
	    matrix[0] = dCopy / determinant;
	    matrix[1] = -bCopy / determinant;
	    matrix[2] = -cCopy / determinant;
	    matrix[3] = aCopy / determinant;
	    }

	__device__
	 void matrixVectorMult(float* matrix, float x1, float x2, float* solX1, float* solX2)
	    {
	    *solX1 = matrix[0] * x1 + matrix[1] * x2;
	    *solX2 = matrix[2] * x1 + matrix[3] * x2;
	    }

	__device__
	int indiceArret(float x1, float x2, float epsilonx, float epsilonf, float epsilonxstar)
	    {
	    float crtX1 = x1;
	    float crtX2 = x2;

	    float nextX1;
	    float nextX2;
	    float solX1;
	    float solX2;
	    float jacob[4];

	    for (int i = 0; i < n; i++)
		{
		// Compute the jacobienne
		fJacobienne(crtX1, crtX2, jacob);

		// Inverse the jacobienne
		inverseMatix(jacob);

		// Current X is near solution a, b or c
		if (normSquare(crtX1 - xa[0], crtX2 - xa[1]) / normSquare(xa[0], xa[1]) < epsilonxstar)
		    {
		    return XA;
		    }
		else if (normSquare(crtX1 - xb[0], crtX2 - xb[1]) / normSquare(xb[0], xb[1]) < epsilonxstar)
		    {
		    return XB;
		    }
		else if (normSquare(crtX1 - xc[0], crtX2 - xc[0]) / normSquare(xc[0], xc[1]) < epsilonxstar)
		    {
		    return XC;
		    }

		// Compute x(i+1)
		float resultF[2];
		f(crtX1,crtX2,resultF);
		//float resF1 = f1(crtX1, crtX2);
		//float resF2 = f2(crtX1, crtX2);
		matrixVectorMult(jacob, resultF[0], resultF[1], &solX1, &solX2);
		nextX1 = crtX1 - solX1;
		nextX2 = crtX2 - solX2;
		crtX1 = nextX1;
		crtX2 = nextX2;
		}
	    return 0;
	    }

    public:

	__device__
	void colorIJ(uchar4* ptrColor, float x, float y, float epsilonx, float epsilonf, float epsilonxstar)
	    {
	    int indice = indiceArret(x, y, epsilonx, epsilonf, epsilonxstar);
	    ptrColor->w = 255; // opaque
	    switch (indice)
		{
		case XA:
		    ptrColor->x = 0;
		    ptrColor->y = 0;
		    ptrColor->z = 0;
		    break;

		case XB:
		    ptrColor->x = 211;
		    ptrColor->y = 211;
		    ptrColor->z = 211;
		    break;

		case XC:
		    ptrColor->x = 255;
		    ptrColor->y = 255;
		    ptrColor->z = 255;
		    break;

		default:
		    ptrColor->x = 30;
		    ptrColor->y = 30;
		    ptrColor->z = 30;
		    break;
		}
	    }

	/*--------------------------------------*\
|*		Attributs						*|
	 \*--------------------------------------*/

    private:
	// Input
	int n;


	float xa[2];
	float xb[2];
	float xc[2];

	static const int XA = 1;
	static const int XB = 2;
	static const int XC = 3;

	static const int CONVERGE_LIMIT = 200;

    };

#endif
