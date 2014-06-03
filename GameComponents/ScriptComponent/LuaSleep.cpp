#include "LuaSleep.h"
#include "LuaError.h"
#include "ProcessMessage.h"
#include <Logger.h>

LuaSleep::LuaSleep(double inputMilliseconds, luabind::object inputFunction)
{
	this->milliseconds = inputMilliseconds;
	this->function = inputFunction;
	this->timeSinceLastCall = 0.0;
	this->InfiniteLoop = false;
}

void LuaSleep::Update(double realTime, double deltaTime)
{
	this->timeSinceLastCall += (realTime * 1000);
}
void LuaSleep::Action(lua_State *lua)
{
	if(this->timeSinceLastCall >= this->milliseconds)
	{
		try
		{
			luabind::call_function<void>(this->function, this->timeSinceLastCall, this->ID);
		}
		catch(...)
		{
			Logger::LogError(LuaError::GetLuaError(lua));
		}
	}
}