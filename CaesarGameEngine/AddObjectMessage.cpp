#include "AddObjectMessage.h"

#include <memory>

#include "Object.h"
#include "ObjectManager.h"
#include "Keys.h"

AddObjectMessage::AddObjectMessage(CHL::MapQ<std::string, std::string> info)
{
	this->messageInfo = info;
}
Message::Status AddObjectMessage::Work()
{
	std::shared_ptr<Object> obj(new Object(this->messageInfo));
	obj->Retrieve(Keys::ID, this->ID);

	{
		boost::mutex::scoped_lock lock(ObjectManager::GetInstance().mutex);
		ObjectManager::GetInstance().Insert(obj);
	}

	return Message::Status::Complete;
}