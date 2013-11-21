#include "TakeScreenShot.h"
#include <BasicScreenCapture.h>
#include <DepthScreenCapture.h>
#include <CubeScreenCapture.h>
#include <GraphicManager.h>
#include <GenerateGUID.h>
#include <EntityCommunicator/EntityConfig.h>
#include <BasicTexture.h>

TakeBasicScreenShot::TakeBasicScreenShot(unsigned int width, unsigned int height, const CHL::Matrix4x4& cameraMatrix, const CHL::Matrix4x4& prespectiveMatrix)
{
	this->camerMatrix = cameraMatrix;
	this->prespectiveMatrix = prespectiveMatrix;
	this->newTextureID = CHL::GenerateGUID();
	this->width = width;
	this->height = height;
}

Message::Status TakeBasicScreenShot::Work()
{
	std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);
	
	auto allObjects = EntityConfig::GetAllEntity();

	std::shared_ptr<BasicScreenCapture> newBasicScreenCapture =
		BasicScreenCapture::Spawn(CHL::GenerateGUID(), this->width, this->height);
	newBasicScreenCapture->D3DInfo.cameraMatrix = this->camerMatrix;
	newBasicScreenCapture->D3DInfo.prespectiveMatrix = this->prespectiveMatrix;
	newBasicScreenCapture->Snap(allObjects);

	auto texture = newBasicScreenCapture->GetScreenTexture();
	std::shared_ptr<BasicTexture> newTexture =
		BasicTexture::Spawn(this->newTextureID, texture);
	GraphicManager::GetInstance().InsertTexture(newTexture);

	newBasicScreenCapture->Destory();

	return Message::Status::Complete;
}

// -------------------------------------------------------------------------//
TakeDepthScreenShot::TakeDepthScreenShot(unsigned int width, unsigned int height, const CHL::Matrix4x4& cameraMatrix, const CHL::Matrix4x4& prespectiveMatrix)
{
	this->camerMatrix = cameraMatrix;
	this->prespectiveMatrix = prespectiveMatrix;
	this->newTextureID = CHL::GenerateGUID();
	this->width = width;
	this->height = height;
}

Message::Status TakeDepthScreenShot::Work()
{
	std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

	auto allObjects = EntityConfig::GetAllEntity();

	std::shared_ptr<DepthScreenCapture> newBasicScreenCapture =
		DepthScreenCapture::Spawn(CHL::GenerateGUID(), this->width, this->height);
	newBasicScreenCapture->D3DInfo.cameraMatrix = this->camerMatrix;
	newBasicScreenCapture->D3DInfo.prespectiveMatrix = this->prespectiveMatrix;
	newBasicScreenCapture->Snap(allObjects);

	auto texture = newBasicScreenCapture->GetScreenTexture();
	std::shared_ptr<BasicTexture> newTexture =
		BasicTexture::Spawn(this->newTextureID, texture);
	GraphicManager::GetInstance().InsertTexture(newTexture);

	newBasicScreenCapture->Destory();

	return Message::Status::Complete;
}

// -------------------------------------------------------------------------//
TakeCubeScreenShot::TakeCubeScreenShot(unsigned int width, unsigned int height, const CHL::Vec4& eye)
{
	this->width = width;
	this->height = height;
	this->eye = eye;
}

Message::Status TakeCubeScreenShot::Work()
{
	std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

	auto allObjects = EntityConfig::GetAllEntity();

	std::shared_ptr<CubeScreenCapture> newBasicScreenCapture =
		CubeScreenCapture::Spawn(CHL::GenerateGUID(), this->width, this->height);
	newBasicScreenCapture->D3DInfo.Eye = this->eye;
	newBasicScreenCapture->Snap(allObjects);

	auto texture = newBasicScreenCapture->GetScreenTexture();
	std::shared_ptr<BasicTexture> newTexture =
		BasicTexture::Spawn(this->newTextureID, texture);
	GraphicManager::GetInstance().InsertTexture(newTexture);

	newBasicScreenCapture->Destory();

	return Message::Status::Complete;
}