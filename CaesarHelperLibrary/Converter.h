#ifndef __StringConverter__
#define __StringConverter__

#include "Linker.h"
#include <string>
#include <sstream>

namespace CHL
{
	template <class T>
	std::string ToString (const T& t)
	{
		std::stringstream ss;
		ss << t;
		return ss.str();
	}
	std::string ToString (const std::wstring& t);

	template <class T>
	std::wstring ToWString (const T& t)
	{
		std::wstringstream ss;
		ss << t;
		return ss.str();
	}
	std::wstring ToWString (const std::string& t);
		
	std::string ToLower(std::string inputString);

	template <class T>
	float ToFloat (const T& t)
	{
		#ifdef min
		#undef min
		#endif
		float returnValue = std::numeric_limits<float>::min();

		std::stringstream ss;
		ss << t;
		ss >> returnValue;

		return returnValue;
	}
	template <class T>
	double ToDouble (const T& t)
	{
		#ifdef min
		#undef min
		#endif
		double returnValue = std::numeric_limits<double>::min();

		std::stringstream ss;
		ss << t;
		ss >> returnValue;

		return returnValue;
	}
	template <class T>
	int ToInt (const T& t)
	{
		#ifdef min
		#undef min
		#endif
		int returnValue = std::numeric_limits<int>::min();

		std::stringstream ss;
		ss << t;
		ss >> returnValue;

		return returnValue;
	}
}

#endif //__StringConverter__