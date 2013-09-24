#include "UpdateObjectMessage.h"

#include "ObjectManager.h"

UpdateObjectMessage::UpdateObjectMessage(const std::string& inputObjectID, const std::string& inputInfoID, const std::string& inputInfo )
{
	this->objectID = inputObjectID;
	this->infoID = inputInfoID;
	this->info = inputInfo;
}
Message::Status UpdateObjectMessage::Work()
{
	boost::mutex::scoped_lock lock(ObjectManager::GetInstance().mutex);

	ObjectManager::GetInstance().UpdateObject(this->objectID, this->infoID, this->info);

	return Message::Status::Complete;
}