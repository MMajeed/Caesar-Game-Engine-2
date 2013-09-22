#ifndef __AddKeyStateAction__
#define __AddKeyStateAction__

#include <string>

#include "Message.h"

#include <luabind\luabind.hpp>

class AddKeyStateAction : public Message
{
public:	
	enum class StateWanted { KeyUp = 0, KeyDown = 1 };

	AddKeyStateAction(unsigned int inputKey, StateWanted inputState, luabind::object inputFunction);

	Status Work();
	
	StateWanted state;
	unsigned int key;
	luabind::object function;
	std::string ID;
};

#endif //__AddKeyStateAction__
