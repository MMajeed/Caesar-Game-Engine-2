#ifndef __LuaError__
#define __LuaError__

#include "Linker.h"

#include <lua.hpp>
#include <string>

namespace LuaError
{
	ScriptComponentDLL_API std::string GetLuaError(lua_State * L);
}

#endif //__LuaError__
