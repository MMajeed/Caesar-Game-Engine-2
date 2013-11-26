#ifndef __AddBasicTexture__
#define __AddBasicTexture__

#include "Linker.h"

#include <Message.h>
#include <string>

class  AddBasicTexture : public Message
{
public:
	AddBasicTexture(std::string texture);

	virtual Message::Status Work();

	std::string	TextureFileName;
	std::string	ID;
};

#endif //__AddBasicTexture__