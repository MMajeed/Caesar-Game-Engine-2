#include "InputCommunicator.h"

#include <InputManager.h>

void InputCommunicator::SubmitMessage(std::shared_ptr<Message> msg)
{
	InputCommunicator::GetComponent()->SubmitMessage(msg);
}

Interface* InputCommunicator::GetComponent()
{
	return &InputManager::GetInstance();
}