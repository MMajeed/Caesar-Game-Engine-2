#ifndef __AnimationConfig__
#define __AnimationConfig__

#include "Linker.h"
#include <Animation.h>
#include <Node.h>
#include <memory>
#include <string>

namespace BasicAnimationConfig
{
	std::string Create(std::shared_ptr<CHL::Animation> animation, std::shared_ptr<CHL::Node> rootNode);
	void Release(std::string ID);
}

#endif //__AnimationConfig__