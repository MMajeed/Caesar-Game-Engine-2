#include "ScreenShotFactory.h"

#include <Components.h>
#include "BasicScreenShot.h"
#include "DepthScreenShot.h"
#include "CubeScreenShot.h"
#include "GenerateGUID.h"
#include "BasicTexture.h"
#include "Resource.h"
#include "D3DX11tex.h"

std::vector<std::string> ScreenShotFactory::Basic(unsigned int width,
												  unsigned int height,
												  unsigned int numberOfTargets,
												  const std::string& cameraID,
												  const std::string& drawSettingsID)
{
	std::vector<std::string> newTextureID;
	for(unsigned int i = 0; i < numberOfTargets; ++i)
	{
		newTextureID.push_back(CHL::GenerateGUID());
	}

	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		std::shared_ptr<BasicScreenShot> newBasicScreenShot =
			BasicScreenShot::Spawn(width, height, numberOfTargets, cameraID, drawSettingsID);
		newBasicScreenShot->Snap();

		for(unsigned int i = 0; i < numberOfTargets; ++i)
		{
			auto texture = newBasicScreenShot->pScreenTexture[i];
			std::shared_ptr<BasicTexture> newTexture = BasicTexture::Spawn(texture);
			Resource::TextureList[newTextureID[i]] = newTexture;
		}

		return Message::Status::Complete;
	});

	return newTextureID;
}
std::string ScreenShotFactory::Depth(unsigned int width,
									 unsigned int height,
									 const std::string& cameraID,
									 const std::string& drawSettingsID)
{
	std::string ID = CHL::GenerateGUID();

	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		std::shared_ptr<DepthScreenShot> newBasicScreenShot =
			DepthScreenShot::Spawn(width, height, cameraID, drawSettingsID);
		newBasicScreenShot->Snap();

		auto texture = newBasicScreenShot->pScreenTexture[0];
		std::shared_ptr<BasicTexture> newTexture =
			BasicTexture::Spawn(texture);
		Resource::TextureList[ID] = newTexture;

		return Message::Status::Complete;
	});

	return ID;
}
std::string ScreenShotFactory::Cube(unsigned int width,
									unsigned int height,
									const std::string& cameraID,
									const std::string& drawSettingsID)
{
	std::string ID = CHL::GenerateGUID();

	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		std::shared_ptr<CubeScreenShot> newBasicScreenShot =
			CubeScreenShot::Spawn(width, height, cameraID, drawSettingsID);
		newBasicScreenShot->Snap();

		auto texture = newBasicScreenShot->pScreenTexture[0];
		std::shared_ptr<BasicTexture> newTexture =
			BasicTexture::Spawn(texture);
		Resource::TextureList[ID] = newTexture;

		return Message::Status::Complete;
	});

	return ID;
}