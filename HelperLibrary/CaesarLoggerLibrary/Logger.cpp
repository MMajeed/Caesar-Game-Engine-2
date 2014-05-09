#include "Logger.h"
#include <iostream>
#include <thread>
#include <Windows.h>
#include <sstream>

namespace Logger
{
	void LogInformation(std::string message)
	{
		for(std::function<void(std::string)>& func : Logger::InformationLogger)
		{
			func(message);
		}
	}
	void LogError(std::string message)
	{
		for(std::function<void(std::string)>& func : Logger::ErrorLogger)
		{
			func(message);
		}

		std::exit(0);
	}

	void AddInformationLogger(std::function<void(std::string)> func)
	{
		Logger::InformationLogger.push_back(func);
	}
	void AddErrorLogger(std::function<void(std::string)> func)
	{
		Logger::ErrorLogger.push_back(func);
	}
}
