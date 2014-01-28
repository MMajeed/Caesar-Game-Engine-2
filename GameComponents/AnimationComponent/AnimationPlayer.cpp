#include "AnimationPlayer.h"
#include "AnimationManager.h"

AnimationPlayer::AnimationPlayer()
{
	this->AnimTime = 0.0;
	this->AnimRate = 0.0;
	this->CurrentFrame = 0;
	this->PreviousFrame = 0;
}

void AnimationPlayer::Play(float delta)
{

}

double AnimationPlayer::GetCurrentPhase(std::shared_ptr<BasicAnimation> animation) const
{
	return (this->AnimTime / animation->Duration);
}
double AnimationPlayer::GetCurrentPhase() const
{
	return this->GetCurrentPhase(this->GetAnimation());
}
void AnimationPlayer::SetCurrentPhase(float phasePercentage)
{
	if(phasePercentage < 0.0f)
	{
		this->AnimTime = 0.0f;
	}
	else if(phasePercentage > 1.0f)
	{
		this->AnimTime = this->GetAnimation()->Duration;
	}
	else
	{
		this->AnimTime = phasePercentage * this->GetAnimation()->Duration;
	}
}

std::shared_ptr<AnimationPlayer> AnimationPlayer::Spawn(std::string basicAnimationID,
														float startPhase,
														float animRate)
{
	std::shared_ptr<AnimationPlayer> newObject(new AnimationPlayer());

	newObject->AnimRate = animRate;
	newObject->SetCurrentPhase(startPhase);
	newObject->AnimationID = basicAnimationID;

	return newObject;
}

const std::shared_ptr<BasicAnimation> AnimationPlayer::GetAnimation() const
{
	AnimationManager& animationManager = AnimationManager::GetInstance();

	std::shared_ptr<BasicAnimation> returnValue;

	auto iter = animationManager.AnimationsContainer.find(this->AnimationID);
	if(iter != animationManager.AnimationsContainer.end())
	{
		returnValue = iter->second;
	}

	return returnValue;
}

const std::hash_map<std::string, CML::Matrix4x4> AnimationPlayer::JointsAnimatedTransformation() const
{
	return this->jointsAnimated;
}