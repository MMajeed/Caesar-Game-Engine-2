#ifndef __LuaKeys__
#define __LuaKeys__

extern "C" {
#include <lua-5.1.0\lua.h>
#include <lua-5.1.0\lualib.h>
#include <lua-5.1.0\lauxlib.h>
}

class LuaKeys
{
public:
	static void Register(lua_State *lua);

	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaKeys::Register(lua);
	}
};

#endif //__LuaKeys__