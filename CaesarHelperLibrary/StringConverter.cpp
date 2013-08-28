#include "StringConverter.h"
#include <sstream>
#include <algorithm>

namespace CHL
{
	std::string WStringtoString( std::wstring inputString )
	{
		std::string converted(inputString.begin(), inputString.end());

		return converted;
	}
	std::wstring StringToWString( std::string inputString )
	{
		std::wstring converted(inputString.begin(), inputString.end());

		return converted;
	}
	std::string ToLower(std::string inputString)
	{
		std::transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower);
		return inputString;
	}
	float StringToFloat(std::string inputString)
	{
		float returnValue = std::numeric_limits<float>::min();

		std::stringstream ss;
		ss << inputString;
		ss >> returnValue;

		return returnValue;
	}
	int StringToInt(std::string inputString)
	{
		int returnValue = std::numeric_limits<int>::min();

		std::stringstream ss;
		ss << inputString;
		ss >> returnValue;

		return returnValue;	
	}
}