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
	std::vector<std::string> Basic(unsigned int width,
								   unsigned int height,
								   unsigned int numberOfTargets,
								   const std::string& cameraID,
								   const std::string& drawSettingsID)
	{
		class TakeBasicScreenShot : public Message
		{
		public:
			TakeBasicScreenShot(unsigned int width,
								unsigned int height,
								unsigned int numberOfTargets,
								const std::string& cameraID,
								const std::string& drawSettingsID)
			{
				this->cameraID = cameraID;
				this->drawSettingsID = drawSettingsID;
				this->width = width;
				this->height = height;
				this->numberOfTargets = numberOfTargets;
				for(unsigned int i = 0; i < this->numberOfTargets; ++i)
				{
					this->newTextureID.push_back(CHL::GenerateGUID());
				}
			}

			Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				std::shared_ptr<BasicScreenShot> newBasicScreenShot =
					BasicScreenShot::Spawn(this->width, this->height, this->numberOfTargets, this->cameraID, this->drawSettingsID);
				newBasicScreenShot->Snap();

				for(unsigned int i = 0; i < this->numberOfTargets; ++i)
				{
					auto texture = newBasicScreenShot->pScreenTexture[i];
					std::shared_ptr<BasicTexture> newTexture = BasicTexture::Spawn(texture);
					ResourceManager::TextureList.Insert(this->newTextureID[i], newTexture);
				}
				
				return Message::Status::Complete;
			}

			std::vector<std::string> newTextureID;
			unsigned int width;
			unsigned int height;
			unsigned int numberOfTargets;
			std::string cameraID;
			std::string drawSettingsID;
		};

		std::shared_ptr<TakeBasicScreenShot> msg(new TakeBasicScreenShot(width, height, numberOfTargets, cameraID, drawSettingsID));
		GraphicManager::GetInstance().SubmitMessage(msg);
		return msg->newTextureID;
	}

	std::string Depth(unsigned int width,
					  unsigned int height,
					  const std::string& cameraID,
					  const std::string& drawSettingsID)
	{
		class TakeDepthScreenShot : public Message
		{
		public:
			TakeDepthScreenShot(unsigned int width,
								unsigned int height,
								const std::string& cameraID,
								const std::string& drawSettingsID)
			{
				this->cameraID = cameraID;
				this->drawSettingsID = drawSettingsID;
				this->newTextureID = CHL::GenerateGUID();
				this->width = width;
				this->height = height;
			}

			Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				std::shared_ptr<DepthScreenShot> newBasicScreenShot =
					DepthScreenShot::Spawn(this->width, this->height, this->cameraID, this->drawSettingsID);
				newBasicScreenShot->Snap();

				auto texture = newBasicScreenShot->pScreenTexture[0];
				std::shared_ptr<BasicTexture> newTexture =
					BasicTexture::Spawn(texture);
				ResourceManager::TextureList.Insert(this->newTextureID, newTexture);

				return Message::Status::Complete;
			}

			unsigned int width;
			unsigned int height;
			std::string newTextureID;
			std::string cameraID;
			std::string drawSettingsID;
		};

		std::shared_ptr<TakeDepthScreenShot> msg(new TakeDepthScreenShot(width, height, cameraID, drawSettingsID));
		GraphicManager::GetInstance().SubmitMessage(msg);
		return msg->newTextureID;
	}

	std::string Cube(unsigned int width,
					 unsigned int height,
					 const std::string& cameraID,
					 const std::string& drawSettingsID)
	{
		class TakeCubeScreenShot : public Message
		{
		public:
			TakeCubeScreenShot(unsigned int width, unsigned int height, const std::string& cameraID, const std::string& drawSettingsID)
			{
				this->width = width;
				this->height = height;
				this->cameraID = cameraID;
				this->drawSettingsID = drawSettingsID;
			}

			Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				std::shared_ptr<CubeScreenShot> newBasicScreenShot =
					CubeScreenShot::Spawn(this->width, this->height, this->cameraID, this->drawSettingsID);
				newBasicScreenShot->Snap();

				auto texture = newBasicScreenShot->pScreenTexture[0];
				std::shared_ptr<BasicTexture> newTexture =
					BasicTexture::Spawn(texture);
				ResourceManager::TextureList.Insert(this->newTextureID, newTexture);

				return Message::Status::Complete;
			}

			unsigned int width;
			unsigned int height;
			std::string newTextureID;
			std::string cameraID;
			std::string drawSettingsID;
		};

		std::shared_ptr<TakeCubeScreenShot> msg(new TakeCubeScreenShot(width, height, cameraID, drawSettingsID));
		GraphicManager::GetInstance().SubmitMessage(msg);
		return msg->newTextureID;
	}
}