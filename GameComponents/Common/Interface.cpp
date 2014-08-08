#include "Interface.h"

#include <iomanip>
#include <thread>
#include <chrono>
#include "Logger.h"
#include <iostream>

Interface::Interface()
{
	this->running = true;
	this->timer.FrameCount = 0;
	this->timer.start = std::chrono::system_clock::now();
	this->timer.NumberOfFramePerSeconds = 120;
}

void Interface::Run()
{
	try
	{
		// setup the frame timer
		std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
		std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

		while( running == true )
		{
			// update timer
			start = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = start - end;
			double frameTime = elapsed_seconds.count();
			double deltaTime = frameTime;

			/*const double MIN_TIMESTEP = 0.015;
			if ( deltaTime > MIN_TIMESTEP )
			{
				deltaTime = MIN_TIMESTEP;
			}*/

			this->ProccessMessages();
			this->Work(frameTime, deltaTime);
			this->ProccessMessages();

			// update timer
			std::chrono::time_point<std::chrono::system_clock> afterWork = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsedWorkTime = afterWork - end;

			std::chrono::duration<double> minWorkTime(2. / this->timer.NumberOfFramePerSeconds);
			if(elapsedWorkTime < minWorkTime)
			{
				std::chrono::duration<double, std::milli> timeToSleep = minWorkTime - elapsedWorkTime;
				std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::milliseconds>(timeToSleep));
			}
			// update fps
			end = start;
			timer.FrameCount += 1;
		}
	}
	catch(const std::exception& ex)
	{
		Logger::LogError(ex.what());
	}
}

void Interface::ProccessMessages()
{
	while( !(this->QueueMessages.empty()) )
	{

		std::shared_ptr<Message> msg;

		{
			std::lock_guard<std::mutex> lock(this->messageMutex);
			msg = this->QueueMessages.front();
		}
		
		if(msg)
		{
			msg->Proccess();

			std::lock_guard<std::mutex> lock(this->messageMutex);
			this->QueueMessages.pop();
		}

	}
}

void Interface::SubmitMessage(std::shared_ptr<Message> msg)
{
	std::lock_guard<std::mutex> lock(this->messageMutex);
	this->QueueMessages.push(msg);
}

void Interface::Start()
{
	this->Init();
	this->Run();
}

bool Interface::AnyMessage()
{
	return this->QueueMessages.empty();
}

Interface::~Interface()
{

}