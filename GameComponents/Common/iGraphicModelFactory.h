#ifndef __iGraphicModelFactory__
#define __iGraphicModelFactory__

#include "Linker.h"
#include <Model.h>
#include <memory>
#include <string>

class CommonDLL_API iGraphicModelFactory
{
public:
	virtual std::string Create(std::shared_ptr<CHL::Model> model) = 0;
	virtual void Release(std::string ID) = 0;
};

#endif //__iGraphicModelFactory__