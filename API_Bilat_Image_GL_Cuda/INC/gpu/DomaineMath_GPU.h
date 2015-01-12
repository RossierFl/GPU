#ifndef DOMAINE_MATH_GPU_H
#define DOMAINE_MATH_GPU_H

#include "envGLImageCudas.h"
#include "cuda.h"
#include "DomaineEcran_GPU.h"
#include <string>

using std::string;
using std::ostream;

#define GPU_SCOPE __host__ __device__

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace gpu
    {
    /**
     * (x0,y0) upper left corner of a dx x dy square.
     * x[x0,x1] y[y0,y1]
     */
    class CBI_GLIMAGE_CUDA DomaineMath
	{
	    /*--------------------------------------*\
	     |*		Constructor		    *|
	     \*-------------------------------------*/

	public:

	    __host__
	    __device__ DomaineMath() :
		    x0(0.0), y0(0.0), x1(0.0), y1(0.0), dxDw(0.0), dyDh(0.0)
		{
		// rien
		}

	    __host__
	    __device__ DomaineMath(double x0, double y0, double x1, double y1) :
		    x0(x0), y0(y0), x1(x1), y1(y1), dxDw(0.0), dyDh(0.0)
		{
		// rien
		}

	    /*--------------------------------------*\
	     |*		Methodes		     *|
	     \*--------------------------------------*/

	    /*------------------------------*\
	     |*		CPU		    *|
	     \*-----------------------------*/

	public:

	    __host__
	    string toString() const;



	private:

	    /**
	     * called only by ImageFonctionelMOOs_A, so Host Only!
	     */
	    __host__
	    void computeDxDy(int w, int h);

	    /*------------------------------*\
	     |*		GPU/CPU		    *|
	     \*-----------------------------*/

	public:

	    __host__ __device__
	    gpu::DomaineMath extractDomaineFromSelection(const gpu::DomaineEcran &domaineSelection, int dxEcran, int dyEcran) const
		{
		double zoomX = dxEcran / (double) domaineSelection.dx;
		double zoomY = dyEcran / (double) domaineSelection.dy;

		double dxResult = dx() / zoomX;
		double dyResult = dy() / zoomY;

		double pourcentageX = domaineSelection.x0 / (double) dxEcran;
		double pourcentageY = domaineSelection.y0 / (double) dyEcran;

		return DomaineMath::create(x0 + (pourcentageX * dx()), y0 + (pourcentageY * dy()), dxResult, dyResult);
		}

	    __host__ __device__
	    double dx() const
		{
		return x1 - x0;
		}

	    __host__ __device__
	    double dy() const
		{
		return y1 - y0;
		}

	    /**
	     * toXY est uniquement utilisable lorsque le domaine a été associé a une ImageFonctionelle!
	     */

	    __host__ __device__
	    void toXY(int i, int j, double* ptrX, double* ptrY) const
		{
		*ptrX = x0 + j * dxDw;
		*ptrY = y0 + i * dyDh;
		}

	    __host__ __device__
	    static gpu::DomaineMath create(double x0, double y0, double dx, double dy)
		{
		return DomaineMath(x0, y0, x0 + dx, y0 + dy);
		}

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

    CBI_GLIMAGE_CUDA __host__ ostream& operator<<(ostream& stream, const gpu::DomaineMath& domaine);

    }
#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

