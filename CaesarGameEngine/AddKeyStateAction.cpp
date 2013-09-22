#include "AddKeyStateAction.h"

#include "LuaManager.h"
#include "LuaKeyAction.h"

AddKeyStateAction::AddKeyStateAction(unsigned int inputKey, StateWanted inputState, luabind::object inputFunction)
{
	this->state = inputState;
	this->key = inputKey;
	this->function = inputFunction;
}

Message::Status AddKeyStateAction::Work()
{
	std::shared_ptr<LuaKeyAction> newAction(new LuaKeyAction(this->key, static_cast<LuaKeyAction::KeyStatWanted>(this->state), this->function));

	{
		boost::mutex::scoped_lock lock(LuaManager::GetInstance().mutex);
		LuaManager::GetInstance().SubmitProcesses(newAction);
	}

	this->ID = newAction->ID;

	return Message::Status::Complete;
}