#ifndef __AnimationCommunicator__
#define __AnimationCommunicator__

#include "Linker.h"

#include <Interface.h>

namespace AnimationCommunicator
{
	AnimationCommunicatorDLL_API void SubmitMessage(std::shared_ptr<Message> msg);
	AnimationCommunicatorDLL_API Interface* GetComponent();
};

#endif //__AnimationCommunicator__