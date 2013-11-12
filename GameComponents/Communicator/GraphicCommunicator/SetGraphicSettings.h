#ifndef __SetGraphicSettings__
#define __SetGraphicSettings__

#include "Linker.h"
#include <Message.h>
#include <Vector.h>
#include <string>
class ClearScreenMessage : public Message
{
public:
	ClearScreenMessage(const CHL::Vec4& input);
	virtual Message::Status Work();
protected:
	CHL::Vec4 colour;
};

class SetCameraIDMessage : public Message
{
public:
	SetCameraIDMessage(const std::string& input);
	virtual Message::Status Work();
protected:
	std::string id;
};

class SetPrespectiveIDMessage : public Message
{
public:
	SetPrespectiveIDMessage(const std::string& input);
	virtual Message::Status Work();
protected:
	std::string id;
};

#endif //__SetGraphicSettings__