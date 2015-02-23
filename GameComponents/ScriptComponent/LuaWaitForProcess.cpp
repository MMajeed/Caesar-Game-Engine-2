#include "LuaWaitForProcess.h"
#include "LuaError.h"
#include <Components.h>
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
			msg = Components::Graphic->GetComponent()->GetBackMessage();
			break;
		case LuaWaitForProcess::ProcessType::Script:
			msg = Components::Script->GetComponent()->GetBackMessage();
			break;
		case LuaWaitForProcess::ProcessType::Animation:
			msg = Components::Animation->GetComponent()->GetBackMessage();
			break;
		case LuaWaitForProcess::ProcessType::Physics:
			msg = Components::Physics->GetComponent()->GetBackMessage();
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