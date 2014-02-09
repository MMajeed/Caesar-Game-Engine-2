#include "PhysicsCommunicator.h"

#include <PhysicsManager.h>

namespace PhysicsCommunicator
{
	void SubmitMessage(std::shared_ptr<Message> msg)
	{
		PhysicsCommunicator::GetComponent()->SubmitMessage(msg);
	}
	Interface* GetComponent()
	{
		return &PhysicsManager::GetInstance();
	}
};