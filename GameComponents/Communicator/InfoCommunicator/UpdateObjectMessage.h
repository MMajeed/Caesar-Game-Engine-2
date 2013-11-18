#ifndef __UpdateObjectMessage__
#define __UpdateObjectMessage__

#include "Linker.h"
#include <Message.h>
#include <INFO.h>

class UpdateObjectMessage : public Message
{
public:
	UpdateObjectMessage(const std::string& objectID, std::shared_ptr<INFO> info);
	virtual Message::Status Work();

	std::string objectID;
	std::shared_ptr<INFO> info;
};

#endif //__UpdateObjectMessage__