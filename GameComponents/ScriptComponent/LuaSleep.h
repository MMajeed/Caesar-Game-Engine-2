#ifndef __LuaSleep__
#define __LuaSleep__

#include "LuaProcesses.h"
#include <string>
#include <luabind\luabind.hpp>

class ScriptComponentDLL_API LuaSleep : public LuaProcesses
{
public:
	LuaSleep(double inputMilliseconds, luabind::object inputFunction);

	virtual void Update(double realTime, double deltaTime);
	virtual void Action(lua_State *lua);

	double milliseconds;
	luabind::object function;
	double timeSinceLastCall;
};


#endif //__LuaSleep__