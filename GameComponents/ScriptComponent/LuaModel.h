#ifndef __LuaModel__
#define __LuaModel__

#include <Lua.hpp>
class LuaModel
{
public:
	static void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__LuaModel__