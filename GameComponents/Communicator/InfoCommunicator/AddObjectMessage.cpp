#include "AddObjectMessage.h"

#include <memory>

#include <Info.h>
#include <InfoManager.h>
#include <Keys.h>

AddObjectMessage::AddObjectMessage(const std::hash_map<std::string, std::shared_ptr<Object>>& info)
{
	this->messageInfo = info;
}
Message::Status AddObjectMessage::Work()
{
	Info obj(this->messageInfo);

	std::shared_ptr<Object> idObj;
	obj.Retrieve(Keys::ID, idObj);
	this->ID = GenericObject<std::string>::GetValue(idObj);

	{
		std::lock_guard<std::mutex> lock(InfoManager::GetInstance().mutex);
		InfoManager::GetInstance().Insert(obj);
	}

	return Message::Status::Complete;
}