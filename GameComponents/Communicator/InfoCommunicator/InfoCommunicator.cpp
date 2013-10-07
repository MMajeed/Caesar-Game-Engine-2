#include "InfoCommunicator.h"

#include <InfoManager.h>

void InfoCommunicator::SubmitMessage(std::shared_ptr<Message> msg)
{
	msg->Proccess();
}

Interface* InfoCommunicator::GetComponent()
{
	return &InfoManager::GetInstance();
}