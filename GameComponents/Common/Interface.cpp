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

void Interface::Run(double frameTime)
{
	try
	{
		if( running == true )
		{
			double deltaTime = frameTime;

			/*const double MIN_TIMESTEP = 0.015;
			if ( deltaTime > MIN_TIMESTEP )
			{
				deltaTime = MIN_TIMESTEP;
			}*/

			this->ProccessMessages();
			this->Work(frameTime, deltaTime);
			this->ProccessMessages();

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
	//this->Run();
}

bool Interface::AnyMessage()
{
	return this->QueueMessages.empty();
}
std::weak_ptr<Message> Interface::GetBackMessage()
{
	std::lock_guard<std::mutex> lock(this->messageMutex);
	if(!(this->QueueMessages.empty()))
	{
		return this->QueueMessages.back();
	}
	else
	{

		return std::weak_ptr<Message>();
	}
}

Interface::~Interface()
{

}