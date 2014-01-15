#include "GetMouseStatus.h"
#include <InputManager.h>

namespace Mouse
{
	std::pair<long, long> GetLoc()
	{
		return InputManager::GetInstance().CursorPosition();
	}
}