#ifndef __LuaKeysID__
#define __LuaKeysID__

#include "Linker.h"

#include <Lua.hpp>

namespace LuaKeysID
{
	ScriptComponentDLL_API void Register(lua_State *lua);

	ScriptComponentDLL_API void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__LuaKeysID__
