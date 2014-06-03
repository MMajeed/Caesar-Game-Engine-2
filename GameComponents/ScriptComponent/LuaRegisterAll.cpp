#include "LuaRegisterAll.h"

#include "LuaMath.h"
#include "LuaKeysID.h"
#include "LuaThreadSetup.h"
#include "LuaComponentManager.h"
#include "Lua3DFile.h"
#include "LuaModel.h"
#include "LuaAnimation.h"
#include "LuaNode.h"

void LuaRegisterAll(lua_State *lua)
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