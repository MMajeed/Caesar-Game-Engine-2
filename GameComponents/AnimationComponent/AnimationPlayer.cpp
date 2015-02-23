#include "AnimationPlayer.h"
#include "AnimationManager.h"
#include <MathFunctions.h>
#include <iostream>
#include "Resource.h"

AnimationPlayer::AnimationPlayer()
{
	this->AnimTime = 0.0;
}

void AnimationPlayer::Play(double delta)
{
	std::shared_ptr<BasicAnimation> spAnimation = this->Animation.lock();
	if(!spAnimation){ return; }

	double difference = delta  ;
	double oldAnimTime = this->AnimTime;
	double newAnimTime = oldAnimTime + difference;

	if(newAnimTime > spAnimation->Duration){ newAnimTime = 0.0f; } // Go to the start
	else if(newAnimTime < 0.0f){newAnimTime = spAnimation->Duration;} // Go to the end
	this->AnimTime = newAnimTime; // Update the time

	for(auto iter = spAnimation->AllNodes.begin();
		iter != spAnimation->AllNodes.end();
		++iter)
	{
		CML::Vec3 translation = this->CaluclateTranslationJoint(iter->second);
		this->CurrentTranslationJoint[iter->first] = translation;

		CML::Vec4 rotation = this->CaluclateRotationJoint(iter->second);
		this->CurrentRotationJoint[iter->first] = rotation;

		CML::Vec3 scale = this->CaluclateScaleJoint(iter->second);
		this->CurrentScaleJoint[iter->first] = scale;
	}
}

CML::Vec3 AnimationPlayer::CaluclateTranslationJoint(const BasicAnimation::Joint& ACNode)
{
	CML::Vec3 returnValue;
	if(ACNode.Translation.size() > 1)
	{
		std::size_t prevFrame = this->LastTranslationFrame[ACNode.Name];
		std::size_t currentFrame = this->CurrentTranslationFrame[ACNode.Name];
		std::size_t nextFrame = prevFrame;
		if(this->AnimTime > ACNode.Translation[nextFrame].Time)
		{
			do
			{
				nextFrame += 1;
			} while(this->AnimTime > ACNode.Translation[nextFrame].Time);
		}
		else if(this->AnimTime < ACNode.Translation[nextFrame].Time)
		{
			do
			{
				nextFrame -= 1;
			} while(this->AnimTime < ACNode.Translation[nextFrame].Time);
		}

		if(std::abs((int)nextFrame - (int)prevFrame) > 1)
		{
			prevFrame = currentFrame;
		}

		this->LastTranslationFrame[ACNode.Name] = prevFrame;
		this->CurrentTranslationFrame[ACNode.Name] = nextFrame;

		if(prevFrame != nextFrame)
		{
			const BasicAnimation::Joint::Key& oldFrame = ACNode.Translation[prevFrame];
			const BasicAnimation::Joint::Key& newFrame = ACNode.Translation[nextFrame];
			double ratio = std::abs(this->AnimTime - oldFrame.Time) / std::abs(newFrame.Time - oldFrame.Time);

			returnValue = CML::Lerp(oldFrame.Value, newFrame.Value, ratio);
		}
		else
		{
			return ACNode.Translation[nextFrame].Value;
		}
	}
	else if(ACNode.Translation.size() == 1)
	{
		returnValue = ACNode.Translation.front().Value;
	}
	else
	{
		returnValue = {0.0, 0.0, 0.0};
	}
	return returnValue;
}
CML::Vec4 AnimationPlayer::CaluclateRotationJoint(const BasicAnimation::Joint& ACNode)
{
	CML::Vec4 returnValue;
	if(ACNode.Rotation.size() > 1)
	{
		std::size_t prevFrame = this->LastRotationFrame[ACNode.Name];
		std::size_t currentFrame = this->CurrentRotationFrame[ACNode.Name];
		std::size_t nextFrame = prevFrame;
		if(this->AnimTime > ACNode.Rotation[nextFrame].Time)
		{
			do
			{
				nextFrame += 1;
			} while(this->AnimTime > ACNode.Rotation[nextFrame].Time);
		}
		else if(this->AnimTime < ACNode.Rotation[nextFrame].Time)
		{
			do
			{
				nextFrame -= 1;
			} while(this->AnimTime < ACNode.Rotation[nextFrame].Time);
		}

		if(std::abs((int)nextFrame - (int)prevFrame) > 1)
		{
			prevFrame = currentFrame;
		}

		this->LastRotationFrame[ACNode.Name] = prevFrame;
		this->CurrentRotationFrame[ACNode.Name] = nextFrame;

		if(prevFrame != nextFrame)
		{
			const BasicAnimation::Joint::QuaKey& oldFrame = ACNode.Rotation[prevFrame];
			const BasicAnimation::Joint::QuaKey& newFrame = ACNode.Rotation[nextFrame];
			double ratio = std::abs(this->AnimTime - oldFrame.Time) / std::abs(newFrame.Time - oldFrame.Time);

			returnValue = CML::Slerp(oldFrame.Value, newFrame.Value, ratio);

			int breakpoint = 0;
		}
		else
		{
			return ACNode.Rotation[nextFrame].Value;
		}
	}
	else if(ACNode.Rotation.size() == 1)
	{
		returnValue = ACNode.Rotation.front().Value;
	}
	else
	{
		returnValue = {0.0, 0.0, 0.0, 0.0};
	}
	return returnValue;
}
CML::Vec3 AnimationPlayer::CaluclateScaleJoint(const BasicAnimation::Joint& ACNode)
{
	CML::Vec3 returnValue;
	if(ACNode.Scale.size() > 1)
	{
		std::size_t prevFrame = this->LastScaleFrame[ACNode.Name];
		std::size_t currentFrame = this->CurrentScaleFrame[ACNode.Name];
		std::size_t nextFrame = prevFrame;
		if(this->AnimTime > ACNode.Scale[nextFrame].Time)
		{
			do
			{
				nextFrame += 1;
			} while(this->AnimTime > ACNode.Scale[nextFrame].Time);
		}
		else if(this->AnimTime < ACNode.Scale[nextFrame].Time)
		{
			do
			{
				nextFrame -= 1;
			} while(this->AnimTime < ACNode.Scale[nextFrame].Time);
		}

		if(std::abs((int)nextFrame - (int)prevFrame) > 1)
		{
			prevFrame = currentFrame;
		}

		this->LastScaleFrame[ACNode.Name] = prevFrame;
		this->CurrentScaleFrame[ACNode.Name] = nextFrame;

		if(prevFrame != nextFrame)
		{
			const BasicAnimation::Joint::Key& oldFrame = ACNode.Scale[prevFrame];
			const BasicAnimation::Joint::Key& newFrame = ACNode.Scale[nextFrame];
			double ratio = std::abs(this->AnimTime - oldFrame.Time) / std::abs(newFrame.Time - oldFrame.Time);

			returnValue = CML::Lerp(oldFrame.Value, newFrame.Value, ratio);
		}
		else
		{
			return ACNode.Scale[nextFrame].Value;
		}
	}
	else if(ACNode.Scale.size() == 1)
	{
		returnValue = ACNode.Scale.front().Value;
	}
	else
	{
		returnValue = {1.0, 1.0, 1.0};
	}
	return returnValue;
}

std::shared_ptr<AnimationPlayer> AnimationPlayer::Spawn(std::string basicAnimationID, double startPhase)
{
	AnimationManager& animationManager = AnimationManager::GetInstance();

	std::shared_ptr<AnimationPlayer> newObject(new AnimationPlayer());

	auto iter = Resource::AnimationsList.find(basicAnimationID);
	if(iter != Resource::AnimationsList.end())
	{
		newObject->Animation = iter->second;
	}

	newObject->SetCurrentPhase(startPhase);

	return newObject;
}

double AnimationPlayer::GetCurrentPhase(std::shared_ptr<BasicAnimation> animation) const
{
	return (this->AnimTime / animation->Duration);
}
double AnimationPlayer::GetCurrentPhase() const
{
	double returnValue = 0.0;
	if(this->Animation.lock())
	{
		returnValue = this->GetCurrentPhase(this->Animation.lock());
	}
	return returnValue;
}
void AnimationPlayer::SetCurrentPhase(double phasePercentage)
{
	if(this->Animation.lock())
	{
		if(phasePercentage < 0.0)
		{
			this->AnimTime = 0.0f;
		}
		else if(phasePercentage > 1.0)
		{
			this->AnimTime = this->Animation.lock()->Duration;
		}
		else
		{
			this->AnimTime = phasePercentage * this->Animation.lock()->Duration;
		}
	}
}