#ifndef __PhysicsCommunicator__
#define __PhysicsCommunicator__

#include "Linker.h"

#include <Interface.h>

namespace PhysicsCommunicator
{
	PhysicsCommunicatorDLL_API void SubmitMessage(std::shared_ptr<Message> msg);
	PhysicsCommunicatorDLL_API Interface* GetComponent();
};

#endif //__PhysicsCommunicator__