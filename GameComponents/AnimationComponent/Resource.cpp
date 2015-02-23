#include "Resource.h"

namespace Resource
{
	AnimationComponentDLL_API std::unordered_map<std::string, std::shared_ptr<BasicAnimation>> AnimationsList;
	AnimationComponentDLL_API std::unordered_map<std::string, std::shared_ptr<AnimationController>> AnimationControllerList;
};
