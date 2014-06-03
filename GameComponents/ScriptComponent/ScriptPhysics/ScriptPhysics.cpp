#include "ScriptPhysics.h"

#include <LuaManager.h>
#include <ProcessMessage.h>
#include <ActivateScriptComponent.h>

#include "LuaCollisionShape.h"
#include "LuaConstraint.h"
#include "LuaRigidBody.h"

ScriptPhysics::ScriptPhysics()
{
	std::shared_ptr<ActivateScriptComponent> newScriptComponent(
		new ActivateScriptComponent(ScriptPhysics::Init));

	ProcessMessage::Add(newScriptComponent);
}

void ScriptPhysics::Init(lua_State *lua)
{
	LuaCollisionShape::RegisterAllLuaFunction(lua);
	LuaConstraint::RegisterAllLuaFunction(lua);
	LuaRigidBody::RegisterAllLuaFunction(lua);
}