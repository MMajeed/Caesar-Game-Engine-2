#include "AnimationPlayer.h"
#include "AnimationManager.h"

AnimationPlayer::AnimationPlayer()
{
	this->AnimTime = 0.0;
	this->AnimRate = 0.0;
	this->LastTranslationFrame = 0;
	this->LastRotationFrame = 0;
	this->LastScaleFrame = 0;
}

void AnimationPlayer::Play(float delta)
{
	std::shared_ptr<BasicAnimation> spAnimation = this->Animation.lock();

	if(spAnimation)
	{
		double oldAnimTime = this->AnimTime;
		double newAnimTime = oldAnimTime +(delta * this->AnimRate);

		if(this->AnimTime == oldAnimTime) // They are the same, so skip
		{
			return;
		}

		if(newAnimTime > spAnimation->Duration)
		{
			newAnimTime = 0.0f;
		}
		else if(newAnimTime < 0.0f)
		{
			newAnimTime = spAnimation->Duration;
		}

		struct PlayRecursively
		{
			static void FindKeys(double oldTime, double newTime, double totalLength,
								 const std::vector<BasicAnimation::Node::Key>& vecKeys,
								 BasicAnimation::Node::Key& outOldFrame,
								 BasicAnimation::Node::Key& outNewFrame
								)
			{
				if(oldTime / totalLength > 0.5) // If we are past the half mark then we start to look from the end
				{
					for(auto iter = vecKeys.rbegin();
						iter != vecKeys.rend();
						++iter)
					{
						if(oldTime > iter->Time)
						{
							outOldFrame = *iter;
							break;
						}
					}
				}
				else // If we are below the half mark then we start to look from the start
				{
					for(auto iter = vecKeys.begin();
						iter != vecKeys.end();
						++iter)
					{
						if(oldTime < iter->Time)
						{
							outOldFrame = *iter;
							break;
						}
					}
				}

				if(newTime / totalLength > 0.5) // If we are past the half mark then we start to look from the end
				{
					for(auto iter = vecKeys.rbegin();
						iter != vecKeys.rend();
						++iter)
					{
						if(newTime > iter->Time)
						{
							outNewFrame = *iter;
							break;
						}
					}
				}
				else // If we are below the half mark then we start to look from the start
				{
					for(auto iter = vecKeys.begin();
						iter != vecKeys.end();
						++iter)
					{
						if(newTime < iter->Time)
						{
							outNewFrame = *iter;
							break;
						}
					}
				}
			}
			static CML::Matrix4x4 CaluclateJoint(double oldTime, double newTime, double totalLength,
												 const std::vector<BasicAnimation::Node::Key>& vecKeys)
			{
				if(vecKeys.size() > 1)
				{
					BasicAnimation::Node::Key outOldFrame;
					BasicAnimation::Node::Key outNewFrame;
					PlayRecursively::FindKeys(oldTime, newTime, totalLength, vecKeys, outOldFrame, outNewFrame);
				}
				else if(vecKeys.size() == 1)
				{

				}
				else
				{

				}
				return{ };
			}
			static void Run(double OldTime, double NewTime, double totalLength,
							std::shared_ptr<BasicAnimation::Node> BANode,
							const CML::Matrix4x4& parentsInvJoint,
							AnimationPlayer* animationPlayer)
			{
			}
		};
	}
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
void AnimationPlayer::SetCurrentPhase(float phasePercentage)
{
	if(this->Animation.lock())
	{
		if(phasePercentage < 0.0f)
		{
			this->AnimTime = 0.0f;
		}
		else if(phasePercentage > 1.0f)
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
														float startPhase,
														float animRate)
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

const std::hash_map<std::string, CML::Matrix4x4> AnimationPlayer::JointsAnimatedTransformation() const
{
	return this->jointsAnimated;
}