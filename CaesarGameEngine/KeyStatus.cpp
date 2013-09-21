#include "KeyStatus.h"

KeyStatus::KeyStatus()
{
	this->CurrentStatus = KeyStatus::Status::Down;
	this->duration = 0.0;
}

void KeyStatus::UpdateStatus(Status status)
{
	if(this->CurrentStatus != status)
	{
		this->CurrentStatus = status;
		this->duration = 0.0;
	}
}

void KeyStatus::Update(double realTime)
{
	this->duration += realTime;
}