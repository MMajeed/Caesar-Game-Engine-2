#ifndef __D3DShaderInfo__
#define __D3DShaderInfo__

#include "Linker.h"

#include <string>

struct D3DShaderInfo
{
	std::string	FileName;
	std::string	EntryPoint;
	std::string	Model;
};

#endif //__D3DShaderInfo__