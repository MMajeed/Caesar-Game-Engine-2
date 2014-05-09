#ifndef __InputCommunicator__
#define __InputCommunicator__

#include "Linker.h"

#include <Interface.h>

namespace InputCommunicator
{
	InputCommunicatorDLL_API void SubmitMessage(std::shared_ptr<Message> msg);
	InputCommunicatorDLL_API Interface* GetComponent();
};

#endif //__InputCommunicator__