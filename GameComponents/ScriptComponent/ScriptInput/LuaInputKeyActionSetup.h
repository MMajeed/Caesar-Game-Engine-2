#ifndef __LuaInputKeyActionSetup__
#define __LuaInputKeyActionSetup__

#include "Linker.h"

#include <Lua.hpp>
#include <luabind\luabind.hpp>

#include <string>

namespace LuaInputKeyActionSetup
{
	ScriptInputDLL_API std::string OnKeyDown(int key, luabind::object const&  function);
	ScriptInputDLL_API std::string OnKeyUp(int key, luabind::object const& function);
	ScriptInputDLL_API void RemoveInputAction(std::string ID);

	ScriptInputDLL_API void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__LuaInputKeyActionSetup__
