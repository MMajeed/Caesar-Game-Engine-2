#include "DepthScreenCapture.h"
#include <GenerateGUID.h>
#include "GraphicManager.h"
#include "BasicTexture.h"
#include "Resource.h"

DepthScreenCapture::DepthScreenCapture()
{
	this->TextureID.resize(1);
}
void DepthScreenCapture::Init()
{
	this->ScreenShot = DepthScreenShot::Spawn(this->width, this->height, this->cameraID, this->drawSettingsID);
}
void DepthScreenCapture::Snap(const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
{
	this->ScreenShot->cameraID = this->cameraID;
	this->ScreenShot->drawSettingsID = this->drawSettingsID;
	this->ScreenShot->Snap(list);

	auto texture = Resource::TextureList.find(this->TextureID[0]);
	if(texture != Resource::TextureList.end())
	{
		texture->second->pTexture = this->ScreenShot->pScreenTexture[0];
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
															  unsigned int Priority,
															  const std::string& CameraID,
															  const std::string& drawSettingsID)
{
	std::shared_ptr<DepthScreenCapture> newObject(new DepthScreenCapture());

	newObject->TextureID[0] = textureID;
	newObject->width = width;
	newObject->height = height;
	newObject->cameraID = CameraID;
	newObject->drawSettingsID = drawSettingsID;
	newObject->Priority = Priority;

	newObject->Init();

	return newObject;
}