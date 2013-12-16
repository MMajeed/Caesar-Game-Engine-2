#include "GraphicCommunicator.h"

#include <GraphicManager.h>

namespace GraphicCommunicator
{
	void SubmitMessage(std::shared_ptr<Message> msg)
	{
		GraphicCommunicator::GetComponent()->SubmitMessage(msg);
	}
	Interface* GetComponent()
	{
		return &GraphicManager::GetInstance();
	}
};