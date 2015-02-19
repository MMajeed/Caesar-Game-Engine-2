#ifndef __LuaWaitForProcess__
#define __LuaWaitForProcess__

#include "LuaProcesses.h"
#include <string>
#include <luabind\luabind.hpp>
#include <Message.h>

class ScriptComponentDLL_API LuaWaitForProcess : public LuaProcesses
{
public:
	enum class ProcessType { Graphic, Script, Animation, Physics };
	LuaWaitForProcess(ProcessType type, luabind::object inputFunction);

	virtual void Update(double realTime, double deltaTime);
	virtual void Action(lua_State *lua);

	ProcessType type;
	std::weak_ptr<Message> msg;

	luabind::object function;
};


#endif //__LuaWaitForProcess__