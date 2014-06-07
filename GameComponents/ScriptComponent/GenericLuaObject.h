#ifndef __GenericLuaObject__
#define __GenericLuaObject__

#include "Linker.h"

#include <string>
#include <Lua.hpp>
#include <luabind\luabind.hpp>

class GenericLuaObject
{
public:
	std::string ID; 

	static void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__GenericLuaObject__
