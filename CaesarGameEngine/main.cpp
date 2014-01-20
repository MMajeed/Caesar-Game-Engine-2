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

	for(auto iter = vInterfaces.begin();
		iter != vInterfaces.end();
		++iter)
	{
		std::shared_ptr<std::thread> thread
			= std::shared_ptr<std::thread>(new std::thread(std::bind(&Interface::Start, iter->second)));

		vThreads.push_back(thread);
	}


	LARGE_INTEGER timerBase = {0};
	LARGE_INTEGER timerNow = {0};
	LARGE_INTEGER timerFrequency = {0};
	if(!QueryPerformanceCounter(&timerBase))
		Logger::LogError("QueryPerformanceCounter() failed to read the high-performance timer.");
	if(!QueryPerformanceFrequency(&timerFrequency))
		Logger::LogError("QueryPerformanceFrequency() failed to create a high-performance timer.");
	double tickInterval = static_cast<double>(timerFrequency.QuadPart);

	std::map<std::string, long long> vLastFrame;
	vLastFrame["Graphic"] = 0;
	vLastFrame["Lua"] = 0;
	vLastFrame["Input"] = 0;
	double lastAbsoluteTime = 0.0;

	while(running == true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds((int)(5000)));

		if(!QueryPerformanceCounter(&timerNow))
			Logger::LogError("QueryPerformanceCounter() failed to update the high-performance timer.");
		long long elapsedCount = timerNow.QuadPart - timerBase.QuadPart;
		double AbsoluteTime = elapsedCount / tickInterval;

		double timeDifference = AbsoluteTime - lastAbsoluteTime;

		std::ostringstream fr;
		fr << std::setprecision(2) << std::fixed;
		fr << "Frame Rate: ";
		for(auto interFaceIter = vInterfaces.begin();
			interFaceIter != vInterfaces.end();
			++interFaceIter)
		{
			long long frameDifference = interFaceIter->second->timer.FrameCount - vLastFrame[interFaceIter->first];
			double frameTimer = frameDifference / timeDifference;

			fr << interFaceIter->first.c_str() << " : ";
			fr << frameTimer << ". ";

			vLastFrame[interFaceIter->first] = interFaceIter->second->timer.FrameCount;
		}
		Logger::LogInformation(fr.str());

		lastAbsoluteTime = AbsoluteTime;
	}

	return 1;
}