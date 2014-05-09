#ifndef __GetKeyStatus__
#define __GetKeyStatus__

#include "Linker.h"
#include <InputKeysEnum.h>

namespace GetKeyStatus
{
	InputCommunicatorDLL_API InputKeysEnum::KeyStatus GetKey(InputKeysEnum::KeyCode keyID);
}

#endif //__GetKeyStatus__