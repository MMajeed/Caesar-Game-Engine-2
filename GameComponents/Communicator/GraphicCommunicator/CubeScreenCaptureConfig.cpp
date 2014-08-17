#include "CubeScreenCaptureConfig.h"
#include <ResourceManager.h>
#include <GenerateGUID.h>
#include <GraphicManager.h>
#include <CubeScreenCapture.h>
#include <BasicTexture.h>

namespace CubeScreenCaptureConfig
{
	void Create(unsigned int width,
				unsigned int height,
				unsigned int priority,
				const std::string& cameraID,
				std::string& ID,
				std::string& textureID)
	{
		class AddCubeScreenCapture : public Message
		{
		public:
			AddCubeScreenCapture(unsigned int width, 
								 unsigned int height,
								 unsigned int priority, 
								 const std::string& cameraID)
			{
				this->width = width;
				this->height = height;
				this->priority = priority;
				this->cameraID = cameraID;
				this->newTextureID = CHL::GenerateGUID();
				this->ID = CHL::GenerateGUID();
			}

			Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				std::shared_ptr<BasicTexture> newTexture = BasicTexture::Spawn();
				ResourceManager::TextureList.Insert(this->newTextureID, newTexture);

				std::shared_ptr<CubeScreenCapture> newCubeScreenShot =
					CubeScreenCapture::Spawn(this->newTextureID, this->width, this->height, this->priority, this->cameraID);
				ResourceManager::ScreenCaptureList.Insert(this->ID, newCubeScreenShot);

				return Message::Status::Complete;
			}

			std::string cameraID;
			std::string newTextureID;
			std::string ID;
			unsigned int width;
			unsigned int height;
			unsigned int priority;
		};

		std::shared_ptr<AddCubeScreenCapture> msg
			(new AddCubeScreenCapture(width, height, priority, cameraID));
		GraphicManager::GetInstance().SubmitMessage(msg);
		
		ID = msg->ID;
		textureID = msg->newTextureID;
	}
	void SetCameraID(const std::string& id, const std::string& cameraID)
	{
		class ChangeEye : public Message
		{
		public:
			ChangeEye(const std::string& id, const std::string& cameraID)
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
					std::shared_ptr<CubeScreenCapture> cast = std::dynamic_pointer_cast<CubeScreenCapture>(screenCapture);
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

		std::shared_ptr<ChangeEye> msg
			(new ChangeEye(id, cameraID));
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