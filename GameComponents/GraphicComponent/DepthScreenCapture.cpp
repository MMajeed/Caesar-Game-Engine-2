#include "DepthScreenCapture.h"
#include <GenerateGUID.h>
#include "GraphicManager.h"
#include "BasicTexture.h"
#include "ResourceManager.h"

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
	auto& texture = ResourceManager::TextureList.Find(this->TextureID);
	if(texture)
	{
		texture->Destory();
	}
}
void DepthScreenCapture::Update(double realTime, double deltaTime)
{

}
void DepthScreenCapture::Snap(std::hash_map<std::string, SP_INFO>& objects)
{
	this->ScreenShot->D3DInfo.cameraID = this->cameraID;
	this->ScreenShot->Snap(objects);

	auto texture = ResourceManager::TextureList.Find(this->TextureID);
	if(texture)
	{
		auto basicTexture = std::dynamic_pointer_cast<BasicTexture>(texture);
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