#include "CubeScreenCapture.h"
#include <GenerateGUID.h>
#include "GraphicManager.h"
#include "BasicTexture.h"
#include "ResourceManager.h"

CubeScreenCapture::CubeScreenCapture()
{
	this->current = 0;
	this->TextureID.resize(1);
}
void CubeScreenCapture::Init()
{
	this->ScreenShot[0] = CubeScreenShot::Spawn(this->width, this->height, this->cameraID);
	this->ScreenShot[1] = CubeScreenShot::Spawn(this->width, this->height, this->cameraID);
}
void CubeScreenCapture::Snap(const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
{
	this->current += 1;
	if(this->current >= 2){ this->current = 0; }

	this->ScreenShot[this->current]->cameraID = this->cameraID;
	this->ScreenShot[this->current]->Snap(list);

	auto texture = ResourceManager::TextureList.Find(this->TextureID[0]);
	if(texture)
	{
		texture->pTexture = this->ScreenShot[this->current]->pScreenTexture[0];
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
															unsigned int Priority,
															const std::string& cameraID)
{
	std::shared_ptr<CubeScreenCapture> newObject(new CubeScreenCapture());

	newObject->TextureID[0] = textureID;
	newObject->width = width;
	newObject->height = height;
	newObject->cameraID = cameraID;
	newObject->Priority = Priority;

	newObject->Init();

	return newObject;
}