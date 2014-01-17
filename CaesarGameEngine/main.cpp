#include <Windows.h>
#include <exception>
#include <iostream>
#include <sstream>
#include <Converter.h>
#include <Logger.h>
#include <InputCommunicator\InputCommunicator.h>
#include <GraphicCommunicator\GraphicCommunicator.h>
#include <ScriptCommunicator\ScriptCommunicator.h>
#include <thread>
#include <map>

void Print(std::string s)
{
	std::cout << s << "\n";
}

bool running = true;

int main()
{
	
	#ifdef _DEBUG
	Logger::AddInformationLogger(Print);
	#endif
	Logger::AddErrorLogger(Print);

	std::map<std::string, Interface*> vInterfaces;
	std::vector<std::shared_ptr<std::thread>> vThreads;

	vInterfaces["Graphic"] = GraphicCommunicator::GetComponent();
	vInterfaces["Lua"] = ScriptCommunicator::GetComponent();
	vInterfaces["Input Manager"] = InputCommunicator::GetComponent();


	for(auto iter = vInterfaces.begin();
		iter != vInterfaces.end();
		++iter)
	{
		std::shared_ptr<std::thread> thread
			= std::shared_ptr<std::thread>(new std::thread(std::bind(&Interface::Start, iter->second)));

		vThreads.push_back(thread);
	}

	while(running == true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds((int)(15)));
	}

	return 1;
}