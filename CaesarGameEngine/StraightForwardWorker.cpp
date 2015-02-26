#include "StraightForwardWorker.h"

#include <thread>

StraightForwardWorker::StraightForwardWorker() 
	: NumberOfFramePerSeconds(12000)
{

}

void StraightForwardWorker::Run()
{
	// setup the frame timer
	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

	while(true)
	{
		// update timer
		start = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = start - end;
		double frameTime = elapsed_seconds.count();

		for(const auto& iter : this->ComponentList)
		{
			iter.Component->Run(frameTime);
		}

		// update timer
		std::chrono::time_point<std::chrono::system_clock> afterWork = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsedWorkTime = afterWork - end;

		std::chrono::duration<double> minWorkTime(2. / this->NumberOfFramePerSeconds);
		if(elapsedWorkTime < minWorkTime)
		{
			std::chrono::duration<double, std::milli> timeToSleep = minWorkTime - elapsedWorkTime;
			std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::milliseconds>(timeToSleep));
		}
		// update fps
		end = start;
	}
}

void StraightForwardWorker::AddComponent(std::shared_ptr<Interface> pInterface, unsigned int Priority)
{
	StraightForwardWorker::ComponentInfo newCI;

	newCI.Component = pInterface;
	newCI.Priority = Priority;

	this->ComponentList.push_back(newCI);

	this->ComponentList.sort([](const StraightForwardWorker::ComponentInfo &a, const StraightForwardWorker::ComponentInfo  &b) 
	{
		return a.Priority > b.Priority;
	});

	pInterface->Init();
}
