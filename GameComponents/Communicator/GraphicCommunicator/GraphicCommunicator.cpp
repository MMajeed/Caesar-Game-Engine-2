#include "GraphicCommunicator.h"

#include <GraphicManager.h>

void GraphicCommunicator::SubmitMessage(std::shared_ptr<Message> msg)
{
	GraphicCommunicator::GetComponent()->SubmitMessage(msg);
}

Interface* GraphicCommunicator::GetComponent()
{
	return &GraphicManager::GetInstance();
}