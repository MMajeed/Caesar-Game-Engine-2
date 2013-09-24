#ifndef __InputManager__
#define __InputManager__

#include "Interface.h"

#include "KeyStatus.h"

#include <Singleton.h>
#include <Queryable.h>
#include <memory>

class InputManager : public Interface, public CHL::Singelton<InputManager>
{
protected:	
	InputManager();
public:
	virtual void Init();
	virtual void Update(double realTime, double deltaTime);
	virtual void Work();
	virtual void Shutdown();

	void UpdateKeyStatus(unsigned int, KeyStatus::Status);

	const CHL::MapQ<unsigned int, KeyStatus> AllObjects();
protected:
	CHL::MapQ<unsigned int, KeyStatus> objects;

	friend CHL::Singelton<InputManager>;
};

#endif //__InputManager__