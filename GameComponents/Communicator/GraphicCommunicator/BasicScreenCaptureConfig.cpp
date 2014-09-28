#include "BasicScreenCaptureConfig.h"
#include <GenerateGUID.h>
#include <GraphicManager.h>
#include <BasicScreenCapture.h>
#include <BasicTexture.h>
#include <ResourceManager.h>

namespace BasicScreenCaptureConfig
{
	void Create(unsigned int width,
				unsigned int height,
				unsigned int priority,
				const std::string& cameraID,
				const std::string& drawSettingsID,
				unsigned int numberOfTargets,
				std::string& ID,
				std::vector<std::string>& textureID)
	{
		class AddBasicScreenCapture : public Message
		{
		public:
			AddBasicScreenCapture(unsigned int width,
								  unsigned int height,
								  unsigned int priority,
								  unsigned int numberOfTargets,
								  const std::string& cameraID,
								  const std::string& drawSettingsID )
			{
				this->cameraID = cameraID;
				this->drawSettingsID = drawSettingsID;
				this->width = width;
				this->height = height;
				this->priority = priority;
				this->numberOfTargets = numberOfTargets;
				this->ID = CHL::GenerateGUID();
				for(unsigned int i = 0; i < this->numberOfTargets; ++i)
				{
					this->textureID.push_back(CHL::GenerateGUID());
				}
			}

			Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				for(unsigned int i = 0; i < this->numberOfTargets; ++i)
				{
					std::shared_ptr<BasicTexture> newTexture = BasicTexture::Spawn();
					ResourceManager::TextureList.Insert(this->textureID[i], newTexture);
				}

				std::shared_ptr<BasicScreenCapture> newBasicScreenShot =
					BasicScreenCapture::Spawn(this->textureID, this->width, this->height, this->priority, this->cameraID, this->drawSettingsID);
				ResourceManager::ScreenCaptureList.Insert(this->ID, newBasicScreenShot);

				return Message::Status::Complete;
			}


			unsigned int width;
			unsigned int height;
			unsigned int priority;
			std::string cameraID;
			std::string drawSettingsID;
			unsigned int numberOfTargets;
			std::string ID;
			std::vector<std::string> textureID;
		};

		std::shared_ptr<AddBasicScreenCapture> msg
			(new AddBasicScreenCapture(width, height, priority, numberOfTargets, cameraID, drawSettingsID));
		GraphicManager::GetInstance().SubmitMessage(msg);
		ID = msg->ID;
		textureID = msg->textureID;
	}
	void SetCameraID(const std::string& id, const std::string& cameraID)
	{
		class ChangeCameraMessage : public Message
		{
		public:
			ChangeCameraMessage(const std::string& id, const std::string& cameraID)
			{
				this->ID = id;
				this->cameraID = cameraID;
			}

			Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				auto screenCapture = ResourceManager::ScreenCaptureList.Find(this->ID);
				if(screenCapture)
				{
					std::shared_ptr<BasicScreenCapture> cast = std::dynamic_pointer_cast<BasicScreenCapture>(screenCapture);
					if(cast)
					{
						cast->cameraID = this->cameraID;
					}
				}
				
				return Message::Status::Complete;
			}
			std::string ID;
			std::string cameraID;
		};

		std::shared_ptr<ChangeCameraMessage> msg
			(new ChangeCameraMessage(id, cameraID));
		GraphicManager::GetInstance().SubmitMessage(msg);
	}
	void SetDrawSettingsID(const std::string& id, const std::string& dsID)
	{
		class ChangeDrawSettingsMessage : public Message
		{
		public:
			ChangeDrawSettingsMessage(const std::string& id, const std::string& DrawSettingsID)
			{
				this->ID = id;
				this->DrawSettingsID = DrawSettingsID;
			}

			Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				auto screenCapture = ResourceManager::ScreenCaptureList.Find(this->ID);
				if(screenCapture)
				{
					std::shared_ptr<BasicScreenCapture> cast = std::dynamic_pointer_cast<BasicScreenCapture>(screenCapture);
					if(cast)
					{
						cast->drawSettingsID = this->DrawSettingsID;
					}
				}

				return Message::Status::Complete;
			}
			std::string ID;
			std::string DrawSettingsID;
		};

		std::shared_ptr<ChangeDrawSettingsMessage> msg
			(new ChangeDrawSettingsMessage(id, dsID));
		GraphicManager::GetInstance().SubmitMessage(msg);
	}
	void SetPriority(const std::string& id, int p)
	{
		class SetPriorityMessage : public Message
		{
		public:
			SetPriorityMessage(const std::string& id, int p)
			{
				this->ID = id;
				this->p = p;
			}

			Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				auto screenCapture = ResourceManager::ScreenCaptureList.Find(this->ID);
				if(screenCapture)
				{
					std::shared_ptr<BasicScreenCapture> cast = std::dynamic_pointer_cast<BasicScreenCapture>(screenCapture);
					if(cast)
					{
						cast->Priority = this->p;
					}
				}

				return Message::Status::Complete;
			}
			std::string ID;
			int p;
		};

		std::shared_ptr<SetPriorityMessage> msg
			(new SetPriorityMessage(id, p));
		GraphicManager::GetInstance().SubmitMessage(msg);
	}
	void Release(std::string ID)
	{
		class ReleaseCapture : public Message
		{
		public:
			std::string ID;
			ReleaseCapture(std::string ID)
			{
				this->ID = ID;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				ResourceManager::ScreenCaptureList.Remove(this->ID);

				return Message::Status::Complete;
			}
		};

		std::shared_ptr<ReleaseCapture> msg
			(new ReleaseCapture(ID));
		GraphicManager::GetInstance().SubmitMessage(msg);
	}
};