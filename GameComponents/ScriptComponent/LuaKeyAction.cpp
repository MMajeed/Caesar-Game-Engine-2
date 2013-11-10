#include "LuaKeyAction.h"
#include "LuaError.h"
#include <InputCommunicator\GetKeyStatus.h>

LuaKeyAction::LuaKeyAction(unsigned int inputKey, LuaKeyAction::KeyStatWanted inputWanted, luabind::object inputFunction)
{
	this->key = inputKey;
	this->wanted = inputWanted;
	this->function = inputFunction;
}

void LuaKeyAction::Action(lua_State *lua)
{
	GetKeyStatus::Key keyStatus = GetKeyStatus::GetKey(this->key);

	if(this->currentKey != static_cast<LuaKeyAction::KeyStatWanted>(keyStatus.state)) // If it has changed
	{
		this->currentKey = static_cast<LuaKeyAction::KeyStatWanted>(keyStatus.state);

		if(this->wanted == this->currentKey)
		{
			try
			{
				luabind::call_function<void>(this->function);
			}
			catch (...)
			{
				throw LuaError(lua);
			}
		}
	}
}

void LuaKeyAction::Update(double realTime, double deltaTime)
{

}