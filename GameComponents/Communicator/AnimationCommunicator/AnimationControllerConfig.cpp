#include "AnimationControllerConfig.h"

#include <AnimationManager.h>
#include <AnimationController.h>
#include <GenerateGUID.h>
#include <MathFunctions.h>

namespace AnimationControllerConfig
{
	std::string Create(std::string basicAnimID, std::shared_ptr<CHL::Node> rootNode, double speed)
	{
		class  CreateMessage : public Message
		{
		public:
			CreateMessage(std::string basicAnimID, std::shared_ptr<CHL::Node> rootNode, double speed)
			{
				this->ID = CHL::GenerateGUID();
				this->basicAnimID = basicAnimID;
				this->rootNode = rootNode;
				this->speed = speed;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(AnimationManager::GetInstance().mutex);
				std::shared_ptr<AnimationController> newAnimationController
					= AnimationController::Spawn(rootNode, this->basicAnimID, speed);
				AnimationManager::GetInstance().InsertAnimationController(this->ID, newAnimationController);

				return Message::Status::Complete;
			}

			std::string basicAnimID;
			std::shared_ptr<CHL::Node> rootNode; 
			double speed;
			std::string	ID;
		};

		std::shared_ptr<CreateMessage> msg(new CreateMessage(basicAnimID, rootNode, speed));
		AnimationManager::GetInstance().SubmitMessage(msg);
		return msg->ID;
	}
	void ChangeAnimation(	std::string AnimationControllerID, 
							std::string basicAnimID, 
							TransitionType Transition, 
							double TransitionLength, 
							bool StartNextPhase)
	{
		class ChangeAnimation : public Message
		{
		public:
			ChangeAnimation(std::string AnimationControllerID, 
							std::string basicAnimID, 
							TransitionType Transition, 
							double TransitionLength, 
							bool StartNextPhase)
			{
				this->AnimationControllerID = AnimationControllerID;
				this->basicAnimID = basicAnimID;
				this->Transition = Transition;
				this->TransitionLength = TransitionLength;
				this->StartNextPhase = StartNextPhase;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(AnimationManager::GetInstance().mutex);

				auto& allController = AnimationManager::GetInstance().AllAnimationController();
				auto iterController = allController.find(this->AnimationControllerID);

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
			}
			std::string AnimationControllerID;
			std::string basicAnimID;
			TransitionType Transition;
			double TransitionLength;
			bool StartNextPhase;
		};

		std::shared_ptr<ChangeAnimation> msg(new ChangeAnimation(AnimationControllerID, basicAnimID, Transition, TransitionLength, StartNextPhase));
		AnimationManager::GetInstance().SubmitMessage(msg);
	}
	void ChangeSpeed(std::string AnimationControllerID, double speed)
	{
		class ChangeSpeed : public Message
		{
		public:
			ChangeSpeed(std::string AnimationControllerID, double speed)
			{
				this->AnimationControllerID = AnimationControllerID;
				this->speed = speed;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(AnimationManager::GetInstance().mutex);

				auto& allController = AnimationManager::GetInstance().AllAnimationController();
				auto iterController = allController.find(this->AnimationControllerID);

				if(iterController != allController.end())
				{
					std::shared_ptr<AnimationController> controllerObj = std::dynamic_pointer_cast<AnimationController>(iterController->second);

					if(controllerObj)
					{
						controllerObj->SetSpeed(speed);
					}
				}

				return Message::Status::Complete;
			}
			std::string AnimationControllerID;
			double speed;
		};

		std::shared_ptr<ChangeSpeed> msg(new ChangeSpeed(AnimationControllerID, speed));
		AnimationManager::GetInstance().SubmitMessage(msg);
	}
	void Release(std::string ID)
	{
		class ReleaseMessage : public Message
		{
		public:
			std::string ID;
			ReleaseMessage(std::string ID)
			{
				this->ID = ID;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(AnimationManager::GetInstance().mutex);

				AnimationManager::GetInstance().RemoveAnimationController(this->ID);

				return Message::Status::Complete;
			}
		};

		std::shared_ptr<ReleaseMessage> msg(new ReleaseMessage(ID));
		AnimationManager::GetInstance().SubmitMessage(msg);
	}

	CML::Matrix4x4 GetSingleJoint(std::string ID, std::string JointName)
	{
		CML::Matrix4x4 returnValue = CML::MatrixIdentity();
		AnimationManager& animationManager = AnimationManager::GetInstance();

		std::lock_guard<std::mutex> lock(animationManager.mutex);
		
		const std::hash_map<std::string, std::shared_ptr<AnimationController>>& animController =
			animationManager.AllAnimationController();

		auto iter = animController.find(ID);
		if(iter != animController.end())
		{
			returnValue = iter->second->GetSingleJoint(JointName);
		}
		return returnValue;
	}
}