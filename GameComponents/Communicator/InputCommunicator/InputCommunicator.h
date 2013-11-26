#ifndef __InputCommunicator__
#define __InputCommunicator__

#include "Linker.h"

#include <Interface.h>

class InputCommunicator
{
public:
	static void SubmitMessage(std::shared_ptr<Message> msg);
	static Interface* GetComponent();
};

#endif //__InputCommunicator__