#ifndef __PhysicsCommunicator__
#define __PhysicsCommunicator__

#include "Linker.h"

#include <Interface.h>

namespace PhysicsCommunicator
{
	void SubmitMessage(std::shared_ptr<Message> msg);
	Interface* GetComponent();
};

#endif //__PhysicsCommunicator__