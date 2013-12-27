#include "DepthScreenCaptureConfig.h"
#include <GenerateGUID.h>
#include <GraphicManager.h>
#include <DepthScreenCapture.h>
#include <BasicTexture.h>

namespace DepthScreenCaptureConfig
{
	void Create(unsigned int width,
				unsigned int height,
				const std::string& cameraID,
				std::string& ID,
				std::string& textureID)
	{
		class AddDepthScreenCapture : public Message
		{
		public:
			AddDepthScreenCapture(unsigned int width, unsigned int height, const std::string& cameraID)
			{
				this->width = width;
				this->height = height;
				this->cameraID = cameraID;
				this->newTextureID = CHL::GenerateGUID();
				this->ID = CHL::GenerateGUID();
			}

			Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				std::shared_ptr<BasicTexture> newTexture =
					BasicTexture::Spawn();
				GraphicManager::GetInstance().InsertTexture(this->newTextureID, newTexture);

				std::shared_ptr<DepthScreenCapture> newDepthScreenShot =
					DepthScreenCapture::Spawn(this->newTextureID, this->width, this->height, this->cameraID);
				GraphicManager::GetInstance().InsertScreenCapture(this->ID, newDepthScreenShot);

				return Message::Status::Complete;
			}


			std::string cameraID;
			std::string newTextureID;
			std::string ID;
			unsigned int width;
			unsigned int height;
		};
		std::shared_ptr<AddDepthScreenCapture> msg
			(new AddDepthScreenCapture(width, height, cameraID));
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

				auto& allContinuous = GraphicManager::GetInstance().AllScreenCapture();
				auto iter = allContinuous.find(this->ID);
				if(iter != allContinuous.end())
				{
					std::shared_ptr<DepthScreenCapture> cast = std::dynamic_pointer_cast<DepthScreenCapture>(iter->second);
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
				
				GraphicManager::GetInstance().RemoveScreenCapture(this->ID);

				return Message::Status::Complete;
			}
		};

		std::shared_ptr<ReleaseCapture> msg
			(new ReleaseCapture(ID));
		GraphicManager::GetInstance().SubmitMessage(msg);
	}
};