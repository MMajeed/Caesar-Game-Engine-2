#ifndef __AddObjectMessage__
#define __AddObjectMessage__

#include "Linker.h"
#include <Queryable.h>
#include <string>
#include <Object.h>

#include <Message.h>

class AddObjectMessage : public Message
{
public:
	AddObjectMessage(const CHL::MapQ<std::string, std::shared_ptr<Object>>& info);
	virtual Message::Status Work();
	CHL::MapQ<std::string, std::shared_ptr<Object>> messageInfo;
	std::string ID;
};

#endif //__AddObjectMessage__