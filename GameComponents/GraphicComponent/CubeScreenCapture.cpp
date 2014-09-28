#include "CubeScreenCapture.h"
#include <GenerateGUID.h>
#include "GraphicManager.h"
#include "BasicTexture.h"
#include "ResourceManager.h"

CubeScreenCapture::CubeScreenCapture()
{
	this->TextureID.resize(1);
	
}
void CubeScreenCapture::Init()
{
	this->ScreenShot = CubeScreenShot::Spawn(this->width, this->height, this->cameraID, this->drawSettingsID);
	auto texture = ResourceManager::TextureList.Find(this->TextureID[0]);
	if(texture)
	{
		texture->pTexture = this->ScreenShot->pScreenTexture[0];
	}
}
void CubeScreenCapture::Snap(const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
{
	this->ScreenShot->cameraID = this->cameraID;
	this->ScreenShot->drawSettingsID = this->drawSettingsID;
	this->ScreenShot->Snap(list);

	
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
															const std::string& cameraID,
															const std::string& drawSettingsID)
{
	std::shared_ptr<CubeScreenCapture> newObject(new CubeScreenCapture());

	newObject->TextureID[0] = textureID;
	newObject->width = width;
	newObject->height = height;
	newObject->cameraID = cameraID;
	newObject->drawSettingsID = drawSettingsID;
	newObject->Priority = Priority;

	newObject->Init();

	return newObject;
}