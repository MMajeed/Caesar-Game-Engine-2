#include "ScriptEntity.h"

#include <ScriptManager.h>
#include <ProcessMessage.h>
#include <ActivateScriptComponent.h>

#include "LuaCamera.h"
#include "LuaObject.h"
#include "LuaDrawSettings.h"

ScriptEntity::ScriptEntity()
{
	std::shared_ptr<ActivateScriptComponent> newScriptComponent(
		new ActivateScriptComponent(ScriptEntity::Init));

	ProcessMessage::Add(newScriptComponent);
}

void ScriptEntity::Init(lua_State *lua)
{
	LuaCamera::RegisterAllLuaFunction(lua);
	LuaObject::RegisterAllLuaFunction(lua);
	LuaDrawSettings::RegisterAllLuaFunction(lua);
}