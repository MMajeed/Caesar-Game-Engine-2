#include "UpdateKey.h"
#include <InputManager.h>

UpdateKey::UpdateKey(unsigned int inputKey, bool keyStatus)
{
	this->currentStatus = keyStatus;
	this->key = inputKey;
}

Message::Status UpdateKey::Work() 
{
	std::lock_guard<std::mutex> lock(InputManager::GetInstance().mutex);

	KeyStatus::Status status = this->currentStatus ? KeyStatus::Status::KeyDown : KeyStatus::Status::KeyUp;

	InputManager::GetInstance().UpdateKeyStatus(this->key, status);

	return Message::Status::Complete;
}