#include "AnimationPlayer.h"
#include "AnimationManager.h"
#include <MathFunctions.h>

AnimationPlayer::AnimationPlayer()
{
	this->AnimTime = 0.0;
	this->AnimRate = 0.0;
	this->LastTranslationFrame = 0;
	this->LastRotationFrame = 0;
	this->LastScaleFrame = 0;
}

void AnimationPlayer::Play(double delta)
{
	std::shared_ptr<BasicAnimation> spAnimation = this->Animation.lock();

	if(spAnimation)
	{
		double oldAnimTime = this->AnimTime;
		double newAnimTime = oldAnimTime +(delta * this->AnimRate);
		this->AnimTime = newAnimTime;
		if(newAnimTime == oldAnimTime) // They are the same, so skip
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

			enum class InterpolationType { Lerp, Slerp, };
			static CML::Vec4 CaluclateJoint(double oldTime, double newTime, double totalLength,
											const std::vector<BasicAnimation::Node::Key>& vecKeys, 
											InterpolationType interpolation )
			{
				CML::Vec4 returnValue;
				if(vecKeys.size() > 1)
				{
					BasicAnimation::Node::Key outOldFrame;
					BasicAnimation::Node::Key outNewFrame;
					PlayRecursively::FindKeys(oldTime, newTime, totalLength, vecKeys, outOldFrame, outNewFrame);

					double ratio = newTime - outNewFrame.Time / (outNewFrame.Time - outNewFrame.Time);

					switch(interpolation)
					{
					case InterpolationType::Lerp:
						returnValue = CML::Lerp(outOldFrame.Value, outNewFrame.Value, ratio);
						break;
					case InterpolationType::Slerp:
						returnValue = CML::Slerp(outOldFrame.Value, outNewFrame.Value, ratio);
						break;
					}
				}
				else if(vecKeys.size() == 1)
				{
					returnValue = vecKeys.front().Value;
				}
				else
				{
					returnValue = {1.0, 1.0, 1.0, 1.0};
				}
				return returnValue;
			}
			static void Run(double oldTime, double newTime, double totalLength,
							std::shared_ptr<BasicAnimation::Node> BANode,
							const CML::Matrix4x4& parentsJoint,
							AnimationPlayer* animationPlayer)
			{
				CML::Vec4 translation = CaluclateJoint(oldTime, newTime, totalLength, BANode->Translation, InterpolationType::Lerp);
				CML::Vec4 rotation = CaluclateJoint(oldTime, newTime, totalLength, BANode->Rotation, InterpolationType::Slerp);
				CML::Vec4 scale = CaluclateJoint(oldTime, newTime, totalLength, BANode->Scale, InterpolationType::Lerp);

				CML::Matrix4x4 tranformation = CML::TransformMatrix(translation, rotation, scale);

				CML::Matrix4x4 finalTranslation = CML::Multiple(tranformation, parentsJoint);

				animationPlayer->SetJoint(BANode->Name, finalTranslation);

				for(auto iter = BANode->Childern.begin();
					iter != BANode->Childern.end();
					++iter)
				{
					PlayRecursively::Run(oldTime, newTime, totalLength, *iter, finalTranslation, animationPlayer);
				}
			}
		};

		PlayRecursively::Run(oldAnimTime, newAnimTime, spAnimation->Duration, spAnimation->RootNode, CML::MatrixIdentity(), this);
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