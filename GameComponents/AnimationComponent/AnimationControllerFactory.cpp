#include "AnimationControllerFactory.h"
#include <GenerateGUID.h>
#include <Components.h>
#include "Resource.h"

std::string AnimationControllerFactory::Create(std::string basicAnimID, std::shared_ptr<CHL::Node> rootNode, double speed)
{
	std::string ID = CHL::GenerateGUID();

	Components::Animation->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Animation->Mutex());

		std::shared_ptr<AnimationController> newAnimationController
			= AnimationController::Spawn(rootNode, basicAnimID, speed);
		Resource::AnimationControllerList[ID] = newAnimationController;

		return Message::Status::Complete;
	});

	return ID;
}
void AnimationControllerFactory::ChangeAnimation(std::string AnimationControllerID,
												 std::string basicAnimID,
												 TransitionType Transition,
												 double TransitionLength,
												 bool StartNextPhase)
{
	Components::Animation->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Animation->Mutex());

		auto& allController = Resource::AnimationControllerList;
		auto iterController = allController.find(AnimationControllerID);

		if(iterController != allController.end())
		{
			std::shared_ptr<AnimationController> controllerObj = std::dynamic_pointer_cast<AnimationController>(iterController->second);

			if(controllerObj)
			{
				AnimationController::TransitionType type = static_cast<AnimationController::TransitionType>(Transition);
				controllerObj->ChangeAnimation(basicAnimID, type, TransitionLength, StartNextPhase);
			}
		}

		return Message::Status::Complete;
	});
}
std::string AnimationControllerFactory::AddMinorAnimation(std::string AnimationControllerID,
														  std::string basicAnimID,
														  std::string startNodeName,
														  double startingRatio,
														  double stepRatio)
{
	std::string MinorAnimationID = CHL::GenerateGUID();

	Components::Animation->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Animation->Mutex());

		auto& allController = Resource::AnimationControllerList;
		auto iterController = allController.find(AnimationControllerID);

		if(iterController != allController.end())
		{
			std::shared_ptr<AnimationController> controllerObj = iterController->second;

			if(controllerObj)
			{
				controllerObj->AddMinorAnimation(MinorAnimationID, basicAnimID, startNodeName, startingRatio, stepRatio);
			}
		}

		return Message::Status::Complete;
	});

	return MinorAnimationID;
}
void AnimationControllerFactory::RemoveMinorAnimation(std::string AnimationControllerID, std::string minorAnimationID)
{
	Components::Animation->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Animation->Mutex());

		auto& allController = Resource::AnimationControllerList;
		auto iterController = allController.find(AnimationControllerID);

		if(iterController != allController.end())
		{
			std::shared_ptr<AnimationController> controllerObj = iterController->second;

			if(controllerObj)
			{
				controllerObj->RemoveMinorAnimation(minorAnimationID);
			}
		}

		return Message::Status::Complete;
	});
}
void AnimationControllerFactory::ChangeSpeed(std::string AnimationControllerID, double speed)
{
	Components::Animation->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Animation->Mutex());

		auto& allController = Resource::AnimationControllerList;
		auto iterController = allController.find(AnimationControllerID);

		if(iterController != allController.end())
		{
			std::shared_ptr<AnimationController> controllerObj = std::dynamic_pointer_cast<AnimationController>(iterController->second);

			if(controllerObj)
			{
				controllerObj->SetSpeed(speed);
			}
		}

		return Message::Status::Complete;
	});
}
void AnimationControllerFactory::Release(std::string ID)
{
	Components::Animation->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Animation->Mutex());

		Resource::AnimationControllerList.erase(ID);

		return Message::Status::Complete;
	});
}

CML::Matrix4x4 AnimationControllerFactory::GetSingleJoint(std::string ID, std::string JointName)
{
	std::lock_guard<std::mutex> lock(Components::Animation->Mutex());

	const auto& animController = Resource::AnimationControllerList;

	auto iter = animController.find(ID);
	if(iter != animController.end())
	{
		return iter->second->GetSingleJoint(JointName);
	}
	else { return CML::Matrix4x4(); }
}