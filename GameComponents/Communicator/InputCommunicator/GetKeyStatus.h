#ifndef __GetKeyStatus__
#define __GetKeyStatus__

#include "Linker.h"

class GetKeyStatus
{
public:
	struct Key
	{
		enum class KeyState{ KeyUp = 0, KeyDown = 1 };
		KeyState state;
		double duration;
		unsigned int key;
	};

	static GetKeyStatus::Key GetKey(unsigned int keyID);
};

#endif //__GetKeyStatus__