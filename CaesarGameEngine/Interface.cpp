#include "Interface.h"

#include <iomanip>

#include <Windows.h>

Interface::Interface()
{
	this->running = true;
	this->timer.AbsoluteTime = 0.0;
	this->timer.FrameCount = 0;
	this->timer.SinceLastWork = 0.0;
}

void Interface::Run()
{
	// setup the frame timer
	LARGE_INTEGER timerFrequency = { 0 };
	LARGE_INTEGER timerBase = { 0 };
	LARGE_INTEGER timerLast = { 0 };
	LARGE_INTEGER timerNow = { 0 };
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
		timer.AbsoluteTime = elapsedCount / tickInterval;
		double frameTime = elapsedFrameCount / tickInterval;
		this->timer.SinceLastWork += frameTime;

		double deltaTime = this->timer.SinceLastWork;

		const double MIN_TIMESTEP = 0.001f;
		if ( deltaTime > MIN_TIMESTEP )
		{
			deltaTime = MIN_TIMESTEP;
		}

		this->ProccessMessages();
		this->Update(frameTime, deltaTime);

		if(this->timer.SinceLastWork >= 0.012)
		{
			this->Work();
			this->timer.SinceLastWork = 0.0;
		}

		// update fps
		timerLast = timerNow;
		++(timer.FrameCount);
	}
}

void Interface::ProccessMessages()
{
	while( !(this->QueueMessages.empty()) )
	{
		std::shared_ptr<Message> msg = this->QueueMessages.back();
		this->QueueMessages.pop();

		msg->Proccess();
	}
}

void Interface::SubmitMessage(std::shared_ptr<Message> msg)
{
	this->QueueMessages.push(msg);
}

Interface::~Interface()
{

}