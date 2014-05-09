#include <exception>
#include <iostream>
#include <sstream>
#include <Converter.h>
#include <Logger.h>
#include <InputCommunicator\InputCommunicator.h>
#include <GraphicCommunicator\GraphicCommunicator.h>
#include <ScriptCommunicator\ScriptCommunicator.h>
#include <AnimationCommunicator\AnimationCommunicator.h>
#include <PhysicsCommunicator\PhysicsCommunicator.h>
#include <thread>
#include <map>
#include <iomanip>

void Print(std::string s)
{
	std::cout << s << "\n";
}

bool running = true;

int main()
{
	Logger::AddInformationLogger(Print);
	Logger::AddErrorLogger(Print);

	std::map<std::string, Interface*> vInterfaces;
	std::vector<std::shared_ptr<std::thread>> vThreads;

	vInterfaces["Graphic"] = GraphicCommunicator::GetComponent();
	vInterfaces["Lua"] = ScriptCommunicator::GetComponent();
	vInterfaces["Input"] = InputCommunicator::GetComponent();
	vInterfaces["Animation"] = AnimationCommunicator::GetComponent();
	vInterfaces["Physics"] = PhysicsCommunicator::GetComponent();

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
		std::this_thread::sleep_for(std::chrono::milliseconds((int)(5000)));
	}

	return 1;
}