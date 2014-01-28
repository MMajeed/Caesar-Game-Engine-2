#ifndef __Logger__
#define __Logger__

#include "Linker.h"
#include <string>
#include <vector>
#include <functional>

namespace Logger
{
	void LogInformation(std::string message);
	void LogError(std::string message);
	static std::vector<std::function<void(std::string)>> InformationLogger;
	static std::vector<std::function<void(std::string)>> ErrorLogger;
	void AddInformationLogger(std::function<void(std::string)> func);
	void AddErrorLogger(std::function<void(std::string)> func);
};

#endif //__Logger__