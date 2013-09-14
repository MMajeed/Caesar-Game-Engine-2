#ifndef __Interface__
#define __Interface__

#include <queue>
#include <string>
#include <memory>

class Message
{
public:
	virtual void Proccess() = 0;
};

class Interface
{
public:
	Interface(std::string name) : Name(name){}

	virtual void Init() = 0;
	virtual void Run();
	virtual void Shutdown() = 0;

	virtual void SubmitMessage(std::shared_ptr<Message> msg);

	virtual ~Interface();

	std::string Name;

	// timer stuff
	struct
	{
		double 	  	AbsoluteTime;
		long long	FrameCount;
		double 	  	SinceLastWork;
	} timer;
protected:
	virtual void ProccessMessages();
	virtual void Update(double realTime, double deltaTime) = 0;
	virtual void Work() = 0;

	std::queue<std::shared_ptr<Message>> QueueMessages;
};

#endif