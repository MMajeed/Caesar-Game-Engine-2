#include "InfoCommunicator.h"

#include <InfoManager.h>

void InfoCommunicator::SubmitMessage(std::shared_ptr<Message> msg)
{
	InfoCommunicator::GetComponent()->SubmitMessage(msg);
}

Interface* InfoCommunicator::GetComponent()
{
	return &InfoManager::GetInstance();
}