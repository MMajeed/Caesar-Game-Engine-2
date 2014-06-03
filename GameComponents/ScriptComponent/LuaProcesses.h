#ifndef __LuaProcesses__
#define __LuaProcesses__

#include "Linker.h"

#include <string>
#include <GenerateGuid.h>
#include <Lua.hpp>

class ScriptComponentDLL_API LuaProcesses
{
protected:
	LuaProcesses(){ this->ID = CHL::GenerateGUID(); this->InfiniteLoop = true; }
	bool InfiniteLoop;
public:
	virtual void Update(double realTime, double deltaTime) = 0;

	virtual void Action(lua_State *lua) = 0;

	std::string ID;

	virtual bool IsInfiniteLoop(){ return this->InfiniteLoop; }

	virtual ~LuaProcesses(){}
};


#endif //__LuaProcesses__