#ifndef __LuaInputKeyActionSetup__
#define __LuaInputKeyActionSetup__

#include <Lua.hpp>
#include <luabind\luabind.hpp>

#include <string>

namespace LuaInputKeyActionSetup
{
	std::string OnKeyDown(int key, luabind::object const&  function);
	std::string OnKeyUp(int key, luabind::object const& function);
	void RemoveInputAction(std::string ID);
	void Register(lua_State *lua);

	void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__LuaInputKeyActionSetup__
