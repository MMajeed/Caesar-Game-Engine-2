#include "ScriptCommunicator.h"

#include <ScriptManager.h>


namespace ScriptCommunicator
{
	void SubmitMessage(std::shared_ptr<Message> msg)
	{
		ScriptCommunicator::GetComponent()->SubmitMessage(msg);
	}
	Interface* GetComponent()
	{
		return &ScriptManager::GetInstance();
	}

};