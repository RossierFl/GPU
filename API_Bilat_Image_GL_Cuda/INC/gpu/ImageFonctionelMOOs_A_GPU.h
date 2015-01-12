#ifndef IMAGE_FONCTIONEL_MOOS_A_GPU_H
#define IMAGE_FONCTIONEL_MOOS_A_GPU_H

#include "ImageMOOs_A_GPU.h"
#include "DomaineMath_GPU.h"

#include <stack>
using std::stack;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace gpu
    {

    class CBI_GLIMAGE_CUDA ImageFonctionelMOOs_A: public ImageMOOs_A
	{

	    /*--------------------------------------*\
	     |*		Constructor		    *|
	     \*-------------------------------------*/

	    public:

	    ImageFonctionelMOOs_A(unsigned int w, unsigned int h, gpu::DomaineMath domaineMath);

	    virtual ~ImageFonctionelMOOs_A();

	    /*--------------------------------------*\
	     |*		Methodes		    *|
	     \*-------------------------------------*/

	public:
	    /**
	     * fillImageGL avec le domaine courant
	     * w et h fixe, ne change pas au cours du temps !
	     */
	    virtual void fillImageGL(uchar4* ptrDevImageGL, int w, int h, const gpu::DomaineMath& domaineNew)=0; //ptrDevImageGL zone memoire commune OpenGL et Cuda

	    /**
	     * Call each time the domaine change
	     * 	1) Domaines : new domaine of the image
	     */
	    virtual void onDomaineChangePerformed(const gpu::DomaineMath& domaineNew);

	    /**
	     * Override
	     */
	    virtual void paintPrimitivesAPI(Graphic2Ds& ptrGraphic2D);

	    /**
	     * Last Domaine push in History
	     */
	    void restoreFromDomaineHistory();

	    /**
	     * First Domaine of History
	     */
	    void headOfDomaineHistory();

	    /**
	     * Override
	     */
	    virtual void print(ostream& stream) const;

	private:

	    /**
	     * Override
	     * call fillImageGL with current domaine
	     */
	    virtual void fillImageGL(uchar4* ptrDevImageGL, int w, int h);

	    /*--------------------------------------*\
	     |*		Get			    *|
	     \*-------------------------------------*/

	public:

	    /**
	     * Domaine currently used
	     */
	    gpu::DomaineMath getCurrentDomaine() const;

	    /*--------------------------------------*\
	     |*		Set			    *|
	     \*-------------------------------------*/

	public:

	    void setCurrentDomaine(gpu::DomaineMath domaineNew);

	    void setEnableDomaineOverlay(bool isEnable);

	    /*--------------------------------------*\
	     |*		Is			    *|
	     \*-------------------------------------*/

	public:

	    inline bool isEnableDomaineOverlay()
		{
		return enableDomaineOverlay;
		}

	    /*--------------------------------------*\
	     |*		Attributs		*|
	     \*-------------------------------------*/

	private:

	    //Input
	    gpu::DomaineMath homeDomaine;

	    //Tools
	    stack<gpu::DomaineMath> stackHistoryDomaine;
	    bool enableDomaineOverlay;

	};
    }

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
