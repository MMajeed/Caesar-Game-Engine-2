#include "ScriptAnimation.h"

#include <ScriptManager.h>
#include <ProcessMessage.h>
#include <ActivateScriptComponent.h>

#include "LuaAnimationObject.h"

ScriptAnimation::ScriptAnimation()
{
	std::shared_ptr<ActivateScriptComponent> newScriptComponent(
		new ActivateScriptComponent(ScriptAnimation::Init));

	ProcessMessage::Add(newScriptComponent);
}

void ScriptAnimation::Init(lua_State *lua)
{
	LuaAnimationObject::RegisterAllLuaFunction(lua);
}