#include "KeyStatus.h"

KeyStatus::KeyStatus()
{
	this->CurrentStatus = KeyStatus::Status::KeyUp;
}

void KeyStatus::UpdateStatus(Status status)
{
	if(this->CurrentStatus != status)
	{
		this->CurrentStatus = status;
	}
}