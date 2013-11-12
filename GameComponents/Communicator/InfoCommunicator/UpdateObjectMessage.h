#ifndef __UpdateObjectMessage__
#define __UpdateObjectMessage__

#include "Linker.h"

#include <vector>
#include <string>
#include <Object.h>
#include <Message.h>

class UpdateObjectMessage : public Message
{
public:
	UpdateObjectMessage(const std::string& inputObjectID, const std::string& inputInfoID, std::shared_ptr<Object> inputInfo );
	virtual Message::Status Work();
	std::string objectID;
	std::string infoID;
	 std::shared_ptr<Object> info;
};

class DeleteInfoMessgae : public Message
{
public:
	DeleteInfoMessgae(const std::string& inputObjectID, const std::string& inputInfoID);
	virtual Message::Status Work();
	std::string objectID;
	std::string infoID;
};

#endif //__UpdateObjectMessage__