#ifndef __LuaThreadSetup__
#define __LuaThreadSetup__

#include <Lua.hpp>
#include <luabind\luabind.hpp>

#include <string>

namespace LuaThreadSetup
{
	std::string Loop(double time, luabind::object const& function);
	void Sleep(double time, luabind::object const& function);
	void Remove(std::string ID);

	void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__LuaThreadSetup__
