#ifndef __AddBasicTexture__
#define __AddBasicTexture__

#include "Linker.h"

#include <Message.h>
#include <string>

namespace BasicTextureConfig
{
	GraphicCommunicatorDLL_API std::string Create(std::string texture);
	GraphicCommunicatorDLL_API void Release(std::string ID);
}

#endif //__AddBasicTexture__