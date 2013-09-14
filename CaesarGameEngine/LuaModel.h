#ifndef __LuaModel__
#define __LuaModel__

extern "C" {
#include <lua-5.1.0\lua.h>
#include <lua-5.1.0\\lualib.h>
#include <lua-5.1.0\\lauxlib.h>
}

class LuaModel
{
public:
	static void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__LuaModel__