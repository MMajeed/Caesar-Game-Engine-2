#include "BasicScreenCapture.h"
#include <GenerateGUID.h>
#include "GraphicManager.h"
#include "BasicTexture.h"
#include "ResourceManager.h"

BasicScreenCapture::BasicScreenCapture()
{
	this->current = 0;
}
void BasicScreenCapture::Init()
{
	this->ScreenShot[0] = BasicScreenShot::Spawn(this->width, this->height, this->cameraID);
	this->ScreenShot[1] = BasicScreenShot::Spawn(this->width, this->height, this->cameraID);
}
void BasicScreenCapture::Destory()
{
	this->ScreenShot[0]->Release();
	this->ScreenShot[1]->Release();
	auto& texture = ResourceManager::TextureList.Find(this->TextureID);
	if(texture)
	{
		texture->Destory();
	}
}
void BasicScreenCapture::Update(double realTime, double deltaTime)
{

}
void BasicScreenCapture::Snap(std::hash_map<std::string, SP_INFO>& objects)
{
	this->current += 1;
	if(this->current >= 2){ this->current = 0; }

	this->ScreenShot[this->current]->D3DInfo.cameraID = this->cameraID;
	this->ScreenShot[this->current]->Snap(objects);

	auto texture = ResourceManager::TextureList.Find(this->TextureID);
	if(texture)
	{
		auto basicTexture = std::dynamic_pointer_cast<BasicTexture>(texture);
		if(basicTexture != 0)
		{
			basicTexture->D3DInfo.pTexture = this->ScreenShot[this->current]->pScreenTexture;
		}
	}
}
std::shared_ptr<ScreenCapture> BasicScreenCapture::clone() const
{
	std::shared_ptr<ScreenCapture> newObject(new BasicScreenCapture(*this));
	newObject->Init();
	return newObject;

}

std::shared_ptr<BasicScreenCapture> BasicScreenCapture::Spawn(const std::string& textureID,
															  unsigned int width,
															  unsigned int height,
															  std::string CameraID)
{
	std::shared_ptr<BasicScreenCapture> newObject(new BasicScreenCapture());

	newObject->TextureID = textureID;
	newObject->width = width;
	newObject->height = height;
	newObject->cameraID = CameraID;

	newObject->Init();

	return newObject;
}