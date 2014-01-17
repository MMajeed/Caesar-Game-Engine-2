#include "Interface.h"

#include <iomanip>
#include <thread>
#include <chrono>
#include <Windows.h>
#include "Logger.h"

Interface::Interface()
{
	this->running = true;
	this->timer.AbsoluteTime = 0.0;
	this->timer.FrameCount = 0;
}

void Interface::Run()
{
	try
	{
		// setup the frame timer
		LARGE_INTEGER timerFrequency = { 0 };
		LARGE_INTEGER timerBase = { 0 };
		LARGE_INTEGER timerLast = { 0 };
		LARGE_INTEGER timerNow = { 0 };
		LARGE_INTEGER timerWorked = { 0 };
		if( !QueryPerformanceFrequency( &timerFrequency ) ) 
			Logger::LogError("QueryPerformanceFrequency() failed to create a high-performance timer.");
		double tickInterval = static_cast<double>( timerFrequency.QuadPart );

		if( !QueryPerformanceCounter( &timerBase ) )
			Logger::LogError("QueryPerformanceCounter() failed to read the high-performance timer.");
		timerLast = timerBase;

		this->timer.FrameCount = 0;

		while( running == true )
		{
			// update timer
			if( !QueryPerformanceCounter( &timerNow ) )
				Logger::LogError("QueryPerformanceCounter() failed to update the high-performance timer.");
			long long elapsedCount = timerNow.QuadPart - timerBase.QuadPart;
			long long elapsedFrameCount = timerNow.QuadPart - timerLast.QuadPart;
			this->timer.AbsoluteTime = elapsedCount / tickInterval;
			double frameTime = elapsedFrameCount / tickInterval;

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
			timerLast = timerNow;
			++(timer.FrameCount);

			// update timer
			if( !QueryPerformanceCounter( &timerWorked ) )
				Logger::LogError("QueryPerformanceCounter() failed to update the high-performance timer.");
			elapsedFrameCount = timerWorked.QuadPart - timerNow.QuadPart ;
			double timeWorked = elapsedFrameCount / tickInterval;;
			timeWorked *= 1000;

			if(timeWorked < 15)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds((int)(15 - timeWorked)));
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
			std::lock_guard<std::mutex> lock(this->mutex);
			msg = this->QueueMessages.front();
		}
		
		msg->Proccess();

		{
			std::lock_guard<std::mutex> lock(this->mutex);
			this->QueueMessages.pop();
		}
	}
}

void Interface::SubmitMessage(std::shared_ptr<Message> msg)
{
    std::lock_guard<std::mutex> lock(this->mutex);
	this->QueueMessages.push(msg);
}

Interface::~Interface()
{

}