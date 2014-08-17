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
	this->ScreenShot[0] = BasicScreenShot::Spawn(this->width, this->height, this->numberOfTargets, this->cameraID);
	this->ScreenShot[1] = BasicScreenShot::Spawn(this->width, this->height, this->numberOfTargets, this->cameraID);
}
void BasicScreenCapture::Snap(const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list)
{
	this->current += 1;
	if(this->current >= 2){ this->current = 0; }

	this->ScreenShot[this->current]->cameraID = this->cameraID;
	this->ScreenShot[this->current]->Snap(list);

	for(unsigned int i = 0; i < this->numberOfTargets; ++i)
	{
		auto texture = ResourceManager::TextureList.Find(this->TextureID[i]);
		if(texture)
		{
			texture->pTexture = this->ScreenShot[this->current]->pScreenTexture[i];
		}
	}
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
															  unsigned int numberOfTargets,
															  unsigned int Priority,
															  const std::string& cameraID)
{
	std::shared_ptr<BasicScreenCapture> newObject(new BasicScreenCapture());

	if(textureID.size() != numberOfTargets){ Logger::LogError("Error, the number of textures sent to basic screen capture did not match the number of targets"); }

	newObject->TextureID = textureID;
	newObject->width = width;
	newObject->height = height;
	newObject->cameraID = cameraID;
	newObject->numberOfTargets = numberOfTargets;
	newObject->Priority = Priority;

	newObject->Init();

	return newObject;
}