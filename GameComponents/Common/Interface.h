#ifndef __Interface__
#define __Interface__

#include <queue>
#include <string>
#include <memory>
#include <mutex>
#include <chrono>
#include <atomic>
#include "Message.h"

class CommonDLL_API Interface
{
public:
	Interface();

	virtual void Init() = 0; // Inits the internal working 
	virtual void Run(double frameTime);
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
		std::atomic<long long>		FrameCount;
		std::atomic<unsigned int>	NumberOfFramePerSeconds;
	} timer;

	std::mutex mutex;
	std::mutex messageMutex;

	bool running;	

	bool AnyMessage();
	std::weak_ptr<Message> GetBackMessage();
protected:
	std::queue<std::shared_ptr<Message>> QueueMessages;	
};

#endif