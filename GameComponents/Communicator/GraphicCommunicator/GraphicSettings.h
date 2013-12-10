#ifndef __GraphicSettings__
#define __GraphicSettings__

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

class OnResize : public Message
{
public:
	OnResize(unsigned int widthInput, unsigned int heightInput);

	virtual Message::Status Work();

	unsigned int width;
	unsigned int height;
};

#endif //__GraphicSettings__