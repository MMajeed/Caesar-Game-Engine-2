#include "LuaLoopCallSetup.h"

#include "LuaLoopCall.h"
#include "LuaManager.h"

std::string LuaLoopCallSetup::Loop(double time, luabind::object const& function)
{
	if (luabind::type(function) != LUA_TFUNCTION)
    {	
		throw std::invalid_argument("Wrong paramter for LoopCall, Please pass in how many seconds apart and function");
    }

	std::shared_ptr<LuaLoopCall> newKeyAction(new LuaLoopCall(time, function));

	LuaManager::GetInstance().SubmitProcesses(newKeyAction);

	return newKeyAction->ID;
}
void LuaLoopCallSetup::Register(lua_State *lua)
{
	luabind::module(lua)[
		luabind::def("LoopCall", LuaLoopCallSetup::Loop)
	  ];
}