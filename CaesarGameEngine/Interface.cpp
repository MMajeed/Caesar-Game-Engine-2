#include "Interface.h"

void Interface::Run(double realTime, double deltaTime)
{
	this->SinceLastWork += realTime;

	this->ProccessMessages();
	this->Update(realTime, deltaTime);

	if(SinceLastWork <= 0.012)
	{
		this->Work();
		this->SinceLastWork = 0.0;
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