#include "AnimationFactorySetup.h"

#include "AnimationControllerFactory.h"
#include "BasicAnimationFactory.h"
#include "AnimationManager.h"

namespace AnimationFactorySetup
{
	AnimationFactory::AnimationItem Load()
	{
		AnimationFactory::AnimationItem returnValue;

		returnValue._AnimationControllerFactory = std::shared_ptr<AnimationControllerFactory>(new AnimationControllerFactory);
		returnValue._BasicAnimationFactory = std::shared_ptr<BasicAnimationFactory>(new BasicAnimationFactory);
		returnValue._AnimationInterface = AnimationManager::GetPointer();

		return returnValue;
	}
};