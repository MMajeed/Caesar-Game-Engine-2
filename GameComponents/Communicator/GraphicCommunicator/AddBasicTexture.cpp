#include "AddBasicTexture.h"

#include <BasicTexture.h>
#include <GraphicManager.h>
#include <GenerateGUID.h>

AddBasicTexture::AddBasicTexture(std::string texture)
{
	this->ID = CHL::GenerateGUID();
	this->TextureFileName = texture;
}

Message::Status AddBasicTexture::Work()
{
	std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

	std::shared_ptr<BasicTexture> newObject =
		BasicTexture::Spawn(this->ID, this->TextureFileName);

	GraphicManager::GetInstance().InsertTexture(newObject);

	this->ID = newObject->ID;

	return Message::Status::Complete;
}