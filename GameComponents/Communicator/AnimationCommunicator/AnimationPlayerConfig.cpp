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
	void SetPhase(std::string AnimationPlayerID, double phase)
	{
		class SetPhaseMesage : public Message
		{
		public:
			SetPhaseMesage(std::string AnimationPlayerID, double phase)
			{
				this->AnimationPlayerID = AnimationPlayerID;
				this->phase = phase;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(AnimationManager::GetInstance().mutex);

				auto& allPlayer = AnimationManager::GetInstance().AllAnimationPlayer();
				auto iterObjDrawable = allPlayer.find(this->AnimationPlayerID);

				if(iterObjDrawable != allPlayer.end())
				{
					iterObjDrawable->second->SetCurrentPhase(this->phase);
				}

				return Message::Status::Complete;
			}

			std::string AnimationPlayerID;
			double phase;
		};

		std::shared_ptr<SetPhaseMesage> msg(new SetPhaseMesage(AnimationPlayerID, phase));
		AnimationManager::GetInstance().SubmitMessage(msg);
	}
	void SetSpeed(std::string AnimationPlayerID, double speed)
	{
		class SetSpeedMesage : public Message
		{
		public:
			SetSpeedMesage(std::string AnimationPlayerID, double speed)
			{
				this->AnimationPlayerID = AnimationPlayerID;
				this->speed = speed;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(AnimationManager::GetInstance().mutex);

				auto& allPlayer = AnimationManager::GetInstance().AllAnimationPlayer();
				auto iterObjDrawable = allPlayer.find(this->AnimationPlayerID);

				if(iterObjDrawable != allPlayer.end())
				{
					iterObjDrawable->second->SetSpeed(this->speed);
				}

				return Message::Status::Complete;
			}

			std::string AnimationPlayerID;
			double speed;
		};

		std::shared_ptr<SetSpeedMesage> msg(new SetSpeedMesage(AnimationPlayerID, speed));
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
}