#ifndef __AnimationCommunicator__
#define __AnimationCommunicator__

#include "Linker.h"

#include <Interface.h>

namespace AnimationCommunicator
{
	void SubmitMessage(std::shared_ptr<Message> msg);
	Interface* GetComponent();
};

#endif //__AnimationCommunicator__