#include "AnimationController.h"
#include "AnimationManager.h"

AnimationController::AnimationController()
{

}

void AnimationController::Play(double delta)
{
	this->Animation.lock()->Play(delta);
}

std::shared_ptr<AnimationController> AnimationController::Spawn(std::string animtionPlayerID)
{
	AnimationManager& animationManager = AnimationManager::GetInstance();

	std::shared_ptr<AnimationController> newObject(new AnimationController());

	auto iter = animationManager.AnimationsPlayerContainer.find(animtionPlayerID);
	if(iter != animationManager.AnimationsPlayerContainer.end())
	{
		newObject->Animation = iter->second;
	}

	return newObject;
}

CML::Matrix4x4 AnimationController::GetSingleJoint(std::string jointName)
{
	return this->Animation.lock()->GetSingleJoint(jointName);
}

const std::hash_map<std::string, CML::Matrix4x4>& AnimationController::JointsAnimatedTransformation() const
{
	return this->Animation.lock()->JointsAnimatedTransformation();
}