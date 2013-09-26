#ifndef __LuaKeysID__
#define __LuaKeysID__

extern "C" {
#include <lua5.1.5\lua.h>
#include <lua5.1.5\lualib.h>
#include <lua5.1.5\lauxlib.h>
}

class LuaKeysID
{
public:
	static void Register(lua_State *lua);

	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaKeysID::Register(lua);
	}
};

#endif //__LuaKeysID__
