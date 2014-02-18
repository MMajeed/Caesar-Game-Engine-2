#ifndef __LuaProcesses__
#define __LuaProcesses__

#include <string>
#include <GenerateGuid.h>
#include <Lua.hpp>

class LuaProcesses
{
protected:
	LuaProcesses(){ this->ID = CHL::GenerateGUID(); }
public:
	virtual void Update(double realTime, double deltaTime) = 0;

	virtual void Action(lua_State *lua) = 0;

	std::string ID;

	virtual ~LuaProcesses(){}
};


#endif //__LuaProcesses__