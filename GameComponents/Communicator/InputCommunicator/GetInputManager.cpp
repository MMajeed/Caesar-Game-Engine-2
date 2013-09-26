#include "GetInputManager.h"

#include <InputManager.h>

Interface* GetInputManager::GetComponent()
{
	return &InputManager::GetInstance();
}