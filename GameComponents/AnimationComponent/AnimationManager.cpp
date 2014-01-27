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
const std::hash_map<std::string, std::shared_ptr<BasicAnimation>> AnimationManager::AllAnimation()
{
	return this->AnimationsContainer;
}

void AnimationManager::InsertAnimationPlayer(const std::string& ID, std::shared_ptr<AnimationPlayer> obj)
{
	this->AnimationsPlayerContainer[ID] = obj;
}
void AnimationManager::RemoveAnimationPlayer(const std::string& ID)
{
	auto iter = this->AnimationsPlayerContainer.find(ID);
	if(iter != this->AnimationsPlayerContainer.end())
	{
		this->AnimationsPlayerContainer.erase(iter);
	}
}
const std::hash_map<std::string, std::shared_ptr<AnimationPlayer>> AnimationManager::AllAnimationPlayer()
{
	return this->AnimationsPlayerContainer;
}