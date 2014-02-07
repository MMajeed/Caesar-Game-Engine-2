#include "AnimationController.h"
#include "AnimationManager.h"
#include <MathFunctions.h>

AnimationController::AnimationController()
{

}

void AnimationController::Play(double delta)
{
	this->UpdatePlayers(delta);
	this->UpdateMainJoints();
	this->UpdateTransitionJoints();

	this->CalculateJointsRecursively(this->RootNode, this->RootNode->Transformation);
}
void AnimationController::UpdatePlayers(double delta)
{
	double newDelta = delta * this->AnimRate;
	double oldPhase = this->MainAnimation->GetCurrentPhase();
	this->MainAnimation->Play(newDelta);
	double newPhase = this->MainAnimation->GetCurrentPhase();

	if(this->TransitionStage.TransitionAnimation)
	{
		switch(this->TransitionStage.State)
		{
		case Transition::TransitionState::CrossFade:
		case Transition::TransitionState::TimeSync:
		case Transition::TransitionState::SnapShot:
		{
			this->TransitionStage.TimeSinceStart += delta;
			if(this->TransitionStage.TimeSinceStart > this->TransitionStage.MaxLength)
			{
				this->TransitionStage.TransitionAnimation.reset();
				break;
			}
			switch(this->TransitionStage.State)
			{
			case Transition::TransitionState::CrossFade:
			{
				this->TransitionStage.TransitionAnimation->Play(newDelta);
				break;
			}
			case Transition::TransitionState::TimeSync:
			{
				this->TransitionStage.TransitionAnimation->SetCurrentPhase(newPhase);
				this->TransitionStage.TransitionAnimation->Play(0.0);
				break;
			}
			case Transition::TransitionState::SnapShot:
			{
				this->TransitionStage.TransitionAnimation->Play(0.0);
				break;
			}
			}
			break;
		}
		case Transition::TransitionState::CrossFadeNext:
		case Transition::TransitionState::TimeSyncNext:
		case Transition::TransitionState::SnapShotNext:
		{
			if(newPhase < oldPhase)
			{
				this->TransitionStage.TimeSinceStart = 0.0;
				auto temp = this->TransitionStage.TransitionAnimation;
				this->TransitionStage.TransitionAnimation = this->MainAnimation;
				this->MainAnimation = temp;
				switch(this->TransitionStage.State)
				{
				case Transition::TransitionState::CrossFadeNext:
				{
					this->TransitionStage.State = Transition::TransitionState::CrossFade;
					break;
				}
				case Transition::TransitionState::TimeSyncNext:
				{
					this->TransitionStage.State = Transition::TransitionState::TimeSync;
					break;
				}
				case Transition::TransitionState::SnapShotNext:
				{
					this->TransitionStage.State = Transition::TransitionState::SnapShot;
					break;
				}
				}
			}
			break;
		}
		}
	}
}
void AnimationController::UpdateMainJoints()
{
	std::hash_map<std::string, CML::Vec3>& CurrentTranslationJoint = this->MainAnimation->CurrentTranslationJoint;
	std::hash_map<std::string, CML::Vec4>& CurrentRotationJoint = this->MainAnimation->CurrentRotationJoint;
	std::hash_map<std::string, CML::Vec3>& CurrentScaleJoint = this->MainAnimation->CurrentScaleJoint;

	for(auto jointIter = this->AllNodes.begin();
		jointIter != this->AllNodes.end();
		++jointIter)
	{
		this->TranslationJoint[jointIter->second->Name] = CurrentTranslationJoint[jointIter->second->Name];
		this->RotationJoint[jointIter->second->Name] = CurrentRotationJoint[jointIter->second->Name];
		this->ScaleJoint[jointIter->second->Name] = CurrentScaleJoint[jointIter->second->Name];
	}
}
void AnimationController::UpdateTransitionJoints()
{
	if(this->TransitionStage.TransitionAnimation == false){ return; }
	if(    this->TransitionStage.State == Transition::TransitionState::CrossFadeNext
		|| this->TransitionStage.State == Transition::TransitionState::TimeSyncNext
		|| this->TransitionStage.State == Transition::TransitionState::SnapShotNext){ return; }

	std::hash_map<std::string, CML::Vec3>& CurrentTranslationJoint = this->TransitionStage.TransitionAnimation->CurrentTranslationJoint;
	std::hash_map<std::string, CML::Vec4>& CurrentRotationJoint = this->TransitionStage.TransitionAnimation->CurrentRotationJoint;
	std::hash_map<std::string, CML::Vec3>& CurrentScaleJoint = this->TransitionStage.TransitionAnimation->CurrentScaleJoint;

	double t = this->TransitionStage.TimeSinceStart / this->TransitionStage.MaxLength;
	for(auto jointIter = this->AllNodes.begin();
		jointIter != this->AllNodes.end();
		++jointIter)
	{
		CML::Vec3& tranA = CurrentTranslationJoint[jointIter->second->Name];
		CML::Vec3& tranB = this->TranslationJoint[jointIter->second->Name];
		this->TranslationJoint[jointIter->second->Name] = CML::Lerp(tranA, tranB, t);

		CML::Vec4& rotA = CurrentRotationJoint[jointIter->second->Name];
		CML::Vec4& rotB = this->RotationJoint[jointIter->second->Name];
		this->RotationJoint[jointIter->second->Name] = CML::Slerp(rotA, rotB, t);

		CML::Vec3& scaleA = CurrentScaleJoint[jointIter->second->Name];
		CML::Vec3& scaleB = this->ScaleJoint[jointIter->second->Name];
		this->ScaleJoint[jointIter->second->Name] = CML::Lerp(scaleA, scaleB, t);
	}
}
void AnimationController::CalculateJointsRecursively(std::shared_ptr<AnimationController::Node> BANode, 
													 const CML::Matrix4x4& parentsJoint)
{
	CML::Vec3 translation = this->TranslationJoint[BANode->Name];
	CML::Vec4 rotation = this->RotationJoint[BANode->Name];
	CML::Vec3 scale = this->ScaleJoint[BANode->Name];

	CML::Matrix4x4 tranformation = CML::TransformMatrix(translation, rotation, scale);
	CML::Matrix4x4 finalTranslation = CML::Multiple(parentsJoint, tranformation);

	this->SetJoint(BANode->Name, finalTranslation);

	for(auto iter = BANode->Childern.begin();
		iter != BANode->Childern.end();
		++iter)
	{
		this->CalculateJointsRecursively(*iter, finalTranslation);
	}
}

void AnimationController::ChangeAnimation(std::string basicAnimationID, TransitionType Transition, double TransitionLength, bool StartNextPhase)
{
	std::shared_ptr<AnimationPlayer> newAnimation = AnimationPlayer::Spawn(basicAnimationID, 0.0);

	switch(Transition)
	{
	case TransitionType::None:
	{
		this->MainAnimation = newAnimation;
		break;
	}
	case TransitionType::CrossFade:
	{
		this->TransitionStage.TimeSinceStart = 0.0;
		this->TransitionStage.MaxLength = TransitionLength;
		if(StartNextPhase == true)
		{ 
			this->TransitionStage.State = Transition::TransitionState::CrossFadeNext;
			this->TransitionStage.TransitionAnimation = newAnimation;
		}
		else if(StartNextPhase == false)
		{ 
			this->TransitionStage.State = Transition::TransitionState::CrossFade;
			this->TransitionStage.TransitionAnimation = this->MainAnimation;
			this->MainAnimation = newAnimation;
		}
		break;
	}
	case TransitionType::SnapShot:
	{
		this->TransitionStage.TimeSinceStart = 0.0;
		this->TransitionStage.MaxLength = TransitionLength;
		if(StartNextPhase == true)
		{
			this->TransitionStage.State = Transition::TransitionState::SnapShotNext;
			this->TransitionStage.TransitionAnimation = newAnimation;
		}
		else if(StartNextPhase == false)
		{
			this->TransitionStage.State = Transition::TransitionState::SnapShot;
			this->TransitionStage.TransitionAnimation = this->MainAnimation;
			this->MainAnimation = newAnimation;
		}
		break;
	}
	case TransitionType::TimeSync:
	{
		this->TransitionStage.TimeSinceStart = 0.0;
		this->TransitionStage.MaxLength = TransitionLength;
		if(StartNextPhase == true)
		{
			this->TransitionStage.State = Transition::TransitionState::TimeSyncNext;
			this->TransitionStage.TransitionAnimation = newAnimation;
		}
		else if(StartNextPhase == false)
		{
			this->TransitionStage.State = Transition::TransitionState::TimeSync;
			this->TransitionStage.TransitionAnimation = this->MainAnimation;
			this->MainAnimation = newAnimation;
		}
		break;
	}
	}
}

std::shared_ptr<AnimationController> AnimationController::Spawn(std::shared_ptr<CHL::Node> rootNode, 
																std::string basicAnimationID,
																double speed)
{
	AnimationManager& animationManager = AnimationManager::GetInstance();

	std::shared_ptr<AnimationController> newObject(new AnimationController());

	newObject->MainAnimation = AnimationPlayer::Spawn(basicAnimationID, 0.0);
	newObject->SetSpeed(speed);
	newObject->RootNode = std::shared_ptr<AnimationController::Node>(new AnimationController::Node);
	newObject->LoadNodesRecursively(newObject->RootNode, rootNode);

	return newObject;
}
void  AnimationController::LoadNodesRecursively(std::shared_ptr<AnimationController::Node>& BANodes, const std::shared_ptr<CHL::Node>& CHLNode)
{
	BANodes->Name = CHLNode->Name;
	BANodes->Transformation = CHLNode->Transformation;

	for(auto iter = CHLNode->Childern.begin();
		iter != CHLNode->Childern.end();
		++iter)
	{
		std::shared_ptr<AnimationController::Node> BAChildNode(new AnimationController::Node);
		BAChildNode->Parent = BANodes;
		this->LoadNodesRecursively(BAChildNode, (*iter));
		BANodes->Childern.push_back(BAChildNode);
	}
	this->AllNodes[BANodes->Name] = BANodes;
}

double AnimationController::GetSpeed()
{
	return this->AnimRate;
}
void AnimationController::SetSpeed(double speed)
{
	this->AnimRate = speed;
}

CML::Matrix4x4 AnimationController::GetSingleJoint(std::string jointName)
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
void AnimationController::SetJoint(std::string name, const CML::Matrix4x4& mat)
{
	AnimationManager& animationManager = AnimationManager::GetInstance();

	std::lock_guard<std::mutex> lock(animationManager.mutex);

	this->jointsAnimated[name] = mat;
}
const std::hash_map<std::string, CML::Matrix4x4>& AnimationController::JointsAnimatedTransformation() const
{
	return this->jointsAnimated;
}
