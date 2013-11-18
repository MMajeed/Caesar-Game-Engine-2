#ifndef __AddObjectMessage__
#define __AddObjectMessage__

#include "Linker.h"
#include <INFO.h>

#include <Message.h>

class AddObjectMessage : public Message
{
public:
	AddObjectMessage(SP_INFO info);
	virtual Message::Status Work();
	SP_INFO infoToAdd;
};

#endif //__AddObjectMessage__