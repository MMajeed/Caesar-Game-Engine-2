#ifndef __ActivateScriptComponent__
#define __ActivateScriptComponent__

#include "LuaProcesses.h"
#include <string>
#include "LuaManager.h"
#include <functional>

class ScriptComponentDLL_API ActivateScriptComponent : public LuaProcesses
{
public:
	ActivateScriptComponent(std::function<void(lua_State*)> func);

	virtual void Update(double realTime, double deltaTime);
	virtual void Action(lua_State *lua);

protected:
	std::function<void(lua_State*)> func;
};


#endif //__ActivateScriptComponent__