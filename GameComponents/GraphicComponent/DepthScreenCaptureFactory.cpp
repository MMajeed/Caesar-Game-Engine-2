#include "DepthScreenCaptureFactory.h"

#include <GenerateGUID.h>
#include <Components.h>
#include "Resource.h"
#include "DepthScreenCapture.h"
#include "BasicTexture.h"

void DepthScreenCaptureFactory::Create(unsigned int width,
									   unsigned int height,
									   unsigned int priority,
									   const std::string& cameraID,
									   const std::string& drawSettingsID,
									   std::string& ID,
									   std::string& textureID)
{
	textureID = CHL::GenerateGUID();
	ID = CHL::GenerateGUID();

	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		std::shared_ptr<BasicTexture> newTexture = BasicTexture::Spawn();
		Resource::TextureList[textureID] = newTexture;

		std::shared_ptr<DepthScreenCapture> newDepthScreenShot =
			DepthScreenCapture::Spawn(textureID, width, height, priority, cameraID, drawSettingsID);
		Resource::ScreenCaptureList[ID] = newDepthScreenShot;

		return Message::Status::Complete;
	});
}
void DepthScreenCaptureFactory::SetCameraID(const std::string& id, const std::string& cameraid)
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		auto screenCapture = Resource::ScreenCaptureList.find(id);
		if(screenCapture != Resource::ScreenCaptureList.end())
		{
			std::shared_ptr<DepthScreenCapture> cast = std::dynamic_pointer_cast<DepthScreenCapture>(screenCapture->second);
			if(cast)
			{
				cast->cameraID = cameraid;
			}
		}

		return Message::Status::Complete;
	});
}
void DepthScreenCaptureFactory::SetDrawSettingsID(const std::string& id, const std::string& dsID)
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		auto screenCapture = Resource::ScreenCaptureList.find(id);
		if(screenCapture != Resource::ScreenCaptureList.end())
		{
			std::shared_ptr<DepthScreenCapture> cast = std::dynamic_pointer_cast<DepthScreenCapture>(screenCapture->second);
			if(cast)
			{
				cast->drawSettingsID = dsID;
			}
		}

		return Message::Status::Complete;
	});
}
void DepthScreenCaptureFactory::SetPriority(const std::string& id, int p)
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		auto screenCapture = Resource::ScreenCaptureList.find(id);
		if(screenCapture != Resource::ScreenCaptureList.end())
		{
			std::shared_ptr<DepthScreenCapture> cast = std::dynamic_pointer_cast<DepthScreenCapture>(screenCapture->second);
			if(cast)
			{
				cast->Priority = p;
			}
		}

		return Message::Status::Complete;
	});
}
void DepthScreenCaptureFactory::Release(std::string ID)
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		Resource::ScreenCaptureList.erase(ID);

		return Message::Status::Complete;
	});
}