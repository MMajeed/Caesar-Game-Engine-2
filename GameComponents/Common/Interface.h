#ifndef __Interface__
#define __Interface__

#include <queue>
#include <string>
#include <memory>
#include <mutex>
#include <chrono>
#include "Message.h"

class Interface
{
public:
	Interface();

	virtual void Init() = 0;
	virtual void Run();
	virtual void Shutdown() = 0;	

	virtual void ProccessMessages();
	virtual void Work(double realTime, double deltaTime) = 0;

	virtual void SubmitMessage(std::shared_ptr<Message> msg);

	virtual void Start();

	virtual ~Interface();

	// timer stuff
	struct
	{
		std::chrono::time_point<std::chrono::system_clock> start;
		long long	FrameCount;
	} timer;

	std::mutex mutex;
	std::mutex messageMutex;

	bool running;	

	bool AnyMessage();
protected:
	std::queue<std::shared_ptr<Message>> QueueMessages;	
};

#endif