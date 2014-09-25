#ifndef IMAGE_FONCTIONEL_MOOS_A_CPU_H
#define IMAGE_FONCTIONEL_MOOS_A_CPU_H

#include "ImageMOOs_A_CPU.h"
#include "DomaineMath_CPU.h"

#include <stack>
using std::stack;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * ImageMOO with a Mathematical Domaine. This domaine can be modified.
 * An history of modification is maintained for undo.
 */
namespace cpu
    {
    class CBI_GLIMAGE ImageFonctionelMOOs_A: public cpu::ImageMOOs_A
	{

	    /*--------------------------------------*\
	    |*		Constructor		    *|
	     \*-------------------------------------*/

	public:

	    ImageFonctionelMOOs_A(unsigned int m, unsigned int n, cpu::DomaineMath domaine);

	    ImageFonctionelMOOs_A(const cpu::ImageFonctionelMOOs_A &imageSource);

	    /*--------------------------------------*\
	     |*		Destructor		    *|
	     \*-------------------------------------*/

	    virtual ~ImageFonctionelMOOs_A();

	    /*--------------------------------------*\
	     |*		Methodes		    *|
	     \*-------------------------------------*/

	public:

	    virtual void fillImageGL(cpu::uchar4* ptrTabPixel, int w, int h, const cpu::DomaineMath& domaineNew)=0;

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

	    /**
	     * Override
	     */
	    virtual void paintPrimitivesAPI(Graphic2Ds& ptrGraphic2D);

	    /**
	     * Override
	     */
	    virtual void fillImageGL(cpu::uchar4* ptrDevImageGL, int w, int h);

	protected:

	    /**
	     * Override
	     * New mathematical domaine for this image.
	     * Previous domaine will be put in history and current domaine is domaineNew
	     */
	    virtual void onDomaineChangePerformed(const cpu::DomaineMath& domaineNew);


	    /*--------------------------------------*\
	    |*		Get			    *|
	     \*-------------------------------------*/

	public:
	    /**
	     * Domaine currently used
	     */
	    cpu::DomaineMath getCurrentDomaine() const;

	    /*--------------------------------------*\
	     |*		Set			    *|
	     \*-------------------------------------*/

	public:

	    void setCurrentDomaine(cpu::DomaineMath domaineNew);

	    void setEnableDomaineOverlay(bool isEnable);

	    /*--------------------------------------*\
	     |*		Is			    *|
	     \*-------------------------------------*/

	public:

	    inline bool isEnableDomaineOverlay()
		{
		return enableDomaineOverlay;
		}

	    /*---------------------------------------*\
	    |*		Attributs  		 *|
	     \*---------------------------------------*/
	private:

	    // Inputs
	    cpu::DomaineMath homeDomaine;

	    // Tools
	    stack<cpu::DomaineMath> stackHistoryDomaine;
	    bool enableDomaineOverlay;
	};
    }

#endif
