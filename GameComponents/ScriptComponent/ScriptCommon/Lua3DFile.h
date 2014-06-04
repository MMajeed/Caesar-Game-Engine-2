#ifndef __Lua3DFile__
#define __Lua3DFile__

#include "Linker.h"

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include <string>

namespace Lua3DFile
{
	ScriptCommonDLL_API luabind::object LoadScene(std::string fileName);

	ScriptCommonDLL_API void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__Lua3DFile__