#ifndef __LuaOnResize__
#define __LuaOnResize__

#include "LuaProcesses.h"
#include <string>
#include <luabind\luabind.hpp>
#include <InputKeysEnum.h>
#include <Message.h>

class ScriptComponentDLL_API LuaOnResize : public LuaProcesses
{
public:
	LuaOnResize(luabind::object inputFunction);

	virtual void Update(double realTime, double deltaTime);
	virtual void Action(lua_State *lua);

	unsigned int lastCheckedWidth;
	unsigned int lastCheckedHeight;
	
	luabind::object function;
};


#endif //__LuaOnResize__