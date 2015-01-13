#ifndef HEATTRANSFERTPROVIDER_H_
#define HEATTRANSFERTPROVIDER_H_

#include "HeatTransfert.h"
#include "Image.h"

class HeatTransfertProvider {

	public:
		static HeatTransfert* create(void);
		static Image* createGL(void);
};

#endif
