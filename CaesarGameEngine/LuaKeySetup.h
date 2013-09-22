#ifndef __LuaKeySetup__
#define __LuaKeySetup__

extern "C" {
#include <lua5.1.5\lua.h>
#include <lua5.1.5\lualib.h>
#include <lua5.1.5\lauxlib.h>
}

#include <luabind\luabind.hpp>

#include <string>

class LuaKeySetup
{
public:
	static std::string OnKeyDown(unsigned int key, luabind::object function);
	static std::string OnKeyUp(unsigned int key, luabind::object const& function);
	static std::string OnKeyHold(unsigned int key, luabind::object const& function);
	static void Register(lua_State *lua);

	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaKeySetup::Register(lua);
	}
};

#endif //__LuaKeySetup__
