#ifndef __Resource__
#define __Resource__

#include "Linker.h"

#include <string>
#include <unordered_map>
#include <memory>

#include <Lua.hpp>
#include <luabind\luabind.hpp>

#include "LuaProcesses.h"

namespace Resource
{
	extern ScriptComponentDLL_API std::unordered_map<std::string, std::shared_ptr<LuaProcesses>> allProcesses;
	extern ScriptComponentDLL_API lua_State *lua;
};

#endif //__Resource__