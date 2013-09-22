#include "GetKeyStatus.h"
#include "InputManager.h"

GetKeyStatus::Key GetKeyStatus::GetKey(unsigned int keyID)
{
	boost::mutex::scoped_lock lock(InputManager().GetInstance().mutex);

	const CHL::MapQueryable<unsigned int, KeyStatus> keys = InputManager::GetInstance().AllObjects();

	CHL::MapQueryable<unsigned int, KeyStatus>::const_iterator key = keys.find(keyID);

	GetKeyStatus::Key returnValue;

	if(key != keys.end())
	{
		returnValue.state = static_cast<GetKeyStatus::Key::KeyState>(key->second.CurrentStatus);
		returnValue.key = keyID;
		returnValue.duration = key->second.duration;
	}
	else
	{
		returnValue.state = GetKeyStatus::Key::KeyState::KeyUp;
		returnValue.key = keyID;
		returnValue.duration = InputManager().GetInstance().timer.AbsoluteTime;
	}

	return returnValue;
}