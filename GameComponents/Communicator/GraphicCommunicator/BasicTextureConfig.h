#ifndef __AddBasicTexture__
#define __AddBasicTexture__

#include "Linker.h"

#include <Message.h>
#include <string>

namespace BasicTextureConfig
{
	std::string Create(std::string texture);
	void Release(std::string ID);
}

#endif //__AddBasicTexture__