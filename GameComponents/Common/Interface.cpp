#include "Interface.h"

#include <iomanip>
#include <thread>
#include <chrono>
#include "Logger.h"

Interface::Interface()
{
	this->running = true;
	this->timer.FrameCount = 0;
	this->timer.start = std::chrono::system_clock::now();
}

void Interface::Run()
{
	try
	{
		// setup the frame timer
		std::chrono::time_point<std::chrono::system_clock> start, end;
		start = std::chrono::system_clock::now();

		while( running == true )
		{
			// update timer
			end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = end - start;
			double frameTime = elapsed_seconds.count();
			double deltaTime = frameTime;

			const double MIN_TIMESTEP = 0.015;
			if ( deltaTime > MIN_TIMESTEP )
			{
				deltaTime = MIN_TIMESTEP;
			}

			this->ProccessMessages();
			this->Update(frameTime, deltaTime);
			this->Work();
			this->ProccessMessages();

			// update fps
			start = end;
			++(timer.FrameCount);

			// update timer
			std::chrono::time_point<std::chrono::system_clock> afterProcessTime = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsedProcessTime = afterProcessTime - end;

			if(elapsedProcessTime.count() < 15)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds((int)(15 - elapsedProcessTime.count())));
			}
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
			this->QueueMessages.pop();
		}
		
		msg->Proccess();
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