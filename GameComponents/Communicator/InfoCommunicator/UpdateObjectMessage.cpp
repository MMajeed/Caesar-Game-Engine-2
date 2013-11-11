#include "UpdateObjectMessage.h"

#include <InfoManager.h>

UpdateObjectMessage::UpdateObjectMessage(const std::string& inputObjectID, const std::string& inputInfoID,  std::shared_ptr<Object> inputInfo )
{
	this->objectID = inputObjectID;
	this->infoID = inputInfoID;
	this->info = inputInfo;
}
Message::Status UpdateObjectMessage::Work()
{
	std::lock_guard<std::mutex> lock(InfoManager::GetInstance().mutex);

	InfoManager::GetInstance().UpdateObject(this->objectID, this->infoID, this->info);

	return Message::Status::Complete;
}

DeleteInfoMessgae::DeleteInfoMessgae(const std::string& inputObjectID, const std::string& inputInfoID)
{
	this->objectID = inputObjectID;
	this->infoID = inputInfoID;
}
Message::Status DeleteInfoMessgae::Work()
{
	std::lock_guard<std::mutex> lock(InfoManager::GetInstance().mutex);

	InfoManager::GetInstance().DeleteInfo(this->objectID, this->infoID);

	return Message::Status::Complete;
}