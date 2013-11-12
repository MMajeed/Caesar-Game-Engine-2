#ifndef __AddObjectMessage__
#define __AddObjectMessage__

#include "Linker.h"
#include <hash_map>
#include <string>
#include <Object.h>

#include <Message.h>

class AddObjectMessage : public Message
{
public:
	AddObjectMessage(const std::hash_map<std::string, std::shared_ptr<Object>>& info);
	virtual Message::Status Work();
	std::hash_map<std::string, std::shared_ptr<Object>> messageInfo;
	std::string ID;
};

#endif //__AddObjectMessage__