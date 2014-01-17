#include "LuaLoopCall.h"
#include "LuaError.h"
#include <Logger.h>

LuaLoopCall::LuaLoopCall(double inputMilliseconds, luabind::object inputFunction)
{
	this->milliseconds = inputMilliseconds;
	this->function = inputFunction;
	this->timeSinceLastCall = 0.0;
}

void LuaLoopCall::Update(double realTime, double deltaTime)
{
	this->timeSinceLastCall += (realTime * 1000);
}
void LuaLoopCall::Action(lua_State *lua)
{
	if(this->timeSinceLastCall >= this->milliseconds)
	{
		try
		{
			luabind::call_function<void>(this->function, this->timeSinceLastCall, this->ID);
		}
		catch (...)
		{
			Logger::LogError(LuaError::GetLuaError(lua));
		}
		this->timeSinceLastCall = 0.0;
	}
}