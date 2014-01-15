#include "LuaKeyAction.h"
#include "LuaError.h"
#include <InputCommunicator\GetKeyStatus.h>

LuaKeyAction::LuaKeyAction(InputKeysEnum::KeyCode inputKey, InputKeysEnum::KeyStatus inputWanted, luabind::object inputFunction)
{
	this->key = inputKey;
	this->wanted = inputWanted;
	this->function = inputFunction;
	this->lastKeyState = GetKeyStatus::GetKey(this->key);
}

void LuaKeyAction::Action(lua_State *lua)
{
	InputKeysEnum::KeyStatus keyStatus = GetKeyStatus::GetKey(this->key);

	if(this->lastKeyState != keyStatus) // If it has changed
	{
		this->lastKeyState = keyStatus;

		if(this->wanted == this->lastKeyState)
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