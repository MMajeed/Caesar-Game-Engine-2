#ifndef __ScriptCommunicator__
#define __ScriptCommunicator__

#include "Linker.h"

#include <Interface.h>
#include <Message.h>

namespace ScriptCommunicator
{
	ScriptCommunicatorDLL_API void SubmitMessage(std::shared_ptr<Message> msg);
	ScriptCommunicatorDLL_API Interface* GetComponent();
};

#endif //__ScriptCommunicator__