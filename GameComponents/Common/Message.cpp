#include "Message.h"
#include <boost/thread.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"

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
		boost::this_thread::sleep(boost::posix_time::milliseconds(sleepFor));
		sleepFor *= 2;
	}
}