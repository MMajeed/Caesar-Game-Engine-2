#include "AnimationControllerConfig.h"

#include <AnimationManager.h>
#include <AnimationController.h>
#include <GenerateGUID.h>
#include <MathFunctions.h>

namespace AnimationControllerConfig
{
	std::string Create(std::string animPlayerID, std::shared_ptr<CHL::Node> rootNode)
	{
		class  CreateMessage : public Message
		{
		public:
			CreateMessage(std::string animPlayerID, std::shared_ptr<CHL::Node> rootNode)
			{
				this->ID = CHL::GenerateGUID();
				this->animPlayerID = animPlayerID;
				this->rootNode = rootNode;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(AnimationManager::GetInstance().mutex);
				std::shared_ptr<AnimationController> newAnimationController
					= AnimationController::Spawn(rootNode, this->animPlayerID);
				AnimationManager::GetInstance().InsertAnimationController(this->ID, newAnimationController);

				return Message::Status::Complete;
			}

			std::string animPlayerID;
			std::shared_ptr<CHL::Node> rootNode;
			std::string	ID;
		};

		std::shared_ptr<CreateMessage> msg(new CreateMessage(animPlayerID, rootNode));
		AnimationManager::GetInstance().SubmitMessage(msg);
		return msg->ID;
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