#ifndef __UpdateKey__
#define __UpdateKey__

#include "Message.h"


class UpdateKey : public Message
{
public:
	// false is up, true is down
	UpdateKey(unsigned int inputKey, bool keyStatus);

	virtual Status Work();

	unsigned int key;
	bool currentStatus;
};

#endif //__InputManager__