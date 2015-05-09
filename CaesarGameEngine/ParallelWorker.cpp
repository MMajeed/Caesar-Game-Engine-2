#include "ParallelWorker.h"

#include <thread>
#include <condition_variable>


ParallelWorker::ParallelWorker(unsigned int fps)
	: iWorker(fps)
{

}

void ParallelWorker::Run()
{
	for(const auto& iter : this->ComponentList)
	{
		std::unique_lock<std::mutex> lk(iter->m);

		iter->Running = true;
		iter->cv.notify_all();
	}

	while(true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds((int)(5000)));

	}
}

void ParallelWorker::ChangeFPS(unsigned int p)
{
	for(auto& iter : this->ComponentList)
	{
		iter->NumberOfFramePerSeconds = p;
	}
}

void ParallelWorker::AddComponent(std::shared_ptr<Interface> pInterface,
								  unsigned int Priority,
								  int Parameter)
{
	std::shared_ptr<ParallelWorker::ComponentManager> newManager(new ParallelWorker::ComponentManager(pInterface, this->NumFPS));

	ComponentList.push_back(newManager);
}

// ************************************************************************************* //

ParallelWorker::ComponentManager::ComponentManager(std::shared_ptr<Interface> pInterface, unsigned int NumberOfFramePerSeconds)
	: Component(pInterface), NumberOfFramePerSeconds(NumberOfFramePerSeconds), Running(false)
{
	this->Thread
		= std::shared_ptr<std::thread>(new std::thread(std::bind(&ParallelWorker::ComponentManager::Run, this)));
}

void ParallelWorker::ComponentManager::Run()
{
	this->Component->Init();
	
	// setup the frame timer
	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

	while(true)
	{
		// wait for the worker
		{
			std::unique_lock<std::mutex> lk(m);
			cv.wait(lk, [=] { return Running; });
		}

		// update timer
		start = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = start - end;
		double frameTime = elapsed_seconds.count();

		this->Component->Run(frameTime);

		// update timer
		std::chrono::time_point<std::chrono::system_clock> afterWork = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsedWorkTime = afterWork - end;

		std::chrono::duration<double> minWorkTime(1. / this->NumberOfFramePerSeconds);
		if(elapsedWorkTime < minWorkTime)
		{
			std::chrono::duration<double, std::milli> timeToSleep = minWorkTime - elapsedWorkTime;
			std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::milliseconds>(timeToSleep));
		}
		// update fps
		end = start;
	}
}
