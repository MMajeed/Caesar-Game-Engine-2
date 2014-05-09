#ifndef __Logger__
#define __Logger__

#include "Linker.h"
#include <string>
#include <vector>
#include <functional>

namespace Logger
{
	CaesarLoggerLibraryDLL_API void LogInformation(std::string message);
	CaesarLoggerLibraryDLL_API void LogError(std::string message);
	static std::vector<std::function<void(std::string)>> InformationLogger;
	static std::vector<std::function<void(std::string)>> ErrorLogger;
	CaesarLoggerLibraryDLL_API void AddInformationLogger(std::function<void(std::string)> func);
	CaesarLoggerLibraryDLL_API void AddErrorLogger(std::function<void(std::string)> func);
}

#endif //__Logger__