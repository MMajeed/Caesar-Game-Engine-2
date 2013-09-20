#include "Message.h"
#include <boost/thread.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"

Message::Message(){ MessageStatus = Incomplete; }

void Message::Proccess()
{
	this->MessageStatus = InProcess;
	this->MessageStatus = this->Work();
}

void Message::WaitTillProcccesed()
{
	int sleepFor = 1;
	while(this->MessageStatus == Message::Incomplete
		|| this->MessageStatus == Message::InProcess)
	{
		boost::this_thread::sleep(boost::posix_time::milliseconds(sleepFor));
		sleepFor *= 2;
	}
}