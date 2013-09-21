#ifndef __Message__
#define __Message__

class Message
{
public:	
	enum class Status{ Incomplete, InProcess , Complete, Unvalid };

	Message();

	virtual void Proccess();

	virtual Status Work() = 0;

	virtual void WaitTillProcccesed();

	Status MessageStatus;
};

#endif //__Message__