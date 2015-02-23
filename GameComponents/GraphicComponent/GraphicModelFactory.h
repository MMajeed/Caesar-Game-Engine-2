#ifndef __GraphicModelFactory__
#define __GraphicModelFactory__

#include "Linker.h"
#include <iGraphicModelFactory.h>

class GraphicComponentDLL_API GraphicModelFactory : public iGraphicModelFactory
{
public:
	virtual std::string Create(std::shared_ptr<CHL::Model> model);
	virtual void Release(std::string ID);
};

#endif //__GraphicModelFactory__