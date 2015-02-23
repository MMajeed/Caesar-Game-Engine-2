#include "GraphicModelFactory.h"

#include "GraphicModel.h"
#include "GraphicManager.h"
#include "Resource.h"
#include <GenerateGUID.h>

std::string GraphicModelFactory::Create(std::shared_ptr<CHL::Model> model)
{
	class CreateMessage : public Message
	{
	public:
		CreateMessage(std::shared_ptr<CHL::Model> model)
		{
			this->ID = CHL::GenerateGUID();
			this->model = model;
		}

		virtual Message::Status Work()
		{
			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

			std::shared_ptr<GraphicModel> newObject =
				GraphicModel::Spawn(this->model);

			Resource::GraphicModelList[this->ID] = newObject;

			return Message::Status::Complete;
		}

		std::shared_ptr<CHL::Model> model;

		std::string	ID;
	};

	std::shared_ptr<CHL::Model> modelClone(new CHL::Model(*model));
	std::shared_ptr<CreateMessage> msg(new CreateMessage(modelClone));
	GraphicManager::GetInstance().SubmitMessage(msg);
	return msg->ID;
}
void GraphicModelFactory::Release(std::string ID)
{
	class ReleaseBasicDrawable : public Message
	{
	public:
		std::string ID;
		ReleaseBasicDrawable(std::string ID)
		{
			this->ID = ID;
		}

		virtual Message::Status Work()
		{
			std::lock_guard<std::mutex> lock(GraphicManager::GetInstance().mutex);

			Resource::GraphicModelList.erase(this->ID);

			return Message::Status::Complete;
		}
	};

	std::shared_ptr<ReleaseBasicDrawable> msg
		(new ReleaseBasicDrawable(ID));
	GraphicManager::GetInstance().SubmitMessage(msg);
}