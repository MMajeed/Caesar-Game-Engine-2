#include "LuaModel.h"

#include "LuaManager.h"

int LuaModel::Model::NewModel(lua_State *lua)
{
	static const luaL_reg Foo_methods[] = {
	  {0, 0}
	};


	return 1;
}

void LuaModel::Model::Register()
{
	lua_State *lua = LuaManager::GetInstance().lua;

	lua_register(lua, "Model", LuaModel::Model::NewModel);	// Register the function
}