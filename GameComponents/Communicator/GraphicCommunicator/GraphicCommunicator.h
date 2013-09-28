#ifndef __GraphicCommunicator__
#define __GraphicCommunicator__

#include "Linker.h"

#include <Interface.h>

class GraphicCommunicator
{
public:
	static void SubmitMessage(std::shared_ptr<Message> msg);
	static Interface* GetComponent();
};

#endif //__GraphicCommunicator__