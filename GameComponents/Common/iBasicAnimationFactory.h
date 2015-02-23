#ifndef __iBasicAnimationFactory__
#define __iBasicAnimationFactory__

#include "Linker.h"
#include <Animation.h>
#include <Matrix.h>
#include <memory>
#include <string>
#include <Node.h>

class CommonDLL_API iBasicAnimationFactory
{
public:
	virtual std::string Create(std::shared_ptr<CHL::Animation> animation) = 0;
	virtual void Release(std::string ID) = 0;
};

#endif //__iBasicAnimationFactory__