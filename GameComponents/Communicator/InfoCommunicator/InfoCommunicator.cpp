#include "InfoCommunicator.h"

#include <ObjectManager.h>

void InfoCommunicator::SubmitMessage(std::shared_ptr<Message> msg)
{
	InfoCommunicator::GetComponent()->SubmitMessage(msg);
}

Interface* InfoCommunicator::GetComponent()
{
	return &ObjectManager::GetInstance();
}