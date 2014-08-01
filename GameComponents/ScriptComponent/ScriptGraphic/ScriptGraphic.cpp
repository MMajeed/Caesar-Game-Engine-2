#include "ScriptGraphic.h"

#include <ScriptManager.h>
#include <ProcessMessage.h>
#include <ActivateScriptComponent.h>

#include "LuaGraphicModel.h"
#include "LuaBasicTexture.h"
#include "LuaGraphic.h"
#include "LuaScreenCapture.h"
#include "LuaScreenShot.h"
#include "LuaShader.h"

ScriptGraphic::ScriptGraphic()
{
	std::shared_ptr<ActivateScriptComponent> newScriptComponent(
		new ActivateScriptComponent(ScriptGraphic::Init));

	ProcessMessage::Add(newScriptComponent);
}

void ScriptGraphic::Init(lua_State *lua)
{
	LuaGraphicModel::RegisterAllLuaFunction(lua);
	LuaBasicTexture::RegisterAllLuaFunction(lua);
	LuaGraphic::RegisterAllLuaFunction(lua);
	LuaScreenCapture::RegisterAllLuaFunction(lua);
	LuaScreenShot::RegisterAllLuaFunction(lua);
	LuaShader::RegisterAllLuaFunction(lua);
}