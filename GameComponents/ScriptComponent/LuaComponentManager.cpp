#include "LuaComponentManager.h"
#include "ScriptManager.h"
#include "ProcessMessage.h"
#include "LuaWaitForProcess.h"
#include <Logger.h>
#include "ScriptManager.h"
#include <GraphicCommunicator\GraphicCommunicator.h>
#include <InputCommunicator\InputCommunicator.h>
#include <AnimationCommunicator\AnimationCommunicator.h>
#include <PhysicsCommunicator\PhysicsCommunicator.h>
#include <GenerateGUID.h>

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
	void WaitToProcessAnimation(luabind::object const& function)
	{
		std::shared_ptr<LuaWaitForProcess> newKeyAction(new LuaWaitForProcess(LuaWaitForProcess::ProcessType::Animation, function));

		ProcessMessage::Add(newKeyAction);
	}
	void WaitToProcessPhysics(luabind::object const& function)
	{
		std::shared_ptr<LuaWaitForProcess> newKeyAction(new LuaWaitForProcess(LuaWaitForProcess::ProcessType::Physics, function));

		ProcessMessage::Add(newKeyAction);
	}

	void LogInformation(std::string message)
	{
		Logger::LogInformation(message);
	}
	void LogError(std::string message)
	{
		Logger::LogError(message);
	}
	void Quit()
	{
		std::exit(0);
	}

	double GetTimeSinceStart()
	{
		std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
		std::chrono::time_point<std::chrono::system_clock>& start = ScriptManager::GetInstance().timer.start;
		std::chrono::duration<double> elapsed_seconds = now - start;
		return elapsed_seconds.count();
	}
	double GetGraphicFrame()
	{
		return (double)GraphicCommunicator::GetComponent()->timer.FrameCount;
	}
	double GetInputFrame()
	{
		return (double)InputCommunicator::GetComponent()->timer.FrameCount;
	}
	double GetScriptFrame()
	{
		return (double)ScriptManager::GetInstance().timer.FrameCount;
	}
	double GetAnimationFrame()
	{
		return (double)AnimationCommunicator::GetComponent()->timer.FrameCount;
	}
	double GetPhysicsFrame()
	{
		return (double)PhysicsCommunicator::GetComponent()->timer.FrameCount;
	}

	std::string GenerateGUID()
	{
		return CHL::GenerateGUID();
	}

	void RegisterAllLuaFunction(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::def("WaitToProcessGraphic", LuaComponentManager::WaitToProcessGraphic),
			luabind::def("WaitToProcessInput", LuaComponentManager::WaitToProcessInput),
			luabind::def("WaitToProcessScript", LuaComponentManager::WaitToProcessScript),
			luabind::def("WaitToProcessAnimation", LuaComponentManager::WaitToProcessAnimation),
			luabind::def("WaitToProcessPhysics", LuaComponentManager::WaitToProcessPhysics),
			luabind::def("LogInformation", LuaComponentManager::LogInformation),
			luabind::def("LogError", LuaComponentManager::LogError),
			luabind::def("Quit", LuaComponentManager::Quit),
			luabind::def("GetTimeSinceStart", LuaComponentManager::GetTimeSinceStart),
			luabind::def("GetGraphicFrame", LuaComponentManager::GetGraphicFrame),
			luabind::def("GetInputFrame", LuaComponentManager::GetInputFrame),
			luabind::def("GetScriptFrame", LuaComponentManager::GetScriptFrame),
			luabind::def("GetAnimationFrame", LuaComponentManager::GetAnimationFrame),
			luabind::def("GetPhysicsFrame", LuaComponentManager::GetPhysicsFrame),
			luabind::def("GenerateGUID", LuaComponentManager::GenerateGUID)
		];
	}
};