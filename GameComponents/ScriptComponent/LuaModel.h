#ifndef __LuaModel__
#define __LuaModel__

extern "C" {
#include <lua5.1.5\lua.h>
#include <lua5.1.5\lualib.h>
#include <lua5.1.5\lauxlib.h>
}

class LuaModel
{
public:
	static void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__LuaModel__