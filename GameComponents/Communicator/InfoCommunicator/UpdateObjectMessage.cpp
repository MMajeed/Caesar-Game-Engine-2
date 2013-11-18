#include "UpdateObjectMessage.h"

#include <InfoManager.h>

UpdateObjectMessage::UpdateObjectMessage(const std::string& objectID, std::shared_ptr<INFO> info)
{
	this->objectID = objectID;
	this->info = info->Clone();
}
Message::Status UpdateObjectMessage::Work()
{
	std::lock_guard<std::mutex> lock(InfoManager::GetInstance().mutex);

	auto iter = InfoManager::GetInstance().objects.find(this->objectID);
	if(iter == InfoManager::GetInstance().objects.end()){ return Message::Status::Unvalid; }

	iter->second = this->info;

	return Message::Status::Complete;
}