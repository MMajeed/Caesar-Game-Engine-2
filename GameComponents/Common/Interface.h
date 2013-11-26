#ifndef __Interface__
#define __Interface__

#include <queue>
#include <string>
#include <memory>
#include <mutex>
#include "Message.h"

class Interface
{
public:
	Interface();

	virtual void Init() = 0;
	virtual void Run();
	virtual void Shutdown() = 0;	

	virtual void ProccessMessages();
	virtual void Update(double realTime, double deltaTime) = 0;
	virtual void Work() = 0;

	virtual void SubmitMessage(std::shared_ptr<Message> msg);

	virtual ~Interface();

	// timer stuff
	struct
	{
		double 	  	AbsoluteTime;
		long long	FrameCount;
	} timer;

	std::mutex mutex;

	bool running;	
protected:
	std::queue<std::shared_ptr<Message>> QueueMessages;	
};

#endif