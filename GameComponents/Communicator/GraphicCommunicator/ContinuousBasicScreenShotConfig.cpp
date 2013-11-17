#include "ContinuousBasicScreenShotConfig.h"
#include <Converter.h>
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <GraphicManager.h>
#include <ContinuousBasicScreenShot.h>
#include <BasicTexture.h>

ContinuousBasicScreenShotConfig::AddContinuousBasicScreenShot::AddContinuousBasicScreenShot
	(unsigned int width, unsigned int height, const CHL::Matrix4x4& cameraMatrix, const CHL::Matrix4x4& prespectiveMatrix)
{
	this->width = width;
	this->height = height;
	this->camerMatrix = cameraMatrix;
	this->prespectiveMatrix = prespectiveMatrix;
	this->newTextureID = CHL::ToString(boost::uuids::random_generator()());
	this->ID = CHL::ToString(boost::uuids::random_generator()());
}

Message::Status ContinuousBasicScreenShotConfig::AddContinuousBasicScreenShot::Work()
{
	std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

	std::shared_ptr<BasicTexture> newTexture =
		BasicTexture::Spawn(this->newTextureID);
	GraphicManager::GetInstance().InsertTexture(newTexture);

	std::shared_ptr<ContinuousBasicScreenShot> newBasicScreenCapture =
		ContinuousBasicScreenShot::Spawn(this->ID, this->newTextureID, this->width, this->height, this->camerMatrix, this->prespectiveMatrix);
	GraphicManager::GetInstance().InsertContinuousScreenCapture(newBasicScreenCapture);

	return Message::Status::Complete;
}

//-----------------------------------------------------------------------//
ContinuousBasicScreenShotConfig::ChangeCameraMatrix::ChangeCameraMatrix(const std::string& id, const CHL::Matrix4x4& camera)
{
	this->ID = id;
	this->camerMatrix = camera;
}

Message::Status ContinuousBasicScreenShotConfig::ChangeCameraMatrix::Work()
{
	auto allContinuous = GraphicManager::GetInstance().AllContinuousScreenCapture();
	auto iter = allContinuous.find(this->ID);
	if(iter != allContinuous.end())
	{
		std::shared_ptr<ContinuousBasicScreenShot> cast = std::dynamic_pointer_cast<ContinuousBasicScreenShot>(iter->second);
		if(cast)
		{
			cast->cameraMatrix = this->camerMatrix;
		}
	}

	return Message::Status::Complete;
}

//-----------------------------------------------------------------------//
ContinuousBasicScreenShotConfig::ChangePrespectiveMatrix::ChangePrespectiveMatrix(const std::string& id, const CHL::Matrix4x4& prespective)
{
	this->ID = id;
	this->prespective = prespective;
}

Message::Status ContinuousBasicScreenShotConfig::ChangePrespectiveMatrix::Work()
{
	auto allContinuous = GraphicManager::GetInstance().AllContinuousScreenCapture();
	auto iter = allContinuous.find(this->ID);
	if(iter != allContinuous.end())
	{
		std::shared_ptr<ContinuousBasicScreenShot> cast = std::dynamic_pointer_cast<ContinuousBasicScreenShot>(iter->second);
		if(cast)
		{
			cast->prespectiveMatrix = this->prespective;
		}
	}

	return Message::Status::Complete;
}