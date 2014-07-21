#ifndef __GenericLuaObject__
#define __GenericLuaObject__

#include "Linker.h"

#include <string>
#include <Lua.hpp>
#include <luabind\luabind.hpp>

class GenericLuaObject
{
public:
	GenericLuaObject() = default;
	GenericLuaObject(std::string ID);
	operator std::string();

	std::string ID; 

	static void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__GenericLuaObject__
