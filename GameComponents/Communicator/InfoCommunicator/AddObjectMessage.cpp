#include "AddObjectMessage.h"
#include <InfoManager.h>

AddObjectMessage::AddObjectMessage(SP_INFO info)
{
	this->infoToAdd = info;
}

Message::Status AddObjectMessage::Work()
{
	std::lock_guard<std::mutex> lock(InfoManager::GetInstance().mutex);
	InfoManager::GetInstance().objects[this->infoToAdd->ID] = this->infoToAdd;

	return Message::Status::Complete;
}