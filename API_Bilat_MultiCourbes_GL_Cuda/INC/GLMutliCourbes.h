#ifndef GL_MUTLI_COURBES_H_
#define GL_MUTLI_COURBES_H_

#include "envBilatMultiCourbes.h"
#include "MultiCourbeOptions.h"
#include "MultiCourbesMOO_A.h"
#include "Displayable_A.h"
#include "bilat_GL.h"
#include "VertexBufferObject.h"
#include "ShaderLoaders.h"
#include <atomic>
//#include <boost/atomic.hpp>

#include "cuda.h"
#include "cuda_gl_interop.h" //link between GL and Cuda

using std::atomic;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**

 *
 */

/**
 * Inputs :
 *
 * 	n nb Courbes
 * 	m nbPoints par courbes
 *
 * 	shaderPath la racine contenant les shader suivants :
 *
 * 		lib/ColorieurCarteHSB.glsl
 * 		lib/ColorieurHSB.glsl
 * 		multiCourbeHSBFragmentShader.glsl
 * 		multiCourbeHSBFragmentShader.glsl
 */
class CBI_MULTI_COURBES GLMutliCourbes: public Displayable_A
    {
	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

    public:

	/**
	 * Inputs :
	 *
	 * 	shaderPath la racine contenant les shader suivants :
	 *
	 * 		lib/ColorieurCarteHSB.glsl
	 * 		lib/ColorieurHSB.glsl
	 * 		multiCourbeHSBFragmentShader.glsl
	 * 		multiCourbeHSBFragmentShader.glsl
	 *
	 *  Algorithme coloration:
	 *
	 * 	(A1) les courbes sont colorier en HSB, en fonction de y
	 * 	(A2) Si y est a l'interieur du sueil [sMin.sMax], la couleur utilisee sera la couleur "anatomique"
	 * 	(A3) minMax permet de calibrer le hue, ie de definier a quelle intensite y associer le hueMin et le hueMax
	 *
	 *  Options:
	 *
	 * 	intervalHue01
	 *
	 * 		Permet de sp�cifier [hMin,hMax]
	 *
	 * 	seuil
	 *
	 * 		Permet de sp�cifier [sMin,sMax] (cf ci-dessus)
	 *
	 * 	colorAnatomique
	 *
	 * 		Couleur RGBA qui sera afficher si y se trouve � l'interieur du seuil.
	 *
	 * 	minMax
	 *
	 * 		Permet de specifier [vMin,vMax], de telle sorte que vMin soit colorier avec hMin, et vMax avec hMax
	 * 		Il s'agit d'une calibration.
	 */
	GLMutliCourbes(MultiCourbesMOO_A* ptrMultiCourbeMOO, string shaderPath);

	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/

    public:

	virtual ~GLMutliCourbes();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/**
	 * Override
	 */
	virtual void init(Panel_A &panel);

	/**
	 * Override
	 */
	virtual void reshape(Panel_A &panel, int w, int h);

	/**
	 * Override
	 */
	virtual void display(Panel_A &panel);

	/**
	 * Override
	 */
	virtual void release(Panel_A &panel);

	/**
	 * On next repaint, fillVBOValues will be called.
	 */
	void update();

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/

	MultiCourbesMOO_A* getMultiCoursbeMOO() const;

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*--------------------------------------*/

    private:

	void loadShader();
	void createVBOs();
	void initInterop();
	void drawMultiCourbes(Panel_A &panel);
	void updateGL(Panel_A &panel);

    private:

	// Inputs
	MultiCourbesMOO_A* ptrMultiCourbeMOO;
	string shaderPath;

	// OpenGL
	VertexBufferObject* ptrVBOVertices;
	VertexBufferObject* ptrVBOValues;
	ShaderPrograms* ptrShaderProgram;

	//Cuda GL Interop
	cudaGraphicsResource* cudaRessource;
	cudaStream_t streamToSynchronize;

	// Tools
	std::atomic<bool> isNeedUpdate;
	bool isInit;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
