#ifndef __GetKeyStatus__
#define __GetKeyStatus__

#include "Linker.h"

namespace GetKeyStatus
{
	enum class KeyState{ KeyUp = 0, KeyDown = 1 };

	GetKeyStatus::KeyState GetKey(unsigned int keyID);
}

#endif //__GetKeyStatus__