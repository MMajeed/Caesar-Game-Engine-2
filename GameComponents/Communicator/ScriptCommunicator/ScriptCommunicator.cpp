#include "ScriptCommunicator.h"

#include <LuaManager.h>

void ScriptCommunicator::SubmitMessage(std::shared_ptr<Message> msg)
{
	ScriptCommunicator::GetComponent()->SubmitMessage(msg);
}

Interface* ScriptCommunicator::GetComponent()
{
	return &LuaManager::GetInstance();
}