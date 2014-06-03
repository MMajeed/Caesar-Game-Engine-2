#include "ScriptGraphic.h"

#include <LuaManager.h>
#include <ProcessMessage.h>
#include <ActivateScriptComponent.h>

#include "LuaBasicDrawableObject.h"
#include "LuaBasicTexture.h"
#include "LuaGraphic.h"
#include "LuaScreenCapture.h"
#include "LuaScreenShot.h"

ScriptGraphic::ScriptGraphic()
{
	std::shared_ptr<ActivateScriptComponent> newScriptComponent(
		new ActivateScriptComponent(ScriptGraphic::Init));

	ProcessMessage::Add(newScriptComponent);
}

void ScriptGraphic::Init(lua_State *lua)
{
	LuaBasicDrawableObject::RegisterAllLuaFunction(lua);
	LuaBasicTexture::RegisterAllLuaFunction(lua);
	LuaGraphic::RegisterAllLuaFunction(lua);
	LuaScreenCapture::RegisterAllLuaFunction(lua);
	LuaScreenShot::RegisterAllLuaFunction(lua);
}