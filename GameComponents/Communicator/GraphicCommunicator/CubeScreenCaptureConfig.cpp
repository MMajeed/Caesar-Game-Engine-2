#include "CubeScreenCaptureConfig.h"
#include <GenerateGUID.h>
#include <GraphicManager.h>
#include <CubeScreenCapture.h>
#include <BasicTexture.h>

namespace CubeScreenCaptureConfig
{
	void Create(unsigned int width,
				unsigned int height,
				const CHL::Vec4& eye,
				std::string& ID,
				std::string& textureID)
	{
		class AddCubeScreenCapture : public Message
		{
		public:
			AddCubeScreenCapture(unsigned int width, unsigned int height, const CHL::Vec4& eye)
			{
				this->width = width;
				this->height = height;
				this->eye = eye;
				this->newTextureID = CHL::GenerateGUID();
				this->ID = CHL::GenerateGUID();
			}

			Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				std::shared_ptr<BasicTexture> newTexture =
					BasicTexture::Spawn(this->newTextureID);
				GraphicManager::GetInstance().InsertTexture(newTexture);

				std::shared_ptr<CubeScreenCapture> newCubeScreenShot =
					CubeScreenCapture::Spawn(this->ID, this->newTextureID, this->width, this->height, this->eye);
				GraphicManager::GetInstance().InsertScreenCapture(newCubeScreenShot);

				return Message::Status::Complete;
			}

			CHL::Vec4 eye;
			std::string newTextureID;
			std::string ID;
			unsigned int width;
			unsigned int height;
		};

		std::shared_ptr<AddCubeScreenCapture> msg
			(new AddCubeScreenCapture(width, height, eye));
		GraphicManager::GetInstance().SubmitMessage(msg);
		
		ID = msg->ID;
		textureID = msg->newTextureID;
	}
	void SetEye(const std::string& id, const CHL::Vec4& eye)
	{
		class ChangeEye : public Message
		{
		public:
			ChangeEye(const std::string& id, const CHL::Vec4& eye)
			{
				this->ID = id;
				this->eye = eye;
			}

			Message::Status Work()
			{
				auto allContinuous = GraphicManager::GetInstance().AllScreenCapture();
				auto iter = allContinuous.find(this->ID);
				if(iter != allContinuous.end())
				{
					std::shared_ptr<CubeScreenCapture> cast = std::dynamic_pointer_cast<CubeScreenCapture>(iter->second);
					if(cast)
					{
						cast->eye = this->eye;
					}
				}

				return Message::Status::Complete;
			}
			std::string ID;
			CHL::Vec4 eye;
		};

		std::shared_ptr<ChangeEye> msg
			(new ChangeEye(id, eye));
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