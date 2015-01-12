#ifndef MULTICOURBEOPTIONS_H_
#define MULTICOURBEOPTIONS_H_

#include "envBilatMultiCourbes.h"
#include "builtin_types.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*
 * Options:
 *
 * 	intervalHue01
 *
 * 		Permet de spécifier [hMin,hMax]
 *
 * 	seuil
 *
 * 		Permet de spécifier [sMin,sMax] (cf ci-dessus)
 *
 * 	colorNotInSeuil
 *
 * 		Couleur RGBA qui sera afficher si y se trouve à l'interieur du seuil.
 *
 * 	minMaxValue
 *
 * 		Permet de specifier [vMin,vMax], de telle sorte que vMin soit colorier avec hMin, et vMax avec hMax
 * 		Il s'agit d'une calibration.
 *
 */
class CBI_MULTI_COURBES MultiCourbeOptions
    {
	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

    public:

	MultiCourbeOptions(float2 minMaxValue, float2 intervalHue01, float2 seuil, float4 colorNotInSeuil);

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/

    public:

	float2 getMinMaxValue() const;

	float2 getIntervalHue() const;

	float2 getSeuil() const;

	float4 getColorNotInSeuil() const;

	/*--------------------------------------*\
	 |*		Set			*|
	 \*-------------------------------------*/

    public:

	void setMinMaxValue(float2 minMaxValue);

	void setIntervalHue(float2 intervalHue01);

	void setSeuil(float2 seuil);

	void setColorNotInSeuil(float4 colorNotInSeuil);

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/
    private:

	// Input
	float2 minMaxValue;
	float2 intervalHue;
	float2 seuil;
	float4 colorNotInSeuil;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
