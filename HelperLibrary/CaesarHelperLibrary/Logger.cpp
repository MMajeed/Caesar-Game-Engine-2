#include "Logger.h"
#include <iostream>
#include <thread>
#include <Windows.h>
#include <sstream>
#include "Converter.h"

void Logger::LogInformation(std::string message)
{
	for(std::function<void(std::string)>& func : Logger::InformationLogger)
	{
		func(message);
	}
}
void Logger::LogError(std::string message)
{
	for(std::function<void(std::string)>& func : Logger::ErrorLogger)
	{
		func(message);
	}
	
	std::exit(0);
}

void Logger::AddInformationLogger(std::function<void(std::string)> func)
{
	Logger::InformationLogger.push_back(func);
}
void Logger::AddErrorLogger(std::function<void(std::string)> func)
{
	Logger::ErrorLogger.push_back(func);
}