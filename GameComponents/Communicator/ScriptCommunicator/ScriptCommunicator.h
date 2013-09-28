#ifndef __ScriptCommunicator__
#define __ScriptCommunicator__

#include "Linker.h"

#include <Interface.h>
#include <Message.h>

class ScriptCommunicator
{
public:
	static void SubmitMessage(std::shared_ptr<Message> msg);
	static Interface* GetComponent();
};

#endif //__ScriptCommunicator__