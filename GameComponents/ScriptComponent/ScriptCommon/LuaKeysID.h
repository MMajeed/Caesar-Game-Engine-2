#ifndef __LuaKeysID__
#define __LuaKeysID__

#include <Lua.hpp>

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
