#include "ScreenShotConfig.h"
#include <BasicScreenShot.h>
#include <DepthScreenShot.h>
#include <CubeScreenShot.h>
#include <GraphicManager.h>
#include <GenerateGUID.h>
#include <EntityCommunicator/EntityConfig.h>
#include <BasicTexture.h>

namespace ScreenShotConfig
{
	std::string Basic(unsigned int width,
					  unsigned int height,
					  const CHL::Matrix4x4& cameraMatrix,
					  const CHL::Matrix4x4& prespectiveMatrix)
	{
		class TakeBasicScreenShot : public Message
		{
		public:
			TakeBasicScreenShot(unsigned int width,
								unsigned int height,
								const CHL::Matrix4x4& cameraMatrix,
								const CHL::Matrix4x4& prespectiveMatrix)
			{
				this->camerMatrix = cameraMatrix;
				this->prespectiveMatrix = prespectiveMatrix;
				this->newTextureID = CHL::GenerateGUID();
				this->width = width;
				this->height = height;
			}

			Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				auto allObjects = EntityConfig::GetAllEntity();

				std::shared_ptr<BasicScreenShot> newBasicScreenShot =
					BasicScreenShot::Spawn(CHL::GenerateGUID(), this->width, this->height);
				newBasicScreenShot->D3DInfo.cameraMatrix = this->camerMatrix;
				newBasicScreenShot->D3DInfo.prespectiveMatrix = this->prespectiveMatrix;
				newBasicScreenShot->Snap(allObjects);

				auto texture = newBasicScreenShot->GetScreenTexture();
				std::shared_ptr<BasicTexture> newTexture =
					BasicTexture::Spawn(this->newTextureID, texture);
				GraphicManager::GetInstance().InsertTexture(newTexture);

				newBasicScreenShot->Release();

				return Message::Status::Complete;
			}

			CHL::Matrix4x4 camerMatrix;
			CHL::Matrix4x4 prespectiveMatrix;
			std::string newTextureID;
			unsigned int width;
			unsigned int height;
		};

		std::shared_ptr<TakeBasicScreenShot> msg(new TakeBasicScreenShot(width, height, cameraMatrix, prespectiveMatrix));
		GraphicManager::GetInstance().SubmitMessage(msg);
		msg->WaitTillProcccesed();
		return msg->newTextureID;
	}
	std::string Depth(unsigned int width,
					  unsigned int height,
					  const CHL::Matrix4x4& cameraMatrix,
					  const CHL::Matrix4x4& prespectiveMatrix)
	{
		class TakeDepthScreenShot : public Message
		{
		public:
			TakeDepthScreenShot(unsigned int width,
								unsigned int height,
								const CHL::Matrix4x4& cameraMatrix,
								const CHL::Matrix4x4& prespectiveMatrix)
			{
				this->camerMatrix = cameraMatrix;
				this->prespectiveMatrix = prespectiveMatrix;
				this->newTextureID = CHL::GenerateGUID();
				this->width = width;
				this->height = height;
			}

			Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				auto allObjects = EntityConfig::GetAllEntity();

				std::shared_ptr<DepthScreenShot> newBasicScreenShot =
					DepthScreenShot::Spawn(CHL::GenerateGUID(), this->width, this->height);
				newBasicScreenShot->D3DInfo.cameraMatrix = this->camerMatrix;
				newBasicScreenShot->D3DInfo.prespectiveMatrix = this->prespectiveMatrix;
				newBasicScreenShot->Snap(allObjects);

				auto texture = newBasicScreenShot->GetScreenTexture();
				std::shared_ptr<BasicTexture> newTexture =
					BasicTexture::Spawn(this->newTextureID, texture);
				GraphicManager::GetInstance().InsertTexture(newTexture);

				newBasicScreenShot->Release();

				return Message::Status::Complete;
			}

			CHL::Matrix4x4 camerMatrix;
			CHL::Matrix4x4 prespectiveMatrix;
			std::string newTextureID;
			unsigned int width;
			unsigned int height;
		};

		std::shared_ptr<TakeDepthScreenShot> msg(new TakeDepthScreenShot(width, height, cameraMatrix, prespectiveMatrix));
		GraphicManager::GetInstance().SubmitMessage(msg);
		msg->WaitTillProcccesed();
		return msg->newTextureID;
	}

	std::string Cube(unsigned int width,
					 unsigned int height,
					 const CHL::Vec4& eye)
	{
		class TakeCubeScreenShot : public Message
		{
		public:
			TakeCubeScreenShot(unsigned int width, unsigned int height, const CHL::Vec4& eye)
			{
				this->width = width;
				this->height = height;
				this->eye = eye;
			}

			Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				auto allObjects = EntityConfig::GetAllEntity();

				std::shared_ptr<CubeScreenShot> newBasicScreenShot =
					CubeScreenShot::Spawn(CHL::GenerateGUID(), this->width, this->height);
				newBasicScreenShot->D3DInfo.Eye = this->eye;
				newBasicScreenShot->Snap(allObjects);

				auto texture = newBasicScreenShot->GetScreenTexture();
				std::shared_ptr<BasicTexture> newTexture =
					BasicTexture::Spawn(this->newTextureID, texture);
				GraphicManager::GetInstance().InsertTexture(newTexture);

				newBasicScreenShot->Release();

				return Message::Status::Complete;
			}

			CHL::Vec4 eye;
			std::string newTextureID;
			unsigned int width;
			unsigned int height;
		};

		std::shared_ptr<TakeCubeScreenShot> msg(new TakeCubeScreenShot(width, height, eye));
		GraphicManager::GetInstance().SubmitMessage(msg);
		msg->WaitTillProcccesed();
		return msg->newTextureID;
	}
}