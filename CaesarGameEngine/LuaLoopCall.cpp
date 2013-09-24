#include "LuaLoopCall.h"

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
void LuaLoopCall::Action()
{
	if(this->timeSinceLastCall >= this->milliseconds)
	{
		luabind::call_function<void>(this->function);
		this->timeSinceLastCall = 0.0;
	}
}