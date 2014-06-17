#include "ScriptEntity.h"

#include <ScriptManager.h>
#include <ProcessMessage.h>
#include <ActivateScriptComponent.h>

#include "LuaCamera.h"
#include "LuaLight.h"
#include "LuaObject.h"

ScriptEntity::ScriptEntity()
{
	std::shared_ptr<ActivateScriptComponent> newScriptComponent(
		new ActivateScriptComponent(ScriptEntity::Init));

	ProcessMessage::Add(newScriptComponent);
}

void ScriptEntity::Init(lua_State *lua)
{
	LuaCamera::RegisterAllLuaFunction(lua);
	LuaLight::RegisterAllLuaFunction(lua);
	LuaObject::RegisterAllLuaFunction(lua);
}