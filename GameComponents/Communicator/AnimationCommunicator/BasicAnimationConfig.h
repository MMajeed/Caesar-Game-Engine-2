#ifndef __AnimationConfig__
#define __AnimationConfig__

#include "Linker.h"
#include <Animation.h>
#include <memory>
#include <string>

namespace BasicAnimationConfig
{
	std::string Create(std::shared_ptr<CHL::Animation> animation);
	void Release(std::string ID);
}

#endif //__AnimationConfig__