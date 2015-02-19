#include "LuaWaitForProcess.h"
#include "LuaError.h"
#include <GraphicCommunicator\GraphicCommunicator.h>
#include <AnimationCommunicator\AnimationCommunicator.h>
#include <PhysicsCommunicator\PhysicsCommunicator.h>
#include "ScriptManager.h"
#include <Logger.h>
#include "ProcessMessage.h"

LuaWaitForProcess::LuaWaitForProcess(LuaWaitForProcess::ProcessType type, luabind::object inputFunction)
{
	this->type = type;
	this->function = inputFunction;

	switch(this->type)
	{
		case LuaWaitForProcess::ProcessType::Graphic:
			msg = GraphicCommunicator::GetComponent()->GetBackMessage();
			break;
		case LuaWaitForProcess::ProcessType::Script:
			msg = ScriptManager::GetInstance().GetBackMessage();
			break;
		case LuaWaitForProcess::ProcessType::Animation:
			msg = AnimationCommunicator::GetComponent()->GetBackMessage();
			break;
		case LuaWaitForProcess::ProcessType::Physics:
			msg = PhysicsCommunicator::GetComponent()->GetBackMessage();
			break;

	}
}

void LuaWaitForProcess::Action(lua_State *lua)
{

	if(msg.expired())
	{
		try
		{
			luabind::call_function<void>(this->function);
		}
		catch(...)
		{
			Logger::LogError(LuaError::GetLuaError(lua));
		}
		this->Delete = true;
	}
}

void LuaWaitForProcess::Update(double realTime, double deltaTime)
{

}