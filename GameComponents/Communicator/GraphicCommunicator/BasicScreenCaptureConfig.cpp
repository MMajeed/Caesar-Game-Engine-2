#include "BasicScreenCaptureConfig.h"
#include <GenerateGUID.h>
#include <GraphicManager.h>
#include <BasicScreenCapture.h>
#include <BasicTexture.h>

namespace BasicScreenCaptureConfig
{
	void Create(unsigned int width,
				unsigned int height,
				const CHL::Matrix4x4& cameraMatrix,
				const CHL::Matrix4x4& prespectiveMatrix,
				std::string& ID,
				std::string& textureID)
	{
		class AddBasicScreenCapture : public Message
		{
		public:
			AddBasicScreenCapture(unsigned int width, 
								  unsigned int height, 
								  const CHL::Matrix4x4& cameraMatrix, 
								  const CHL::Matrix4x4& prespectiveMatrix)
			{
				this->width = width;
				this->height = height;
				this->camerMatrix = cameraMatrix;
				this->prespectiveMatrix = prespectiveMatrix;
				this->newTextureID = CHL::GenerateGUID();
				this->ID = CHL::GenerateGUID();
			}

			Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				std::shared_ptr<BasicTexture> newTexture =
					BasicTexture::Spawn(this->newTextureID);
				GraphicManager::GetInstance().InsertTexture(newTexture);

				std::shared_ptr<BasicScreenCapture> newBasicScreenShot =
					BasicScreenCapture::Spawn(this->ID, this->newTextureID, this->width, this->height, this->camerMatrix, this->prespectiveMatrix);
				GraphicManager::GetInstance().InsertScreenCapture(newBasicScreenShot);

				return Message::Status::Complete;
			}

			CHL::Matrix4x4 camerMatrix;
			CHL::Matrix4x4 prespectiveMatrix;
			std::string newTextureID;
			std::string ID;
			unsigned int width;
			unsigned int height;
		};

		std::shared_ptr<AddBasicScreenCapture> msg
			(new AddBasicScreenCapture(width, height, cameraMatrix, prespectiveMatrix));
		GraphicManager::GetInstance().SubmitMessage(msg);
		ID = msg->ID;
		textureID = msg->newTextureID;
	}
	void SetCamera(const std::string& id, const CHL::Matrix4x4& camera)
	{
		class ChangeCameraMatrix : public Message
		{
		public:
			ChangeCameraMatrix(const std::string& id, const CHL::Matrix4x4& camera)
			{
				this->ID = id;
				this->camerMatrix = camera;
			}

			Message::Status Work()
			{
				auto allContinuous = GraphicManager::GetInstance().AllScreenCapture();
				auto iter = allContinuous.find(this->ID);
				if(iter != allContinuous.end())
				{
					std::shared_ptr<BasicScreenCapture> cast = std::dynamic_pointer_cast<BasicScreenCapture>(iter->second);
					if(cast)
					{
						cast->cameraMatrix = this->camerMatrix;
					}
				}

				return Message::Status::Complete;
			}
			std::string ID;
			CHL::Matrix4x4 camerMatrix;
		};

		std::shared_ptr<ChangeCameraMatrix> msg
			(new ChangeCameraMatrix(id, camera));
		GraphicManager::GetInstance().SubmitMessage(msg);
	}
	void SetPrespective(const std::string& id, const CHL::Matrix4x4& prespective)
	{
		class ChangePrespectiveMatrix : public Message
		{
		public:
			ChangePrespectiveMatrix(const std::string& id, const CHL::Matrix4x4& prespective)
			{
				this->ID = id;
				this->prespective = prespective;
			}

			Message::Status Work()
			{
				auto allContinuous = GraphicManager::GetInstance().AllScreenCapture();
				auto iter = allContinuous.find(this->ID);
				if(iter != allContinuous.end())
				{
					std::shared_ptr<BasicScreenCapture> cast = std::dynamic_pointer_cast<BasicScreenCapture>(iter->second);
					if(cast)
					{
						cast->prespectiveMatrix = this->prespective;
					}
				}

				return Message::Status::Complete;
			}

			std::string ID;
			CHL::Matrix4x4 prespective;
		};

		std::shared_ptr<ChangePrespectiveMatrix> msg
			(new ChangePrespectiveMatrix(id, prespective));
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