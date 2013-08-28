#ifndef __StringConverter__
#define __StringConverter__

#include "Linker.h"
#include <string>

namespace CHL
{
	std::string WStringtoString( std::wstring inputString );
	std::wstring StringToWString( std::string inputString );
	std::string ToLower(std::string inputString);
	float StringToFloat(std::string inputString);
	int StringToInt(std::string inputString);
}

#endif //__StringConverter__