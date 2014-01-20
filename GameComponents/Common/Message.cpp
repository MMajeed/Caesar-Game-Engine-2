#include "Message.h"
#include <thread>

Message::Message(){ MessageStatus = Message::Status::Incomplete; }

void Message::Proccess()
{
	this->MessageStatus = Message::Status::InProcess;
	this->MessageStatus = this->Work();
}

void Message::WaitTillProcccesed()
{
	int sleepFor = 1;
	while(this->MessageStatus == Message::Status::Incomplete
		|| this->MessageStatus == Message::Status::InProcess)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds((int)(sleepFor)));
		sleepFor *= 2;
	}
}