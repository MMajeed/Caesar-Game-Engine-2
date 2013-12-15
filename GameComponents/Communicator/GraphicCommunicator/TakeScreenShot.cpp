#include "TakeScreenShot.h"
#include <BasicScreenShot.h>
#include <DepthScreenShot.h>
#include <CubeScreenShot.h>
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