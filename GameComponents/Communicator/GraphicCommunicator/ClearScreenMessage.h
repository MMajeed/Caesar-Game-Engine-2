#ifndef __ClearScreen__
#define __ClearScreen__

#include "Linker.h"
#include <Message.h>
#include <Vector.h>

class ClearScreenMessage : public Message
{
public:
	ClearScreenMessage(const CHL::Vec4& input);

	virtual Message::Status Work();

protected:
	CHL::Vec4 colour;
};

#endif