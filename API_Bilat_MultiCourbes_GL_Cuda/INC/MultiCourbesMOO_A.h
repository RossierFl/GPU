#ifndef MULTICOURBEMOOA_H_
#define MULTICOURBEMOOA_H_

#include "envBilatMultiCourbes.h"
#include "MultiCourbeOptions.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_MULTI_COURBES MultiCourbesMOO_A
    {
    public:

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

	MultiCourbesMOO_A(int n,int m,MultiCourbeOptions multiCourbeOption);

	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/

	virtual ~MultiCourbesMOO_A();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

	/**
	 * n nbCourbes
	 * m nbPoints par courbe
	 *
	 * ptrDevData matrice nxm des multicourbes row-major lineariser.
	 */
	virtual void fillData(float* ptrDevData, size_t sizeOctet, int n, int m)=0;

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/

	int getN() const;

	int getM() const;

	MultiCourbeOptions getMultiCourbeOption() const;

	/*--------------------------------------*\
	 |*		Set			*|
	 \*-------------------------------------*/

	void setMultiCourbeOption(MultiCourbeOptions multiCourbeOption);

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	int n;
	int m;
	MultiCourbeOptions multiCourbeOption;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
