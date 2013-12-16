#include "UpdateKey.h"
#include <InputManager.h>

void UpdateKey(unsigned int inputKey, bool keyStatus)
{
	class UpdateKeyMessage : public Message
	{
	public:
		// false is up, true is down
		UpdateKeyMessage(unsigned int inputKey, bool keyStatus)
		{
			this->currentStatus = keyStatus;
			this->key = inputKey;
		}

		virtual Status Work()
		{
			std::lock_guard<std::mutex> lock(InputManager::GetInstance().mutex);

			KeyStatus::Status status = this->currentStatus ? KeyStatus::Status::KeyDown : KeyStatus::Status::KeyUp;

			InputManager::GetInstance().UpdateKeyStatus(this->key, status);

			return Message::Status::Complete;
		}

		unsigned int key;
		bool currentStatus;
	};
	std::shared_ptr<UpdateKeyMessage> msg(new UpdateKeyMessage(inputKey, keyStatus));
	InputManager::GetInstance().SubmitMessage(msg);
}