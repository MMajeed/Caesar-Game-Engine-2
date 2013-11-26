#ifndef __LuaLoopCallSetup__
#define __LuaLoopCallSetup__

#include <Lua.hpp>
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
