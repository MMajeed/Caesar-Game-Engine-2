#include "BasicScreenCaptureFactory.h"

#include <Components.h>
#include <GenerateGUID.h>
#include "BasicScreenCapture.h"
#include "BasicTexture.h"
#include "Resource.h"

void BasicScreenCaptureFactory::Create(unsigned int width,
									   unsigned int height,
									   unsigned int priority,
									   const std::string& cameraID,
									   const std::string& drawSettingsID,
									   unsigned int numberOfTargets,
									   std::string& ID,
									   std::vector<std::string>& textureID)
{

	ID = CHL::GenerateGUID();
	for(unsigned int i = 0; i < numberOfTargets; ++i)
	{
		textureID.push_back(CHL::GenerateGUID());
	}

	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		for(unsigned int i = 0; i < numberOfTargets; ++i)
		{
			std::shared_ptr<BasicTexture> newTexture = BasicTexture::Spawn();
			Resource::TextureList[textureID[i]] = newTexture;
		}

		std::shared_ptr<BasicScreenCapture> newBasicScreenShot =
			BasicScreenCapture::Spawn(textureID, width, height, priority, cameraID, drawSettingsID);
		Resource::ScreenCaptureList[ID] = newBasicScreenShot;


		return Message::Status::Complete;
	});
}
void BasicScreenCaptureFactory::SetCameraID(const std::string& id, const std::string& cameraid)
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		auto screenCapture = Resource::ScreenCaptureList.find(id);
		if(screenCapture != Resource::ScreenCaptureList.end())
		{
			std::shared_ptr<BasicScreenCapture> cast = std::dynamic_pointer_cast<BasicScreenCapture>(screenCapture->second);
			if(cast)
			{
				cast->cameraID = cameraid;
			}
		}

		return Message::Status::Complete;
	});
}
void BasicScreenCaptureFactory::SetDrawSettingsID(const std::string& id, const std::string& dsID)
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		auto screenCapture = Resource::ScreenCaptureList.find(id);
		if(screenCapture != Resource::ScreenCaptureList.end())
		{
			std::shared_ptr<BasicScreenCapture> cast = std::dynamic_pointer_cast<BasicScreenCapture>(screenCapture->second);
			if(cast)
			{
				cast->drawSettingsID = dsID;
			}
		}

		return Message::Status::Complete;
	});
}
void BasicScreenCaptureFactory::SetPriority(const std::string& id, int p)
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		auto screenCapture = Resource::ScreenCaptureList.find(id);
		if(screenCapture != Resource::ScreenCaptureList.end())
		{
			std::shared_ptr<BasicScreenCapture> cast = std::dynamic_pointer_cast<BasicScreenCapture>(screenCapture->second);
			if(cast)
			{
				cast->Priority = p;
			}
		}

		return Message::Status::Complete;
	});
}
void BasicScreenCaptureFactory::Release(std::string ID)
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		Resource::ScreenCaptureList.erase(ID);

		return Message::Status::Complete;
	});
}