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
								  const std::string& cameraID)
			{
				this->cameraID = cameraID;
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
					BasicScreenCapture::Spawn(this->textureID, this->width, this->height, this->numberOfTargets, this->priority, this->cameraID);
				ResourceManager::ScreenCaptureList.Insert(this->ID, newBasicScreenShot);

				return Message::Status::Complete;
			}


			unsigned int width;
			unsigned int height;
			unsigned int priority;
			std::string cameraID;
			unsigned int numberOfTargets;
			std::string ID;
			std::vector<std::string> textureID;
		};

		std::shared_ptr<AddBasicScreenCapture> msg
			(new AddBasicScreenCapture(width, height, priority, numberOfTargets, cameraID));
		GraphicManager::GetInstance().SubmitMessage(msg);
		ID = msg->ID;
		textureID = msg->textureID;
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

		std::shared_ptr<ChangeCameraMatrix> msg
			(new ChangeCameraMatrix(id, cameraID));
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