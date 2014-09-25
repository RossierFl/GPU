#ifndef DOMAINE_MATH_CPU_H
#define DOMAINE_MATH_CPU_H

#include "envGLImage.h"
#include "DomaineEcran_CPU.h"
#include <string>

using std::string;
using std::ostream;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace cpu
    {
    /**
     * (x0,y0) upper left corner of a dx x dy square.
     * x[x0,x1] y[y0,y1]
     */
    class CBI_GLIMAGE DomaineMath
	{
	    /*--------------------------------------*\
	     |*		Constructor		    *|
	     \*-------------------------------------*/

	public:

	    DomaineMath();

	    DomaineMath(double x0, double y0, double x1, double y1);

	    /*--------------------------------------*\
	     |*		Methodes		     *|
	     \*--------------------------------------*/

	public:

	    cpu::DomaineMath extractDomaineFromSelection(const cpu::DomaineEcran &domaineSelection, int dxFrame, int dyFrame) const;

	    string toString() const;

	    inline double dx() const
		{
		return x1 - x0;
		}

	    inline double dy() const
		{
		return y1 - y0;
		}


	    /**
	     * toXY est uniquement utilisable lorsque le domaine a été associé a une ImageFonctionelle!
	     */
	    void toXY(int i, int j, double* ptrX, double* ptrY) const;

	    static cpu::DomaineMath create(double x0, double y0, double dx, double dy);

	private:

	    void computeDxDy(int w, int h);

	public:


	    /*--------------------------------------*\
	    |*		Attributs		    *|
	     \*-------------------------------------*/

	public:

	    //Input
	    double x0;
	    double y0;
	    double x1;
	    double y1;

	private:

	    // Tools
	    double dxDw; //old dx
	    double dyDh; //old dy

	    friend class ImageFonctionelMOOs_A;
	    // Toutes les méthode de la classe ImageFonctionelMOOs_A sont amie
	};

    CBI_GLIMAGE ostream& operator<<(ostream& stream, const cpu::DomaineMath& domaine);


    }
#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

