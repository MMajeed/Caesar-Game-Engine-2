#ifndef __LuaThreadSetup__
#define __LuaThreadSetup__

#include "Linker.h"

#include <Lua.hpp>
#include <luabind\luabind.hpp>

#include <string>

namespace LuaThreadSetup
{
	ScriptComponentDLL_API std::string Loop(double time, luabind::object const& function);
	ScriptComponentDLL_API void Sleep(double time, luabind::object const& function);
	ScriptComponentDLL_API void Remove(std::string ID);

	ScriptComponentDLL_API void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__LuaThreadSetup__
