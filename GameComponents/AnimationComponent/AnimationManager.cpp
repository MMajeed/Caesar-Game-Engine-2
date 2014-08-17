#include "AnimationManager.h"
#include <Windows.h>

AnimationManager::AnimationManager()
{

}

void AnimationManager::Init()
{

}
void AnimationManager::Work(double realTime, double deltaTime)
{
	for(auto iter = this->AnimationControllerContainer.begin();
		iter != this->AnimationControllerContainer.end();
		++iter)
	{
		iter->second->Play(deltaTime);
	}
}
void AnimationManager::Shutdown()
{

}


void AnimationManager::InsertAnimation(const std::string& ID, std::shared_ptr<BasicAnimation> obj)
{
	this->AnimationsContainer[ID] = obj;
}
void AnimationManager::RemoveAnimation(const std::string& ID)
{
	auto iter = this->AnimationsContainer.find(ID);
	if(iter != this->AnimationsContainer.end())
	{
		this->AnimationsContainer.erase(iter);
	}
}
const std::unordered_map<std::string, std::shared_ptr<BasicAnimation>>& AnimationManager::AllAnimation()
{
	return this->AnimationsContainer;
}


void AnimationManager::InsertAnimationController(const std::string& ID, std::shared_ptr<AnimationController> obj)
{
	this->AnimationControllerContainer[ID] = obj;
}
void AnimationManager::RemoveAnimationController(const std::string& ID)
{
	auto iter = this->AnimationControllerContainer.find(ID);
	if(iter != this->AnimationControllerContainer.end())
	{
		this->AnimationControllerContainer.erase(iter);
	}
}
const std::unordered_map<std::string, std::shared_ptr<AnimationController>>& AnimationManager::AllAnimationController()
{
	return this->AnimationControllerContainer;
}