#include "InputManager.h"

InputManager::InputManager()
{

}

void InputManager::Init()
{

}
void InputManager::Update(double realTime, double deltaTime)
{
	for(auto iter = this->objects.begin();
		iter != this->objects.end();
		++iter)
	{
		iter->second.Update(realTime);
	}
}
void InputManager::Work()
{

}
void InputManager::Shutdown()
{

}

void InputManager::UpdateKeyStatus(unsigned int key, KeyStatus::Status status)
{
	this->objects[key].UpdateStatus(status);
}

const CHL::MapQ<unsigned int, KeyStatus> InputManager::AllObjects()
{
	return this->objects;
}