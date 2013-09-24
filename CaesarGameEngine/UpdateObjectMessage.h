#ifndef __UpdateObjectMessage__
#define __UpdateObjectMessage__

#include <Queryable.h>
#include <string>

#include "Message.h"

class UpdateObjectMessage : public Message
{
public:
	UpdateObjectMessage(const std::string& inputObjectID, const std::string& inputInfoID, const std::string& inputInfo );
	virtual Message::Status Work();
	std::string objectID;
	std::string infoID;
	std::string info;
};

#endif //__UpdateObjectMessage__