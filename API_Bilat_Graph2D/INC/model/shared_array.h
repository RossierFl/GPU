#ifndef SHAREDARRAY_H_
#define SHAREDARRAY_H_

// C++11
#include <memory>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

template<class T>
class shared_array: public std::shared_ptr<T>
    {
    public:
	shared_array(T* pointer) :
		std::shared_ptr<T>(pointer, std::default_delete<T[]>())
	    {

	    }

	T& operator[](int i)
	    {
	    return this->get()[i];
	    }

	T& operator[](int i) const
	    {
	    return this->get()[i];
	    }
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
