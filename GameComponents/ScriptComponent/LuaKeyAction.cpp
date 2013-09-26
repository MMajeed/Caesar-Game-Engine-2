#include "LuaKeyAction.h"

#include <InputCommunicator\GetKeyStatus.h>

LuaKeyAction::LuaKeyAction(unsigned int inputKey, LuaKeyAction::KeyStatWanted inputWanted, luabind::object inputFunction)
{
	this->key = inputKey;
	this->wanted = inputWanted;
	this->function = inputFunction;
}

void LuaKeyAction::Action()
{
	GetKeyStatus::Key keyStatus = GetKeyStatus::GetKey(this->key);

	if(this->currentKey != static_cast<LuaKeyAction::KeyStatWanted>(keyStatus.state)) // If it has changed
	{
		this->currentKey = static_cast<LuaKeyAction::KeyStatWanted>(keyStatus.state);

		if(this->wanted == this->currentKey)
		{
			luabind::call_function<void>(this->function);
		}
	}
}

void LuaKeyAction::Update(double realTime, double deltaTime)
{

}