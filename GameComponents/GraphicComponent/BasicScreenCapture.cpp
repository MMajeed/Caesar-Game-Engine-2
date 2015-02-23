#include "BasicScreenCapture.h"
#include <GenerateGUID.h>
#include "GraphicManager.h"
#include "BasicTexture.h"
#include "Resource.h"

BasicScreenCapture::BasicScreenCapture()
{
}
void BasicScreenCapture::Init()
{
	this->ScreenShot = BasicScreenShot::Spawn(this->width, this->height, this->TextureID.size(), this->cameraID, this->drawSettingsID);
	for(unsigned int i = 0; i < this->TextureID.size(); ++i)
	{
		auto texture = Resource::TextureList.find(this->TextureID[i]);
		if(texture != Resource::TextureList.end())
		{
			texture->second->pTexture = this->ScreenShot->pScreenTexture[i];
		}
	}
}
void BasicScreenCapture::Snap(const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
{
	this->ScreenShot->cameraID = this->cameraID;
	this->ScreenShot->drawSettingsID = this->drawSettingsID;
	this->ScreenShot->Snap(list);
}
std::shared_ptr<ScreenCapture> BasicScreenCapture::clone() const
{
	std::shared_ptr<ScreenCapture> newObject(new BasicScreenCapture(*this));
	newObject->Init();
	return newObject;

}

std::shared_ptr<BasicScreenCapture> BasicScreenCapture::Spawn(const std::vector<std::string>& textureID,
															  unsigned int width,
															  unsigned int height,
															  unsigned int Priority,
															  const std::string& cameraID,
															  const std::string& drawSettingsID)
{
	std::shared_ptr<BasicScreenCapture> newObject(new BasicScreenCapture());

	newObject->TextureID = textureID;
	newObject->width = width;
	newObject->height = height;
	newObject->cameraID = cameraID;
	newObject->drawSettingsID = drawSettingsID;
	newObject->Priority = Priority;

	newObject->Init();

	return newObject;
}