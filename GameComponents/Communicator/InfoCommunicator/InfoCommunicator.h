#ifndef __InfoCommunicator__
#define __InfoCommunicator__

#include "Linker.h"

#include <Interface.h>

class InfoCommunicator
{
public:
	static void SubmitMessage(std::shared_ptr<Message> msg);
	static Interface* GetComponent();
};

#endif //__InfoCommunicator__