#ifndef __LuaError__
#define __LuaError__

#include <lua.hpp>
#include <string>

namespace LuaError
{
	std::string GetLuaError(lua_State * L);
}

#endif //__LuaError__
