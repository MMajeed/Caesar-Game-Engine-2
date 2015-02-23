#include "GraphicModelFactory.h"

#include <Components.h>
#include <GenerateGUID.h>
#include "GraphicModel.h"
#include "Resource.h"

std::string GraphicModelFactory::Create(std::shared_ptr<CHL::Model> model)
{
	std::string ID = CHL::GenerateGUID();

	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		std::shared_ptr<GraphicModel> newObject = GraphicModel::Spawn(model);
		Resource::GraphicModelList[ID] = newObject;

		return Message::Status::Complete;
	});
	
	return ID;
}
void GraphicModelFactory::Release(std::string ID)
{
	Components::Graphic->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Graphic->Mutex());

		Resource::GraphicModelList.erase(ID);

		return Message::Status::Complete;
	});
}