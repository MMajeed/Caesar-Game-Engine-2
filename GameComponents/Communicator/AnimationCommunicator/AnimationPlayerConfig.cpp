#include "AnimationPlayerConfig.h"

#include <AnimationManager.h>
#include <AnimationPlayer.h>
#include <GenerateGUID.h>

namespace AnimationPlayerConfig
{
	std::string Create(std::string basicAnimationID, double startPhase, double animRate)
	{
		class  CreateMessage : public Message
		{
		public:
			CreateMessage(std::string basicAnimationID, double startPhase, double animRate)
			{
				this->ID = CHL::GenerateGUID();
				this->basicAnimationID = basicAnimationID;
				this->startPhase = startPhase;
				this->animRate = animRate;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(AnimationManager::GetInstance().mutex);
				std::shared_ptr<AnimationPlayer> neAnimationPlayer
						= AnimationPlayer::Spawn(this->basicAnimationID, this->startPhase, this->animRate);
				AnimationManager::GetInstance().InsertAnimationPlayer(this->ID, neAnimationPlayer);

				return Message::Status::Complete;
			}

			std::string basicAnimationID;
			double startPhase;
			double animRate;
			std::string	ID;
		};

		std::shared_ptr<CreateMessage> msg(new CreateMessage(basicAnimationID, startPhase, animRate));
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
}