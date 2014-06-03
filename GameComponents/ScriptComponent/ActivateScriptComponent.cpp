#include "ActivateScriptComponent.h"

ActivateScriptComponent::ActivateScriptComponent(std::function<void(lua_State*)> func)
{
	this->func = func;
	this->InfiniteLoop = false;
}

void ActivateScriptComponent::Update(double realTime, double deltaTime)
{

}
void ActivateScriptComponent::Action(lua_State *lua)
{
	this->func(lua);
}