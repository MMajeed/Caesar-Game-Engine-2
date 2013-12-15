#include "CubeScreenCaptureConfig.h"
#include <GenerateGUID.h>
#include <GraphicManager.h>
#include <CubeScreenCapture.h>
#include <BasicTexture.h>

CubeScreenCaptureConfig::AddCubeScreenCapture::AddCubeScreenCapture
(unsigned int width, unsigned int height, const CHL::Vec4& eye)
{
	this->width = width;
	this->height = height;
	this->eye = eye;
	this->newTextureID = CHL::GenerateGUID();
	this->ID = CHL::GenerateGUID();
}

Message::Status CubeScreenCaptureConfig::AddCubeScreenCapture::Work()
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

//-----------------------------------------------------------------------//
CubeScreenCaptureConfig::ChangeEye::ChangeEye(const std::string& id, const CHL::Vec4& eye)
{
	this->ID = id;
	this->eye = eye;
}

Message::Status CubeScreenCaptureConfig::ChangeEye::Work()
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