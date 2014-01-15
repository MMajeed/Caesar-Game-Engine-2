#ifndef __InputCommunicator__
#define __InputCommunicator__

#include "Linker.h"

#include <Interface.h>

namespace InputCommunicator
{
	void SubmitMessage(std::shared_ptr<Message> msg);
	Interface* GetComponent();
};

#endif //__InputCommunicator__