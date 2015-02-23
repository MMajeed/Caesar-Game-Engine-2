#ifndef __Message__
#define __Message__

#include "Linker.h"

#include <functional>

class CommonDLL_API Message
{
public:	
	enum class Status{ Incomplete, InProcess , Complete, Unvalid };

	Message();

	virtual void Proccess();

	virtual Status Work() = 0;

	virtual void WaitTillProcccesed();

	Status MessageStatus;
};

class CommonDLL_API FuncMessage : public Message
{
public:
	FuncMessage(std::function<Message::Status()> p);

	std::function<Message::Status()> work;

	virtual Message::Status Work();
};

#endif //__Message__