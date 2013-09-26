#ifndef __AddObjectMessage__
#define __AddObjectMessage__

#include "Linker.h"
#include <Queryable.h>
#include <string>

#include <Message.h>

class AddObjectMessage : public Message
{
public:
	AddObjectMessage(CHL::MapQ<std::string, std::string> info);
	virtual Message::Status Work();
	CHL::MapQ<std::string, std::string> messageInfo;
	std::string ID;
};

#endif //__AddObjectMessage__