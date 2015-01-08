#ifndef MandelbrotJulia_MATH_H_
#define MandelbrotJulia_MATH_H_

#include <math.h>

#include "CalibreurF.h"
#include "ColorTools.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/


class MandelbrotJuliaMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__
	MandelbrotJuliaMath(int n,bool isJulia,float cX=0, float cY=0):calibreur(IntervalF(-1, 1), IntervalF(0, 1))
	    {
	     this->n = n;
	    this->cX=cX;
	    this->cY=cY;
	    this->isJulia=isJulia;
	    }

	// constructeur copie automatique car pas pointeur dans
	//	MandelbrotJuliaMath
	// 	calibreur
	// 	IntervalF

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/**
	 * x=pixelI
	 * y=pixelJ
	 */
	__device__
	void colorXY(uchar4* ptrColor, float x, float y, const DomaineMath& domaineMath, float t)
	    {
	    int s =0;
	    if(isJulia){
		s = j(x,y,cX,cY,t);
	    }else{
		s= f(x, y, t,isJulia);
	    }
	   
	    if(!isConvergent(s,t)){
		 
		 float hue01 = h_color(s,t);

		ColorTools::HSB_TO_RVB(hue01, ptrColor); // update color
		
	    }else {
		ptrColor->x=0;
		ptrColor->y=0;
		ptrColor->z=0;
		
	    }
	    ptrColor->w = 255; // opaque
	    }

    private:

	__device__
	float f(float x, float y, float t,bool isJulia)
	    {
	    float a=0;
		float b=0;
		if(isJulia){
		    a=x;
		    b=y;
		}
		int k=0;

		while(k<t && (a*a+b*b)<=4){
		    float aCopy = a;
		    a=(a*a-b*b)+x;
		    b=2*aCopy*b+y;
		    //cout<<"Value:"<< (a*a+b*b)<<endl;
		    k++;
		}
		//cout<<"K:"<<k<<endl;
		return k;
	    }

		__device__ int j(float x, float y, float cX,float cY,float t)
		    {


			float a=x;
			float b=y;

			int k=0;

			while(k<t && (a*a+b*b)<=4){
			    float aCopy = a;
			    a=(a*a-b*b)+cX;
			    b=2*aCopy*b+cY;
			    
			    k++;
			}
			
			return k;
		    }
			
		__device__	bool isConvergent(int s,int n){
	    return s==n ;
	}

	__device__ float h_color(int s,int n){
	    return (float)s/(float)n;
	}
	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	int n;
	float cX;
	float cY;
	bool isJulia;

	// Tools
	CalibreurF calibreur;

    };



#endif 



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
