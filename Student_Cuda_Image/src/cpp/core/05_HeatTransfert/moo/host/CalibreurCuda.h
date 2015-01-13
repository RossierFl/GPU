#ifndef CALIBREURCUDA_H_
#define CALIBREURCUDA_H_

class CalibreurCuda
    {
    public:
	CalibreurCuda(float x1, float x2, float y1, float y2)
	{
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
	pente = (y2 - y1) / (x2 - x1);
	t = y1 - pente * x1;
	}

	CalibreurCuda(const CalibreurCuda& source)
	    {
	    x1 = source.x1;
	    x2 = source.x2;
	    y1 = source.y1;
	    y2 = source.y2;
	    pente = source.pente;
	    t = source.t;
	    }

	virtual ~CalibreurCuda()
	    {

	    }

	__device__
	float calibrer(float x) const
	    {
	    return (pente * x) + t;
	    }

    private:

	float x1;
	float x2;

	float y1;
	float y2;

	float pente;
	float t;
    };


#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
