#include "AnimationController.h"
#include "AnimationManager.h"
#include <MathFunctions.h>

AnimationController::AnimationController()
{

}

void AnimationController::Play(double delta)
{
	std::shared_ptr<AnimationPlayer> spAnimation = this->MainAnimation.lock();
	if(!spAnimation){ return; }

	spAnimation->Play(delta);

	this->TranslationJoint = spAnimation->GetAllTranslation();
	this->RotationJoint = spAnimation->GetAllRotation();
	this->ScaleJoint = spAnimation->GetAllScale();

	this->CalculateJointsRecursively(this->RootNode, this->RootNode->Transformation);
}
void AnimationController::CalculateJointsRecursively(std::shared_ptr<AnimationController::Node> BANode, const CML::Matrix4x4& parentsJoint)
{
	std::shared_ptr<AnimationPlayer> spAnimation = this->MainAnimation.lock();
	if(!spAnimation){ return; }

	CML::Vec3 translation = spAnimation->GetAllTranslation()[BANode->Name];
	CML::Vec4 rotation = spAnimation->GetAllRotation()[BANode->Name];
	CML::Vec3 scale = spAnimation->GetAllScale()[BANode->Name];

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

std::shared_ptr<AnimationController> AnimationController::Spawn(std::shared_ptr<CHL::Node> rootNode, std::string animtionPlayerID)
{
	AnimationManager& animationManager = AnimationManager::GetInstance();

	std::shared_ptr<AnimationController> newObject(new AnimationController());

	auto iter = animationManager.AnimationsPlayerContainer.find(animtionPlayerID);
	if(iter != animationManager.AnimationsPlayerContainer.end())
	{
		newObject->MainAnimation = iter->second;
	}

	struct LoadNodesRecursive
	{
		static void Run(std::shared_ptr<AnimationController::Node>& BANodes,
						const std::shared_ptr<CHL::Node>& CHLNode)
		{
			BANodes->Name = CHLNode->Name;
			BANodes->Transformation = CHLNode->Transformation;


			for(auto iter = CHLNode->Childern.begin();
				iter != CHLNode->Childern.end();
				++iter)
			{
				std::shared_ptr<AnimationController::Node> BAChildNode(new AnimationController::Node);
				BAChildNode->Parent = BANodes;
				LoadNodesRecursive::Run(BAChildNode, (*iter));
				BANodes->Childern.push_back(BAChildNode);
			}
		}
	};
	newObject->RootNode = std::shared_ptr<AnimationController::Node>(new AnimationController::Node);
	LoadNodesRecursive::Run(newObject->RootNode, rootNode);

	return newObject;
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
