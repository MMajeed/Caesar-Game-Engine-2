#ifndef __GraphicCommunicator__
#define __GraphicCommunicator__

#include "Linker.h"

#include <Interface.h>

namespace GraphicCommunicator
{
	void SubmitMessage(std::shared_ptr<Message> msg);
	Interface* GetComponent();
};

#endif //__GraphicCommunicator__