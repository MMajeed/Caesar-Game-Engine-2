#include "AddBasicTexture.h"

#include <BasicTexture.h>
#include <GraphicManager.h>
#include <Converter.h>
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

AddBasicTexture::AddBasicTexture(int slot, std::string texture)
{
	this->ID = CHL::ToString(boost::uuids::random_generator()());
	this->slot = slot;
	this->TextureFileName = texture;
}

Message::Status AddBasicTexture::Work()
{
	std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

	std::shared_ptr<Texture> newObject =
		BasicTexture::Spawn(this->ID, this->slot, this->TextureFileName);

	GraphicManager::GetInstance().InsertTexture(newObject);

	this->ID = newObject->ID;

	return Message::Status::Complete;
}