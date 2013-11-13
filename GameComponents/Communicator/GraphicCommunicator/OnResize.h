#ifndef __OnResize__
#define __OnResize__

#include "Linker.h"

#include <Message.h>
#include <string>

class OnResize : public Message
{
public:
	OnResize(unsigned int widthInput, unsigned int heightInput);

	virtual Message::Status Work();

	unsigned int width;
	unsigned int height;
};

#endif //__OnResize__