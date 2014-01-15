#ifndef __LuaProcesses__
#define __LuaProcesses__

#include <string>
#include <GenerateGuid.h>
#include <Lua.hpp>

class LuaProcesses
{
public:
	LuaProcesses(){}

	virtual void Update(double realTime, double deltaTime) = 0;

	virtual void Action(lua_State *lua) = 0;
};


#endif //__LuaProcesses__