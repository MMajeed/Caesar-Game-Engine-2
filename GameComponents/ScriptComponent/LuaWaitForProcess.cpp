#include "LuaWaitForProcess.h"
#include "LuaError.h"
#include <GraphicCommunicator\GraphicCommunicator.h>
#include <InputCommunicator\InputCommunicator.h>
#include <ScriptCommunicator\ScriptCommunicator.h>
#include <Logger.h>
#include "ProcessMessage.h"

LuaWaitForProcess::LuaWaitForProcess(LuaWaitForProcess::ProcessType type, luabind::object inputFunction)
{
	this->type = type;
	this->function = inputFunction;
}

void LuaWaitForProcess::Action(lua_State *lua)
{
	bool empty = false;
	switch(this->type)
	{
		case LuaWaitForProcess::ProcessType::Graphic:
			empty = GraphicCommunicator::GetComponent()->AnyMessage();
			break;
		case LuaWaitForProcess::ProcessType::Input:
			empty = InputCommunicator::GetComponent()->AnyMessage();
			break;
		case LuaWaitForProcess::ProcessType::Script:
			empty = ScriptCommunicator::GetComponent()->AnyMessage();
			break;
	}
	if(empty == true)
	{
		try
		{
			luabind::call_function<void>(this->function);
		}
		catch(...)
		{
			Logger::LogError(LuaError::GetLuaError(lua));
		}
		ProcessMessage::Remove(this->ID);
	}
}

void LuaWaitForProcess::Update(double realTime, double deltaTime)
{

}