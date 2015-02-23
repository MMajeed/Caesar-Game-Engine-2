#ifndef __BasicAnimationFactory__
#define __BasicAnimationFactory__

#include "Linker.h"
#include <iBasicAnimationFactory.h>

class AnimationComponentDLL_API BasicAnimationFactory : public iBasicAnimationFactory
{
public:
	virtual std::string Create(std::shared_ptr<CHL::Animation> animation);
	virtual void Release(std::string ID);
};

#endif //__BasicAnimationFactory__