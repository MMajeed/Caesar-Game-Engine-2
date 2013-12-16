#include "DepthScreenCapture.h"
#include <GenerateGUID.h>
#include "GraphicManager.h"
#include "BasicTexture.h"

DepthScreenCapture::DepthScreenCapture(const std::string& inputID)
:ScreenCapture(inputID)
{
}
void DepthScreenCapture::Init()
{
	this->ScreenShot = DepthScreenShot::Spawn(CHL::GenerateGUID(), this->width, this->height);
}
void DepthScreenCapture::Destory()
{
	this->ScreenShot->Release();
	auto& allTexture = GraphicManager::GetInstance().AllTexture();
	auto textureIter = allTexture.find(this->TextureID);
	if(textureIter != allTexture.end())
	{
		textureIter->second->Destory();
	}
}
void DepthScreenCapture::Update(double realTime, double deltaTime)
{

}
void DepthScreenCapture::Snap(std::hash_map<std::string, SP_INFO>& objects)
{
	this->ScreenShot->D3DInfo.cameraMatrix = this->cameraMatrix;
	this->ScreenShot->D3DInfo.prespectiveMatrix = this->prespectiveMatrix;
	this->ScreenShot->Snap(objects);

	auto allTexture = GraphicManager::GetInstance().AllTexture();
	auto textureIter = allTexture.find(this->TextureID);
	if(textureIter != allTexture.end())
	{
		auto basicTexture = std::dynamic_pointer_cast<BasicTexture>(textureIter->second);
		if(basicTexture != 0)
		{
			basicTexture->D3DInfo.pTexture = this->ScreenShot->pScreenTexture;
		}
	}
}
std::shared_ptr<ScreenCapture> DepthScreenCapture::clone() const
{
	std::shared_ptr<ScreenCapture> newObject(new DepthScreenCapture(*this));
	newObject->Init();
	return newObject;

}

std::shared_ptr<DepthScreenCapture> DepthScreenCapture::Spawn(const std::string& inputID,
																			const std::string& textureID,
																			unsigned int width,
																			unsigned int height,
																			CHL::Matrix4x4 cameraMatrix,
																			CHL::Matrix4x4 prespectiveMatrix)
{
	std::shared_ptr<DepthScreenCapture> newObject(new DepthScreenCapture(inputID));

	newObject->TextureID = textureID;
	newObject->width = width;
	newObject->height = height;
	newObject->prespectiveMatrix = prespectiveMatrix;
	newObject->cameraMatrix = cameraMatrix;

	newObject->Init();

	return newObject;
}