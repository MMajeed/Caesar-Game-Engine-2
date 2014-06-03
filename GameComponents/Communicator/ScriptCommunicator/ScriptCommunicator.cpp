#include "ScriptCommunicator.h"

#include <LuaManager.h>


namespace ScriptCommunicator
{
	void SubmitMessage(std::shared_ptr<Message> msg)
	{
		ScriptCommunicator::GetComponent()->SubmitMessage(msg);
	}
	Interface* GetComponent()
	{
		return &LuaManager::GetInstance();
	}

};