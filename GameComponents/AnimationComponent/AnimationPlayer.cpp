#include "AnimationPlayer.h"
#include "AnimationManager.h"
#include <MathFunctions.h>
#include <iostream>

AnimationPlayer::AnimationPlayer()
{
	this->AnimTime = 0.0;
	this->AnimRate = 0.0;
}

void AnimationPlayer::Play(double delta)
{
	std::shared_ptr<BasicAnimation> spAnimation = this->Animation.lock();

	if(spAnimation)
	{
		double difference = delta  ;
		double oldAnimTime = this->AnimTime;
		double newAnimTime = oldAnimTime + (difference * this->AnimRate);
		if(newAnimTime == oldAnimTime){ return; } // They are the same, so skip

		if(newAnimTime > spAnimation->Duration){ newAnimTime = 0.0f; } // Go to the start
		else if(newAnimTime < 0.0f){newAnimTime = spAnimation->Duration;} // Go to the end
		this->AnimTime = newAnimTime; // Update the time

		this->PlayRecursively(spAnimation->RootNode, spAnimation->RootNode->Transformation);
	}
}

void AnimationPlayer::PlayRecursively(std::shared_ptr<BasicAnimation::Node> BANode, const CML::Matrix4x4& parentsJoint)
{
	CML::Vec3 translation = this->CaluclateTranslationJoint(BANode);
	CML::Vec4 rotation = this->CaluclateRotationJoint(BANode);
	CML::Vec3 scale = this->CaluclateScaleJoint(BANode);

	CML::Matrix4x4 tranformation = CML::TransformMatrix(translation, rotation, scale);
	CML::Matrix4x4 finalTranslation = CML::Multiple(parentsJoint, tranformation);

	this->SetJoint(BANode->Name, finalTranslation);

	for(auto iter = BANode->Childern.begin();
		iter != BANode->Childern.end();
		++iter)
	{
		this->PlayRecursively(*iter, finalTranslation);
	}
}
CML::Vec3 AnimationPlayer::CaluclateTranslationJoint(std::shared_ptr<BasicAnimation::Node> BANode)
{
	CML::Vec3 returnValue;
	if(BANode->Translation.size() > 1)
	{
		std::size_t prevFrame = this->LastTranslationFrame[BANode->Name];
		std::size_t currentFrame = this->CurrentTranslationFrame[BANode->Name];
		std::size_t nextFrame = prevFrame;
		if(this->AnimTime > BANode->Translation[nextFrame].Time)
		{
			do
			{
				nextFrame += 1;
			} while(this->AnimTime > BANode->Translation[nextFrame].Time);
		}
		else if(this->AnimTime < BANode->Translation[nextFrame].Time)
		{
			do
			{
				nextFrame -= 1;
			} while(this->AnimTime < BANode->Translation[nextFrame].Time);
		}

		if(std::abs((int)nextFrame - (int)prevFrame) > 1)
		{
			prevFrame = currentFrame;
		}

		this->LastTranslationFrame[BANode->Name] = prevFrame;
		this->CurrentTranslationFrame[BANode->Name] = nextFrame;

		if(prevFrame != nextFrame)
		{
			const BasicAnimation::Node::Key& oldFrame = BANode->Translation[prevFrame];
			const BasicAnimation::Node::Key& newFrame = BANode->Translation[nextFrame];
			double ratio = std::abs(this->AnimTime - oldFrame.Time) / std::abs(newFrame.Time - oldFrame.Time);

			returnValue = CML::Lerp(oldFrame.Value, newFrame.Value, ratio);
		}
		else
		{
			return BANode->Translation[nextFrame].Value;
		}
	}
	else if(BANode->Translation.size() == 1)
	{
		returnValue = BANode->Translation.front().Value;
	}
	else
	{
		returnValue = {0.0, 0.0, 0.0};
	}
	return returnValue;
}
CML::Vec4 AnimationPlayer::CaluclateRotationJoint(std::shared_ptr<BasicAnimation::Node> BANode)
{
	CML::Vec4 returnValue;
	if(BANode->Rotation.size() > 1)
	{
		std::size_t prevFrame = this->LastRotationFrame[BANode->Name];
		std::size_t currentFrame = this->CurrentRotationFrame[BANode->Name];
		std::size_t nextFrame = prevFrame;
		if(this->AnimTime > BANode->Rotation[nextFrame].Time)
		{
			do
			{
				nextFrame += 1;
			} while(this->AnimTime > BANode->Rotation[nextFrame].Time);
		}
		else if(this->AnimTime < BANode->Rotation[nextFrame].Time)
		{
			do
			{
				nextFrame -= 1;
			} while(this->AnimTime < BANode->Rotation[nextFrame].Time);
		}

		if(std::abs((int)nextFrame - (int)prevFrame) > 1)
		{
			prevFrame = currentFrame;
		}

		this->LastRotationFrame[BANode->Name] = prevFrame;
		this->CurrentRotationFrame[BANode->Name] = nextFrame;

		if(prevFrame != nextFrame)
		{
			const BasicAnimation::Node::QuaKey& oldFrame = BANode->Rotation[prevFrame];
			const BasicAnimation::Node::QuaKey& newFrame = BANode->Rotation[nextFrame];
			double ratio = std::abs(this->AnimTime - oldFrame.Time) / std::abs(newFrame.Time - oldFrame.Time);

			returnValue = CML::Slerp(oldFrame.Value, newFrame.Value, ratio);

			int breakpoint = 0;
		}
		else
		{
			return BANode->Rotation[nextFrame].Value;
		}
	}
	else if(BANode->Rotation.size() == 1)
	{
		returnValue = BANode->Rotation.front().Value;
	}
	else
	{
		returnValue = {0.0, 0.0, 0.0, 0.0};
	}
	return returnValue;
}
CML::Vec3 AnimationPlayer::CaluclateScaleJoint(std::shared_ptr<BasicAnimation::Node> BANode)
{
	CML::Vec3 returnValue;
	if(BANode->Scale.size() > 1)
	{
		std::size_t prevFrame = this->LastScaleFrame[BANode->Name];
		std::size_t currentFrame = this->CurrentScaleFrame[BANode->Name];
		std::size_t nextFrame = prevFrame;
		if(this->AnimTime > BANode->Scale[nextFrame].Time)
		{
			do
			{
				nextFrame += 1;
			} while(this->AnimTime > BANode->Scale[nextFrame].Time);
		}
		else if(this->AnimTime < BANode->Scale[nextFrame].Time)
		{
			do
			{
				nextFrame -= 1;
			} while(this->AnimTime < BANode->Scale[nextFrame].Time);
		}

		if(std::abs((int)nextFrame - (int)prevFrame) > 1)
		{
			prevFrame = currentFrame;
		}

		this->LastScaleFrame[BANode->Name] = prevFrame;
		this->CurrentScaleFrame[BANode->Name] = nextFrame;

		if(prevFrame != nextFrame)
		{
			const BasicAnimation::Node::Key& oldFrame = BANode->Scale[prevFrame];
			const BasicAnimation::Node::Key& newFrame = BANode->Scale[nextFrame];
			double ratio = std::abs(this->AnimTime - oldFrame.Time) / std::abs(newFrame.Time - oldFrame.Time);

			returnValue = CML::Lerp(oldFrame.Value, newFrame.Value, ratio);
		}
		else
		{
			return BANode->Scale[nextFrame].Value;
		}
	}
	else if(BANode->Scale.size() == 1)
	{
		returnValue = BANode->Scale.front().Value;
	}
	else
	{
		returnValue = {1.0, 1.0, 1.0};
	}
	return returnValue;
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

std::shared_ptr<AnimationPlayer> AnimationPlayer::Spawn(std::string basicAnimationID,
														double startPhase,
														double animRate)
{
	AnimationManager& animationManager = AnimationManager::GetInstance();

	std::shared_ptr<AnimationPlayer> newObject(new AnimationPlayer());

	newObject->AnimRate = animRate;
	newObject->SetCurrentPhase(startPhase);
	auto iter = animationManager.AnimationsContainer.find(basicAnimationID);
	if(iter != animationManager.AnimationsContainer.end())
	{
		newObject->Animation = iter->second;
	}

	return newObject;
}

CML::Matrix4x4 AnimationPlayer::GetSingleJoint(std::string jointName)
{
	CML::Matrix4x4 returnValue = CML::MatrixIdentity();
	AnimationManager& animationManager = AnimationManager::GetInstance();

	auto iter = this->jointsAnimated.find(jointName);
	if(iter != this->jointsAnimated.end())
	{
		returnValue = iter->second;
	}
	return returnValue;
}
void AnimationPlayer::SetJoint(std::string name, const CML::Matrix4x4& mat)
{
	AnimationManager& animationManager = AnimationManager::GetInstance();

	std::lock_guard<std::mutex> lock(animationManager.mutex);

	this->jointsAnimated[name] = mat;
}
const std::hash_map<std::string, CML::Matrix4x4>& AnimationPlayer::JointsAnimatedTransformation() const
{
	return this->jointsAnimated;
}