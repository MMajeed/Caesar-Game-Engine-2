#include "ScreenShotConfig.h"
#include <BasicScreenShot.h>
#include <DepthScreenShot.h>
#include <CubeScreenShot.h>
#include <GraphicManager.h>
#include <GenerateGUID.h>
#include <BasicTexture.h>
#include <ResourceManager.h>
#include <D3DX11tex.h>

namespace ScreenShotConfig
{
	std::string Basic(unsigned int width,
					  unsigned int height,
					  const std::string& cameraID)
	{
		class TakeBasicScreenShot : public Message
		{
		public:
			TakeBasicScreenShot(unsigned int width,
								unsigned int height,
								const std::string& cameraID)
			{
				this->cameraID = cameraID;
				this->newTextureID = CHL::GenerateGUID();
				this->width = width;
				this->height = height;
			}

			Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				std::shared_ptr<BasicScreenShot> newBasicScreenShot =
					BasicScreenShot::Spawn(this->width, this->height, this->cameraID);
				newBasicScreenShot->Snap();

				auto texture = newBasicScreenShot->pScreenTexture;
				std::shared_ptr<BasicTexture> newTexture =
					BasicTexture::Spawn(texture);
				ResourceManager::TextureList.Insert(this->newTextureID, newTexture);
				
				return Message::Status::Complete;
			}

			std::string newTextureID;
			unsigned int width;
			unsigned int height;
			std::string cameraID;
		};

		std::shared_ptr<TakeBasicScreenShot> msg(new TakeBasicScreenShot(width, height, cameraID));
		GraphicManager::GetInstance().SubmitMessage(msg);
		return msg->newTextureID;
	}

	std::string Depth(unsigned int width,
					  unsigned int height,
					  const std::string& cameraID)
	{
		class TakeDepthScreenShot : public Message
		{
		public:
			TakeDepthScreenShot(unsigned int width,
								unsigned int height,
								const std::string& cameraID)
			{
				this->cameraID = cameraID;
				this->newTextureID = CHL::GenerateGUID();
				this->width = width;
				this->height = height;
			}

			Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				std::shared_ptr<DepthScreenShot> newBasicScreenShot =
					DepthScreenShot::Spawn(this->width, this->height, this->cameraID);
				newBasicScreenShot->Snap();

				auto texture = newBasicScreenShot->pScreenTexture;
				std::shared_ptr<BasicTexture> newTexture =
					BasicTexture::Spawn(texture);
				ResourceManager::TextureList.Insert(this->newTextureID, newTexture);

				return Message::Status::Complete;
			}

			unsigned int width;
			unsigned int height;
			std::string newTextureID;
			std::string cameraID;
		};

		std::shared_ptr<TakeDepthScreenShot> msg(new TakeDepthScreenShot(width, height, cameraID));
		GraphicManager::GetInstance().SubmitMessage(msg);
		return msg->newTextureID;
	}

	std::string Cube(unsigned int width,
					 unsigned int height,
					 const std::string& cameraID)
	{
		class TakeCubeScreenShot : public Message
		{
		public:
			TakeCubeScreenShot(unsigned int width, unsigned int height, const std::string& cameraID)
			{
				this->width = width;
				this->height = height;
				this->cameraID = cameraID;
			}

			Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				std::shared_ptr<CubeScreenShot> newBasicScreenShot =
					CubeScreenShot::Spawn(this->width, this->height, this->cameraID);
				newBasicScreenShot->Snap();

				auto texture = newBasicScreenShot->pScreenTexture;
				std::shared_ptr<BasicTexture> newTexture =
					BasicTexture::Spawn(texture);
				ResourceManager::TextureList.Insert(this->newTextureID, newTexture);

				return Message::Status::Complete;
			}

			unsigned int width;
			unsigned int height;
			std::string newTextureID;
			std::string cameraID;
		};

		std::shared_ptr<TakeCubeScreenShot> msg(new TakeCubeScreenShot(width, height, cameraID));
		GraphicManager::GetInstance().SubmitMessage(msg);
		return msg->newTextureID;
	}
}