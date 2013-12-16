#include "InputManager.h"

InputManager::InputManager()
{

}

void InputManager::Init()
{

}
void InputManager::Update(double realTime, double deltaTime)
{
	
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

const std::hash_map<unsigned int, KeyStatus> InputManager::AllObjects()
{
	return this->objects;
}