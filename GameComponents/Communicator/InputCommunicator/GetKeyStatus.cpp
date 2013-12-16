#include "GetKeyStatus.h"
#include <InputManager.h>

namespace GetKeyStatus
{
	GetKeyStatus::KeyState GetKey(unsigned int keyID)
	{
		std::hash_map<unsigned int, KeyStatus> keys;

		{
			std::lock_guard<std::mutex> lock(InputManager::GetInstance().mutex);
			keys = InputManager::GetInstance().AllObjects();
		}

		std::hash_map<unsigned int, KeyStatus>::const_iterator key = keys.find(keyID);

		if(key == keys.end())
		{
			return GetKeyStatus::KeyState::KeyUp;
		}
		else
		{
			return static_cast<GetKeyStatus::KeyState>(key->second.CurrentStatus);
		}
	}
}