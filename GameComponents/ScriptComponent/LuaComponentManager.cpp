#include "LuaComponentManager.h"

#include "ProcessMessage.h"
#include "LuaWaitForProcess.h"
#include <Logger.h>

namespace LuaComponentManager
{
	void WaitToProcessGraphic(luabind::object const& function)
	{
		std::shared_ptr<LuaWaitForProcess> newKeyAction(new LuaWaitForProcess(LuaWaitForProcess::ProcessType::Graphic, function));

		ProcessMessage::Add(newKeyAction);
	}
	void WaitToProcessInput(luabind::object const& function)
	{
		std::shared_ptr<LuaWaitForProcess> newKeyAction(new LuaWaitForProcess(LuaWaitForProcess::ProcessType::Input, function));

		ProcessMessage::Add(newKeyAction);
	}
	void WaitToProcessScript(luabind::object const& function)
	{
		std::shared_ptr<LuaWaitForProcess> newKeyAction(new LuaWaitForProcess(LuaWaitForProcess::ProcessType::Script, function));

		ProcessMessage::Add(newKeyAction);
	}
	void LogInformation(std::string message)
	{
		void Logger::LogInformation(std::string message);
	}
	void LogError(std::string message)
	{
		void Logger::LogError(std::string message);
	}
	void Quit()
	{
		std::exit(0);
	}

	void RegisterAllLuaFunction(lua_State *lua)
	{

		luabind::module(lua)[
			luabind::def("WaitToProcessGraphic", LuaComponentManager::WaitToProcessGraphic),
			luabind::def("WaitToProcessInput", LuaComponentManager::WaitToProcessInput),
			luabind::def("WaitToProcessScript", LuaComponentManager::WaitToProcessScript),
			luabind::def("LogInformation", LuaComponentManager::LogInformation),
			luabind::def("LogError", LuaComponentManager::LogError),
			luabind::def("Quit", LuaComponentManager::Quit)
		];
	}
};