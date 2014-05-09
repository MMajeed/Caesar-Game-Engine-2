#ifndef __AnimationConfig__
#define __AnimationConfig__

#include "Linker.h"
#include <Animation.h>
#include <memory>
#include <string>

namespace BasicAnimationConfig
{
	AnimationCommunicatorDLL_API std::string Create(std::shared_ptr<CHL::Animation> animation);
	AnimationCommunicatorDLL_API void Release(std::string ID);
}

#endif //__AnimationConfig__