#include "ScriptInput.h"

#include <LuaManager.h>
#include <ProcessMessage.h>
#include <ActivateScriptComponent.h>

#include "LuaInputKeyActionSetup.h"
#include "LuaMouse.h"

ScriptInput::ScriptInput()
{
	std::shared_ptr<ActivateScriptComponent> newScriptComponent(
		new ActivateScriptComponent(ScriptInput::Init));

	ProcessMessage::Add(newScriptComponent);
}

void ScriptInput::Init(lua_State *lua)
{
	LuaInputKeyActionSetup::RegisterAllLuaFunction(lua);
	LuaMouse::RegisterAllLuaFunction(lua);
}