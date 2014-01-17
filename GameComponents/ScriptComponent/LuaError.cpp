#include "LuaError.h"

std::string LuaError::GetLuaError(lua_State * L)
{
	const char * s = lua_tostring(L, -1);
	if(s == NULL) s = "unrecognized Lua ErrorException";
	return s;
}