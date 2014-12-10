#ifndef ProduitScalaireHOST_H_
#define ProduitScalaireHOST_H_

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class ProduitScalaireHost
    {
    public:
	ProduitScalaireHost();
	virtual ~ProduitScalaireHost();
	static void MyCalculateProduitScalaire();
	static double ResultatTheorique(long n);
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
