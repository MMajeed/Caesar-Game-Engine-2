#include "GetKeyStatus.h"
#include <InputManager.h>

namespace GetKeyStatus
{
	InputKeysEnum::KeyStatus GetKey(InputKeysEnum::KeyCode keyID)
	{
		return InputManager::GetInstance().GetCurrentKeyState(keyID);
	}
}