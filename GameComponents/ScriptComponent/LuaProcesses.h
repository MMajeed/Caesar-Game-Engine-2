#ifndef __LuaProcesses__
#define __LuaProcesses__

#include <string>
#include <GenerateGuid.h>
#include <Lua.hpp>

class LuaProcesses
{
public:
	LuaProcesses(){ this->ID = CHL::GenerateGUID(); }

	virtual void Update(double realTime, double deltaTime) = 0;

	virtual void Action(lua_State *lua) = 0;

	std::string ID;
};


#endif //__LuaProcesses__