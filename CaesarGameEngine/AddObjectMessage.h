#ifndef __AddObjectMessage__
#define __AddObjectMessage__

#include <Queryable.h>
#include <string>

#include "Message.h"

class AddObjectMessage : public Message
{
public:
	AddObjectMessage(CHL::MapQueryable<std::string, std::string> info);
	virtual Message::Status Work();
	CHL::MapQueryable<std::string, std::string> messageInfo;
	std::string ID;
};

#endif //__AddObjectMessage__