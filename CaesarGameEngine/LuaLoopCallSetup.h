#ifndef __LuaLoopCallSetup__
#define __LuaLoopCallSetup__

extern "C" {
#include <lua5.1.5\lua.h>
#include <lua5.1.5\lualib.h>
#include <lua5.1.5\lauxlib.h>
}

#include <luabind\luabind.hpp>

#include <string>

class LuaLoopCallSetup
{
public:
	static std::string Loop(double time, luabind::object const& function);
	static void Register(lua_State *lua);

	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaLoopCallSetup::Register(lua);
	}
};

#endif //__LuaLoopCallSetup__
