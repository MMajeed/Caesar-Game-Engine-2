#include "InputManager.h"
#include <Windows.h>

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

InputKeysEnum::KeyStatus InputManager::GetCurrentKeyState(InputKeysEnum::KeyCode key)
{
	short state = GetAsyncKeyState(static_cast<int>(key));
	if(state < 0)
	{
		return InputKeysEnum::KeyStatus::KeyDown;
	}
	else 
	{
		return InputKeysEnum::KeyStatus::KeyUp;
	}
}


std::pair<long, long> InputManager::CursorPosition()
{
	POINT p;
	GetCursorPos(&p);
	return std::make_pair(p.x, p.y);
}