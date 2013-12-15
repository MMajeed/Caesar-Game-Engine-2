#include "BasicScreenCaptureConfig.h"
#include <GenerateGUID.h>
#include <GraphicManager.h>
#include <BasicScreenCapture.h>
#include <BasicTexture.h>

BasicScreenCaptureConfig::AddBasicScreenCapture::AddBasicScreenCapture
	(unsigned int width, unsigned int height, const CHL::Matrix4x4& cameraMatrix, const CHL::Matrix4x4& prespectiveMatrix)
{
	this->width = width;
	this->height = height;
	this->camerMatrix = cameraMatrix;
	this->prespectiveMatrix = prespectiveMatrix;
	this->newTextureID = CHL::GenerateGUID();
	this->ID = CHL::GenerateGUID();
}

Message::Status BasicScreenCaptureConfig::AddBasicScreenCapture::Work()
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

//-----------------------------------------------------------------------//
BasicScreenCaptureConfig::ChangeCameraMatrix::ChangeCameraMatrix(const std::string& id, const CHL::Matrix4x4& camera)
{
	this->ID = id;
	this->camerMatrix = camera;
}

Message::Status BasicScreenCaptureConfig::ChangeCameraMatrix::Work()
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

//-----------------------------------------------------------------------//
BasicScreenCaptureConfig::ChangePrespectiveMatrix::ChangePrespectiveMatrix(const std::string& id, const CHL::Matrix4x4& prespective)
{
	this->ID = id;
	this->prespective = prespective;
}

Message::Status BasicScreenCaptureConfig::ChangePrespectiveMatrix::Work()
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