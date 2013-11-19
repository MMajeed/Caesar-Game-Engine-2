#include "ContinuousDepthScreenShotConfig.h"
#include <GenerateGUID.h>
#include <GraphicManager.h>
#include <ContinuousDepthScreenShot.h>
#include <BasicTexture.h>

ContinuousDepthScreenShotConfig::AddContinuousDepthScreenShot::AddContinuousDepthScreenShot
(unsigned int width, unsigned int height, const CHL::Matrix4x4& cameraMatrix, const CHL::Matrix4x4& prespectiveMatrix)
{
	this->width = width;
	this->height = height;
	this->camerMatrix = cameraMatrix;
	this->prespectiveMatrix = prespectiveMatrix;
	this->newTextureID = CHL::GenerateGUID();
	this->ID = CHL::GenerateGUID();
}

Message::Status ContinuousDepthScreenShotConfig::AddContinuousDepthScreenShot::Work()
{
	std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

	std::shared_ptr<BasicTexture> newTexture =
		BasicTexture::Spawn(this->newTextureID);
	GraphicManager::GetInstance().InsertTexture(newTexture);

	std::shared_ptr<ContinuousDepthScreenShot> newDepthScreenCapture =
		ContinuousDepthScreenShot::Spawn(this->ID, this->newTextureID, this->width, this->height, this->camerMatrix, this->prespectiveMatrix);
	GraphicManager::GetInstance().InsertContinuousScreenCapture(newDepthScreenCapture);

	return Message::Status::Complete;
}

//-----------------------------------------------------------------------//
ContinuousDepthScreenShotConfig::ChangeCameraMatrix::ChangeCameraMatrix(const std::string& id, const CHL::Matrix4x4& camera)
{
	this->ID = id;
	this->camerMatrix = camera;
}

Message::Status ContinuousDepthScreenShotConfig::ChangeCameraMatrix::Work()
{
	auto allContinuous = GraphicManager::GetInstance().AllContinuousScreenCapture();
	auto iter = allContinuous.find(this->ID);
	if(iter != allContinuous.end())
	{
		std::shared_ptr<ContinuousDepthScreenShot> cast = std::dynamic_pointer_cast<ContinuousDepthScreenShot>(iter->second);
		if(cast)
		{
			cast->cameraMatrix = this->camerMatrix;
		}
	}

	return Message::Status::Complete;
}

//-----------------------------------------------------------------------//
ContinuousDepthScreenShotConfig::ChangePrespectiveMatrix::ChangePrespectiveMatrix(const std::string& id, const CHL::Matrix4x4& prespective)
{
	this->ID = id;
	this->prespective = prespective;
}

Message::Status ContinuousDepthScreenShotConfig::ChangePrespectiveMatrix::Work()
{
	auto allContinuous = GraphicManager::GetInstance().AllContinuousScreenCapture();
	auto iter = allContinuous.find(this->ID);
	if(iter != allContinuous.end())
	{
		std::shared_ptr<ContinuousDepthScreenShot> cast = std::dynamic_pointer_cast<ContinuousDepthScreenShot>(iter->second);
		if(cast)
		{
			cast->prespectiveMatrix = this->prespective;
		}
	}

	return Message::Status::Complete;
}