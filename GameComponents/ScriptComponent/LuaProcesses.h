#ifndef __LuaProcesses__
#define __LuaProcesses__

#include "Linker.h"

#include <string>
#include <GenerateGuid.h>
#include <Lua.hpp>

class ScriptComponentDLL_API LuaProcesses
{
protected:
	LuaProcesses(){ this->ID = CHL::GenerateGUID(); this->Delete = false; }
	bool Delete;
public:
	virtual void Update(double realTime, double deltaTime) = 0;

	virtual void Action(lua_State *lua) = 0;

	std::string ID;

	virtual bool DoDelete(){ return this->Delete; }

	virtual ~LuaProcesses(){}
};


#endif //__LuaProcesses__