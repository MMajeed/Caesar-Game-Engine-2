#include "LuaError.h"

static void LuaError_lua_resource_delete(lua_State * L)
{
	lua_pop(L, 1);
}

LuaError::LuaError(lua_State * L)
	: m_L(L), m_lua_resource(L, LuaError_lua_resource_delete)
{

}

LuaError::LuaError(const LuaError & other)
	: m_L(other.m_L), m_lua_resource(other.m_lua_resource)
{

}
const char * LuaError::what() const throw()
{
	const char * s = lua_tostring(m_L, -1);
	if (s == NULL) s = "unrecognized Lua error";
	return s;
}

LuaError::~LuaError()
{
}