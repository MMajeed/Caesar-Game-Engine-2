#include "AddBasicTexture.h"

#include <BasicTexture.h>
#include <GraphicManager.h>

AddBasicTexture::AddBasicTexture(int slot, std::string texture)
{
	this->slot = slot;
	this->TextureFileName = texture;
}

Message::Status AddBasicTexture::Work()
{
	boost::mutex::scoped_lock lock(GraphicManager::GetInstance().mutex);

	std::shared_ptr<Texture> newObject =
		BasicTexture::Spawn(this->slot, this->TextureFileName);

	GraphicManager::GetInstance().InsertTexture(newObject);

	this->ID = newObject->ID;

	return Message::Status::Complete;
}