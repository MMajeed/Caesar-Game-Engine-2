#ifndef __GraphicCommunicator__
#define __GraphicCommunicator__

#include "Linker.h"

#include <Interface.h>

namespace GraphicCommunicator
{
	GraphicCommunicatorDLL_API  void SubmitMessage(std::shared_ptr<Message> msg);
	GraphicCommunicatorDLL_API Interface* GetComponent();
};

#endif //__GraphicCommunicator__