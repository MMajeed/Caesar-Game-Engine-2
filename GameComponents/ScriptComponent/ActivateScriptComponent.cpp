#include "ActivateScriptComponent.h"

ActivateScriptComponent::ActivateScriptComponent(std::function<void(lua_State*)> func)
{
	this->func = func;
}

void ActivateScriptComponent::Update(double realTime, double deltaTime)
{

	this->Delete = true;
}
void ActivateScriptComponent::Action(lua_State *lua)
{
	this->func(lua);
}