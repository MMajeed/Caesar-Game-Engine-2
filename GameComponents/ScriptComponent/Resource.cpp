#include "Resource.h"

namespace Resource
{
	std::unordered_map<std::string, std::shared_ptr<LuaProcesses>> allProcesses;
	lua_State *lua;
};
