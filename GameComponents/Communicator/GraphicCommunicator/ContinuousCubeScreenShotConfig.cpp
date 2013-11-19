#include "ContinuousCubeScreenShotConfig.h"
#include <GenerateGUID.h>
#include <GraphicManager.h>
#include <ContinuousCubeScreenShot.h>
#include <BasicTexture.h>

ContinuousCubeScreenShotConfig::AddContinuousCubeScreenShot::AddContinuousCubeScreenShot
(unsigned int width, unsigned int height, const CHL::Vec4& eye)
{
	this->width = width;
	this->height = height;
	this->eye = eye;
	this->newTextureID = CHL::GenerateGUID();
	this->ID = CHL::GenerateGUID();
}

Message::Status ContinuousCubeScreenShotConfig::AddContinuousCubeScreenShot::Work()
{
	std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

	std::shared_ptr<BasicTexture> newTexture =
		BasicTexture::Spawn(this->newTextureID);
	GraphicManager::GetInstance().InsertTexture(newTexture);

	std::shared_ptr<ContinuousCubeScreenShot> newCubeScreenCapture =
		ContinuousCubeScreenShot::Spawn(this->ID, this->newTextureID, this->width, this->height, this->eye);
	GraphicManager::GetInstance().InsertContinuousScreenCapture(newCubeScreenCapture);

	return Message::Status::Complete;
}

//-----------------------------------------------------------------------//
ContinuousCubeScreenShotConfig::ChangeEye::ChangeEye(const std::string& id, const CHL::Vec4& eye)
{
	this->ID = id;
	this->eye = eye;
}

Message::Status ContinuousCubeScreenShotConfig::ChangeEye::Work()
{
	auto allContinuous = GraphicManager::GetInstance().AllContinuousScreenCapture();
	auto iter = allContinuous.find(this->ID);
	if(iter != allContinuous.end())
	{
		std::shared_ptr<ContinuousCubeScreenShot> cast = std::dynamic_pointer_cast<ContinuousCubeScreenShot>(iter->second);
		if(cast)
		{
			cast->eye = this->eye;
		}
	}

	return Message::Status::Complete;
}