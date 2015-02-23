#include "TextureFactory.h"

#include "Resource.h"
#include "BasicTexture.h"
#include <Components.h>
#include <GenerateGUID.h>

std::string TextureFactory::Create(std::string texture)
{
	std::string ID = CHL::GenerateGUID();

	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());
		
		std::shared_ptr<BasicTexture> newObject = BasicTexture::Spawn(texture);
		Resource::TextureList[ID] = newObject;

		return Message::Status::Complete;
	});

	return ID;
}
void TextureFactory::Release(std::string ID)
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		Resource::TextureList.erase(ID);

		return Message::Status::Complete;
	});
}