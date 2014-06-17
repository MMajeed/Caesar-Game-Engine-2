#include "LuaThreadSetup.h"

#include "LuaLoopCall.h"
#include "LuaSleep.h"
#include "ScriptManager.h"
#include "ProcessMessage.h"
#include <Logger.h>

namespace LuaThreadSetup
{
	std::string Loop(double time, luabind::object const& function)
	{
		if(luabind::type(function) != LUA_TFUNCTION)
		{
			Logger::LogError("Wrong paramter for LoopCall, Please pass in how many seconds apart and function");
		}

		std::shared_ptr<LuaLoopCall> newKeyAction(new LuaLoopCall(time, function));

		ProcessMessage::Add(newKeyAction);

		return newKeyAction->ID;
	}
	void Sleep(double time, luabind::object const& function)
	{
		if(luabind::type(function) != LUA_TFUNCTION)
		{
			Logger::LogError("Wrong paramter for LoopCall, Please pass in how many seconds apart and function");
		}
		std::string ID = CHL::GenerateGUID();
		std::shared_ptr<LuaSleep> newKeyAction(new LuaSleep(time, function));
		ProcessMessage::Add(newKeyAction);
	}
	void Remove(std::string ID)
	{
		ProcessMessage::Remove(ID);
	}
	void RegisterAllLuaFunction(lua_State *lua)
	{

		luabind::module(lua)[
			luabind::def("LoopCall", LuaThreadSetup::Loop),
				luabind::def("Sleep", LuaThreadSetup::Sleep),
				luabind::def("RemoveProcess", LuaThreadSetup::Remove)
		];
	}
};