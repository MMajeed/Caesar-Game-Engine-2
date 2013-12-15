#ifndef __InputManager__
#define __InputManager__

#include "Linker.h"

#include <Interface.h>
#include "KeyStatus.h"
#include <Singleton.h>
#include <hash_map>
#include <memory>

class InputManager : public Interface, public CHL::Singleton<InputManager>
{
protected:	
	InputManager();
	InputManager(const InputManager& that) = delete;
	InputManager& operator=(const InputManager&) = delete;
public:
	virtual void Init();
	virtual void Update(double realTime, double deltaTime);
	virtual void Work();
	virtual void Shutdown();

	void UpdateKeyStatus(unsigned int, KeyStatus::Status);

	const std::hash_map<unsigned int, KeyStatus> AllObjects();
protected:
	std::hash_map<unsigned int, KeyStatus> objects;

	friend CHL::Singleton<InputManager>;
};

#endif //__InputManager__
