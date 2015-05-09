#include "HalfAndHalfWorker.h"

#include <thread>
#include <condition_variable>

HalfAndHalfWorker::HalfAndHalfWorker(unsigned int fps)
	: iWorker(fps)
{

}

void HalfAndHalfWorker::Run()
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

		for(const auto& iter : this->FirstComponentList)
		{
			iter.Component->Run(frameTime);
		}

		// This loop sets tells all the parallelcomponents to start working again
		for(const auto& iter : this->ParallelComponentList)
		{
			std::unique_lock<std::mutex> lk(iter->m);

			iter->Running = true;
			iter->cv.notify_all();
		}

		// This loop waits until all the ParallelComponentList to finish their work
		for(const auto& iter : this->ParallelComponentList)
		{
			std::unique_lock<std::mutex> lk(iter->m);
			iter->cv.wait(lk, [=] { return iter->Running == false; });
		}

		for(const auto& iter : this->LastComponentList)
		{
			iter.Component->Run(frameTime);
		}

		// update timer
		std::chrono::time_point<std::chrono::system_clock> afterWork = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsedWorkTime = afterWork - end;

		std::chrono::duration<double> minWorkTime(1. / this->NumFPS);
		if(elapsedWorkTime < minWorkTime)
		{
			std::chrono::duration<double, std::milli> timeToSleep = minWorkTime - elapsedWorkTime;
			std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::milliseconds>(timeToSleep));
		}
		// update fps
		end = start;
	}
}

void HalfAndHalfWorker::ChangeFPS(unsigned int p)
{
	this->NumFPS = p;
}

void HalfAndHalfWorker::AddComponent(std::shared_ptr<Interface> pInterface,
									 unsigned int Priority,
									 int Parameter)
{
	if(Parameter == (int)HalfAndHalfWorker::ComponentParameter::First)
	{
		this->AddFirstComponent(pInterface, Priority);
	}
	else if(Parameter == (int)HalfAndHalfWorker::ComponentParameter::Last)
	{
		this->AddLastComponent(pInterface, Priority);
	}
	else
	{
		this->AddParallelComponent(pInterface);
	}
}


void HalfAndHalfWorker::AddFirstComponent(std::shared_ptr<Interface> pInterface, unsigned int Priority)
{
	HalfAndHalfWorker::ForwardManager newCI;

	newCI.Component = pInterface;
	newCI.Priority = Priority;

	this->FirstComponentList.push_back(newCI);

	this->FirstComponentList.sort([](const HalfAndHalfWorker::ForwardManager &a, const HalfAndHalfWorker::ForwardManager &b)
	{
		return a.Priority > b.Priority;
	});

	pInterface->Init();
}
void HalfAndHalfWorker::AddParallelComponent(std::shared_ptr<Interface> pInterface)
{
	std::shared_ptr<HalfAndHalfWorker::ParallelManager> newManager(new HalfAndHalfWorker::ParallelManager(pInterface));

	this->ParallelComponentList.push_back(newManager);
}
void HalfAndHalfWorker::AddLastComponent(std::shared_ptr<Interface> pInterface, unsigned int Priority)
{
	HalfAndHalfWorker::ForwardManager newCI;

	newCI.Component = pInterface;
	newCI.Priority = Priority;

	this->LastComponentList.push_back(newCI);

	this->LastComponentList.sort([](const HalfAndHalfWorker::ForwardManager &a, const HalfAndHalfWorker::ForwardManager &b)
	{
		return a.Priority > b.Priority;
	});

	pInterface->Init();
}


// ************************************************************************************* //

HalfAndHalfWorker::ParallelManager::ParallelManager(std::shared_ptr<Interface> pInterface)
	: Component(pInterface), Running(false)
{
	this->Thread
		= std::shared_ptr<std::thread>(new std::thread(std::bind(&HalfAndHalfWorker::ParallelManager::Run, this)));
}

void HalfAndHalfWorker::ParallelManager::Run()
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
			cv.wait(lk, [=] { return Running; }); // Wait until it is turned back to true
		}

		// update timer
		start = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = start - end;
		double frameTime = elapsed_seconds.count();

		this->Component->Run(frameTime);

		// update fps
		end = start;

		{
			std::unique_lock<std::mutex> lk(m);
			this->Running = false; // Set it to false
			cv.notify_all();
		}
	}
}
