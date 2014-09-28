#include "DepthScreenCaptureConfig.h"
#include <ResourceManager.h>
#include <GenerateGUID.h>
#include <GraphicManager.h>
#include <DepthScreenCapture.h>
#include <BasicTexture.h>

namespace DepthScreenCaptureConfig
{
	void Create(unsigned int width,
				unsigned int height,
				unsigned int priority,
				const std::string& cameraID,
				const std::string& drawSettingsID,
				std::string& ID,
				std::string& textureID)
	{
		class AddDepthScreenCapture : public Message
		{
		public:
			AddDepthScreenCapture(unsigned int width, 
								  unsigned int height,
								  unsigned int priority,
								  const std::string& cameraID,
								  const std::string& drawSettingsID)
			{
				this->width = width;
				this->height = height;
				this->priority = priority;
				this->cameraID = cameraID;
				this->drawSettingsID = drawSettingsID;
				this->newTextureID = CHL::GenerateGUID();
				this->ID = CHL::GenerateGUID();
			}

			Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				std::shared_ptr<BasicTexture> newTexture =
					BasicTexture::Spawn();
				ResourceManager::TextureList.Insert(this->newTextureID, newTexture);

				std::shared_ptr<DepthScreenCapture> newDepthScreenShot =
					DepthScreenCapture::Spawn(this->newTextureID, this->width, this->height, this->priority, this->cameraID, this->drawSettingsID);
				ResourceManager::ScreenCaptureList.Insert(this->ID, newDepthScreenShot);

				return Message::Status::Complete;
			}


			std::string cameraID;
			std::string drawSettingsID;
			std::string newTextureID;
			std::string ID;
			unsigned int width;
			unsigned int height;
			unsigned int priority;
		};
		std::shared_ptr<AddDepthScreenCapture> msg
			(new AddDepthScreenCapture(width, height, priority, cameraID, drawSettingsID));
		GraphicManager::GetInstance().SubmitMessage(msg);
		ID = msg->ID;
		textureID = msg->newTextureID;
	}
	void SetCameraID(const std::string& id, const std::string& cameraID)
	{
		class ChangeCameraMatrix : public Message
		{
		public:
			ChangeCameraMatrix(const std::string& id, const std::string& cameraID)
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
					std::shared_ptr<DepthScreenCapture> cast = std::dynamic_pointer_cast<DepthScreenCapture>(screenCapture);
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

		std::shared_ptr<ChangeCameraMatrix> msg
			(new ChangeCameraMatrix(id, cameraID));
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
					std::shared_ptr<DepthScreenCapture> cast = std::dynamic_pointer_cast<DepthScreenCapture>(screenCapture);
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