#include "DepthScreenCapture.h"
#include <GenerateGUID.h>
#include "GraphicManager.h"
#include "BasicTexture.h"

DepthScreenCapture::DepthScreenCapture()
{
}
void DepthScreenCapture::Init()
{
	this->ScreenShot = DepthScreenShot::Spawn(this->width, this->height, this->cameraID);
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
	this->ScreenShot->D3DInfo.cameraID = this->cameraID;
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

std::shared_ptr<DepthScreenCapture> DepthScreenCapture::Spawn(const std::string& textureID,
															  unsigned int width,
															  unsigned int height,
															  std::string CameraID)
{
	std::shared_ptr<DepthScreenCapture> newObject(new DepthScreenCapture());

	newObject->TextureID = textureID;
	newObject->width = width;
	newObject->height = height;
	newObject->cameraID = CameraID;

	newObject->Init();

	return newObject;
}