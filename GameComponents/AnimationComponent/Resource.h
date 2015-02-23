#ifndef __Resource__
#define __Resource__

#include "Linker.h"

#include <string>
#include <unordered_map>

#include "BasicAnimation.h"
#include "AnimationPlayer.h"
#include "AnimationController.h"

namespace Resource
{
	extern AnimationComponentDLL_API std::unordered_map<std::string, std::shared_ptr<BasicAnimation>> AnimationsList;
	extern AnimationComponentDLL_API std::unordered_map<std::string, std::shared_ptr<AnimationController>> AnimationControllerList;
};

#endif //__Resource__