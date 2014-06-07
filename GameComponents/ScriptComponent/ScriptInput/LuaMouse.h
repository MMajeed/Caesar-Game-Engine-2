#ifndef __LuaMouse__
#define __LuaMouse__

#include "Linker.h"

#include <Lua.hpp>
#include <luabind\luabind.hpp>

#include <string>

namespace LuaMouse
{
	ScriptInputDLL_API luabind::object Location();

	ScriptInputDLL_API void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__LuaMouse__
