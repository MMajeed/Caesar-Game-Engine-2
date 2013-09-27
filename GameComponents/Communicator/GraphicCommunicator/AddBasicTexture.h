#ifndef __AddBasicTexture__
#define __AddBasicTexture__

#include "Linker.h"

#include <Message.h>
#include <string>

class  AddBasicTexture : public Message
{
public:
	AddBasicTexture(int slot, std::string texture);

	virtual Message::Status Work();

	int slot;
	std::string	TextureFileName;

	std::string	ID;
};

#endif //__AddBasicTexture__