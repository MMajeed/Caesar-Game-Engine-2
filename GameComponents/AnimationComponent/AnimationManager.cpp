#include "AnimationManager.h"

#include <Components.h>
#include "BasicAnimationFactory.h"
#include "BasicAnimationFactory.h"
#include "AnimationFactorySetup.h"
#include "Resource.h"

AnimationManager::AnimationManager()
{
}
void AnimationManager::Init()
{

}
void AnimationManager::Work(double realTime, double deltaTime)
{
	for(auto iter = Resource::AnimationControllerList.begin();
		iter != Resource::AnimationControllerList.end();
		++iter)
	{
		iter->second->Play(deltaTime);
	}
}
void AnimationManager::Shutdown()
{

}
