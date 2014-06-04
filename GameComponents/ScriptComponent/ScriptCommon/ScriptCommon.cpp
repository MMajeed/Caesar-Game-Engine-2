 #include "ScriptCommon.h"

#include <LuaManager.h>
#include <ProcessMessage.h>
#include <ActivateScriptComponent.h>

#include "LuaMath.h"
#include "LuaKeysID.h"
#include "LuaThreadSetup.h"
#include "LuaComponentManager.h"
#include "Lua3DFile.h"
#include "LuaModel.h"
#include "LuaAnimation.h"
#include "LuaNode.h"

ScriptCommon::ScriptCommon()
{
	std::shared_ptr<ActivateScriptComponent> newScriptComponent(
		new ActivateScriptComponent(ScriptCommon::Init));

	ProcessMessage::Add(newScriptComponent);
}

void ScriptCommon::Init(lua_State *lua)
{
	LuaMath::RegisterAllLuaFunction(lua);
	LuaKeysID::RegisterAllLuaFunction(lua);
	LuaThreadSetup::RegisterAllLuaFunction(lua);
	LuaComponentManager::RegisterAllLuaFunction(lua);
	Lua3DFile::RegisterAllLuaFunction(lua);
	LuaModel::RegisterAllLuaFunction(lua);
	LuaAnimation::RegisterAllLuaFunction(lua);
	LuaNode::RegisterAllLuaFunction(lua);
}