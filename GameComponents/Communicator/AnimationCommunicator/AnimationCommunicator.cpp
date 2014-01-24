#include "AnimationCommunicator.h"

#include <AnimationManager.h>

namespace AnimationCommunicator
{
	void SubmitMessage(std::shared_ptr<Message> msg)
	{
		AnimationCommunicator::GetComponent()->SubmitMessage(msg);
	}
	Interface* GetComponent()
	{
		return &AnimationManager::GetInstance();
	}
};