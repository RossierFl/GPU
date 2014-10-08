#ifndef MandelbrotJulia_MATH_H_
#define MandelbrotJulia_MATH_H_

#include "CalibreurF.h"
#include "ColorTools.h"
#include <math.h>
#include <complex>

using namespace std;
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Dans un header only pour preparer la version cuda
 */
class MandelbrotJuliaMath
    {
	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	/**
	 * calibreurColor : transformation affine entre [-1,1] (l'output de f(x,y)) et [0,1] (le spectre hsb)
	 */
	__device__
	MandelbrotJuliaMath(int n,bool isJulia,double cX=0, double cY=0) :
		calibreur(IntervalF(-1, 1), IntervalF(0, 1))
	    {
	    this->n = n;
	    this->cX=cX;
	    this->cY=cY;
	    this->isJulia=isJulia;
	    }

	virtual ~MandelbrotJuliaMath(void)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:
	__device__
	void colorXY(uchar4* ptrColor, double x, double y, const DomaineMath& domaineMath, double t)
	    {
	//cout << "X : " << x << endl;
	//cout << "Y : " << y << endl;

	    int s =0;
	    if(isJulia){
		s = j(x,y,cX,cY,t);
	    }else{
		s= f(x, y, t,isJulia);
	    }
	    //cout << "Z: " << z << endl;

	    //cout << "Nbr : " << z << endl;
	    if(!isConvergent(s,t)){
		 //calibreur.calibrer(s);
		 float hue01 = h_color(s,t);

		ColorTools::HSB_TO_RVB(hue01, ptrColor); // update color
		// cout << "S: " << s << endl;
		/* ptrColor->x=255;
		 ptrColor->y=255*s/(double)t;
		 ptrColor->z=0;*/
		//std::cout << "Couleur!!";
	    }else {
		ptrColor->x=0;
		ptrColor->y=0;
		ptrColor->z=0;
		//std::cout << "NOIR!!";
	    }
	    ptrColor->w = 255; // opaque
	    }

    private:

	__device__
	int f(double x, double y, double t,bool isJulia)
	    {
	    /*
		std::complex<double> *z;
		if(isJulia){
		    z = new std::complex<double>(x,y);
		}else{
		    z = new std::complex<double>(0.0,0.0);
		}
		//double z = 0.0;
		std::complex<double> c(x,y);
		int i=0;
		for( i=0;i<t && std::abs(*z)<2;i++){
		    *z=(*z)*(*z)+c;
		}
		delete z;
		z=NULL;
		//*isConverg = i==t;
		return i;*/

		double a=0;
		double b=0;
		if(isJulia){
		    a=x;
		    b=y;
		}
		int k=0;

		while(k<t && (a*a+b*b)<=4){
		    double aCopy = a;
		    a=(a*a-b*b)+x;
		    b=2*aCopy*b+y;
		    //cout<<"Value:"<< (a*a+b*b)<<endl;
		    k++;
		}
		//cout<<"K:"<<k<<endl;
		return k;
	    }
	int j(double x, double y, double cX,double cY,double t)
		    {


			double a=x;
			double b=y;

			int k=0;

			while(k<t && (a*a+b*b)<=4){
			    double aCopy = a;
			    a=(a*a-b*b)+cX;
			    b=2*aCopy*b+cY;
			    //cout<<"Value:"<< (a*a+b*b)<<endl;
			    k++;
			}
			//cout<<"K:"<<k<<endl;
			return k;
		    }

	__device__
	bool isConvergent(int s,int n){
	    return s==n ;
	}

	__device__
	float h_color(int s,int n){
	    return (float)s/(float)n;
	}

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    protected:

	// Inputs
	int n;
	double cX;
	double cY;
	bool isJulia;

	// Tools
	CalibreurF calibreur;

    }
;

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
