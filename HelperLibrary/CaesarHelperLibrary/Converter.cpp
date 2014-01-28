#include "Converter.h"
#include <sstream>
#include <algorithm>

namespace CHL
{
	std::string ToString (const std::wstring& t)
	{
		return std::string(t.begin(), t.end());
	}
	std::wstring ToWString (const std::string& t)
	{
		return std::wstring(t.begin(), t.end());
	}	

	std::string ToLower(std::string inputString)
	{
		std::transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower);
		return inputString;
	}
}