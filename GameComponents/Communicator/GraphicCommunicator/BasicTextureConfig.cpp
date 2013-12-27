#include "BasicTextureConfig.h"

#include <BasicTexture.h>
#include <GraphicManager.h>
#include <GenerateGUID.h>

namespace BasicTextureConfig
{
	std::string Create(std::string texture)
	{
		class  AddBasicTexture : public Message
		{
		public:
			AddBasicTexture(std::string texture)
			{
				this->ID = CHL::GenerateGUID();
				this->TextureFileName = texture;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				std::shared_ptr<BasicTexture> newObject =
					BasicTexture::Spawn(this->TextureFileName);

				GraphicManager::GetInstance().InsertTexture(this->ID, newObject);

				return Message::Status::Complete;
			}

			std::string	TextureFileName;
			std::string	ID;
		};

		std::shared_ptr<AddBasicTexture> msg(new AddBasicTexture(texture));
		GraphicManager::GetInstance().SubmitMessage(msg);
		return msg->ID;
	}

	void Release(std::string ID)
	{
		class ReleaseTexture : public Message
		{
		public:
			std::string ID;
			ReleaseTexture(std::string ID)
			{
				this->ID = ID;
			}

			virtual Message::Status Work()
			{
				std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

				GraphicManager::GetInstance().RemoveTexture(this->ID);

				return Message::Status::Complete;
			}
		};

		std::shared_ptr<ReleaseTexture> msg
			(new ReleaseTexture(ID));
		GraphicManager::GetInstance().SubmitMessage(msg);
	}
}