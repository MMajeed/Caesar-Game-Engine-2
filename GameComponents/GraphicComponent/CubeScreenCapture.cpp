#include "CubeScreenCapture.h"
#include <GenerateGUID.h>
#include "GraphicManager.h"
#include "BasicTexture.h"
#include "ResourceManager.h"

CubeScreenCapture::CubeScreenCapture()
{
	this->current = 0;
}
void CubeScreenCapture::Init()
{
	this->ScreenShot[0] = CubeScreenShot::Spawn(this->width, this->height, this->cameraID);
	this->ScreenShot[1] = CubeScreenShot::Spawn(this->width, this->height, this->cameraID);
}
void CubeScreenCapture::Destory()
{
	this->ScreenShot[0]->Release();
	this->ScreenShot[1]->Release();
	auto texture = ResourceManager::TextureList.Find(this->TextureID);
	if(texture)
	{
		texture->Destory();
	}
}
void CubeScreenCapture::Update(double realTime, double deltaTime)
{

}
void CubeScreenCapture::Snap(std::hash_map<std::string, SP_INFO>& objects)
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
std::shared_ptr<ScreenCapture> CubeScreenCapture::clone() const
{
	std::shared_ptr<ScreenCapture> newObject(new CubeScreenCapture(*this));
	newObject->Init();
	return newObject;

}

std::shared_ptr<CubeScreenCapture> CubeScreenCapture::Spawn(const std::string& textureID,
															unsigned int width,
															unsigned int height,
															const std::string& cameraID)
{
	std::shared_ptr<CubeScreenCapture> newObject(new CubeScreenCapture());

	newObject->TextureID = textureID;
	newObject->width = width;
	newObject->height = height;
	newObject->cameraID = cameraID;

	newObject->Init();

	return newObject;
}