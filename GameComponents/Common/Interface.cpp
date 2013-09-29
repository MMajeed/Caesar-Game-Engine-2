#include "Interface.h"

#include <iomanip>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <Windows.h>

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
			throw std::exception( "QueryPerformanceFrequency() failed to create a high-performance timer." );
		double tickInterval = static_cast<double>( timerFrequency.QuadPart );

		if( !QueryPerformanceCounter( &timerBase ) )
			throw std::exception( "QueryPerformanceCounter() failed to read the high-performance timer." );
		timerLast = timerBase;

		this->timer.FrameCount = 0;

		while( running == true )
		{
			// update timer
			if( !QueryPerformanceCounter( &timerNow ) )
				throw std::exception( "QueryPerformanceCounter() failed to update the high-performance timer." );
			long long elapsedCount = timerNow.QuadPart - timerBase.QuadPart;
			long long elapsedFrameCount = timerNow.QuadPart - timerLast.QuadPart;
			this->timer.AbsoluteTime = elapsedCount / tickInterval;
			double frameTime = elapsedFrameCount / tickInterval;

			double deltaTime = frameTime;

			/*const double MIN_TIMESTEP = 0.001f;
			if ( deltaTime > MIN_TIMESTEP )
			{
				deltaTime = MIN_TIMESTEP;
			}*/

			this->ProccessMessages();
			this->Update(frameTime, deltaTime);
			this->Work();

			// update fps
			timerLast = timerNow;
			++(timer.FrameCount);

			// update timer
			if( !QueryPerformanceCounter( &timerWorked ) )
				throw std::exception( "QueryPerformanceCounter() failed to update the high-performance timer." );
			elapsedFrameCount = timerWorked.QuadPart - timerNow.QuadPart ;
			double timeWorked = elapsedFrameCount / tickInterval;;
			timeWorked *= 1000;

			if(timeWorked < 15)
			{
				boost::this_thread::sleep(boost::posix_time::milliseconds((int)(15 - timeWorked)));
			}
		}
	}
	catch(std::exception ex)
	{
		throw;
	}
	catch( ... )
	{
		throw;
	}
}

void Interface::ProccessMessages()
{
	while( !(this->QueueMessages.empty()) )
	{

		std::shared_ptr<Message> msg;

		{
			boost::mutex::scoped_lock lock(this->mutex);
			msg = this->QueueMessages.front();
		}
		
		msg->Proccess();

		{
			boost::mutex::scoped_lock lock(this->mutex);
			this->QueueMessages.pop();
		}
	}
}

void Interface::SubmitMessage(std::shared_ptr<Message> msg)
{
	boost::mutex::scoped_lock lock(this->mutex);
	this->QueueMessages.push(msg);
}

Interface::~Interface()
{

}