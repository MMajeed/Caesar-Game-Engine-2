#include "InputCommunicator.h"

#include <InputManager.h>

namespace InputCommunicator
{
	void SubmitMessage(std::shared_ptr<Message> msg)
	{
		InputCommunicator::GetComponent()->SubmitMessage(msg);
	}
	Interface* GetComponent()
	{
		return &InputManager::GetInstance();
	}
};