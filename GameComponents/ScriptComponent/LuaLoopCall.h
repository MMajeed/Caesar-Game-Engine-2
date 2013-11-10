#ifndef __LuaLoopCall__
#define __LuaLoopCall__

#include "LuaProcesses.h"
#include <string>
#include <luabind\luabind.hpp>

class LuaLoopCall : public LuaProcesses
{
public:
	LuaLoopCall(double inputMilliseconds, luabind::object inputFunction);

	virtual void Update(double realTime, double deltaTime);
	virtual void Action(lua_State *lua);

	double milliseconds;
	luabind::object function;

	double timeSinceLastCall;
};


#endif //__LuaLoopCall__