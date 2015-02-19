#include "LuaKeyAction.h"
#include "LuaError.h"
#include <Windows.h>
#include <Logger.h>

LuaKeyAction::LuaKeyAction(InputKeysEnum::KeyCode inputKey, InputKeysEnum::KeyStatus inputWanted, luabind::object inputFunction)
{
	this->key = inputKey;
	this->wanted = inputWanted;
	this->function = inputFunction;
	short state = GetAsyncKeyState(static_cast<int>(this->key));
	if(state < 0)
	{
		this->lastKeyState = InputKeysEnum::KeyStatus::KeyDown;
	}
	else
	{
		this->lastKeyState = InputKeysEnum::KeyStatus::KeyUp;
	}
}

void LuaKeyAction::Action(lua_State *lua)
{
	InputKeysEnum::KeyStatus keyStatus = InputKeysEnum::KeyStatus::KeyDown;

	short state = GetAsyncKeyState(static_cast<int>(key));
	if(state < 0)
	{
		keyStatus = InputKeysEnum::KeyStatus::KeyDown;
	}
	else
	{
		keyStatus = InputKeysEnum::KeyStatus::KeyUp;
	}

	if(this->lastKeyState != keyStatus) // If it has changed
	{
		this->lastKeyState = keyStatus;

		if(this->wanted == this->lastKeyState)
		{
			try
			{
				luabind::call_function<void>(this->function, this->ID);
			}
			catch (...)
			{
				Logger::LogError(LuaError::GetLuaError(lua));
			}
		}
	}
}

void LuaKeyAction::Update(double realTime, double deltaTime)
{

}