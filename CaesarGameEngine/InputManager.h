#ifndef __InputManager__
#define __InputManager__

#include "Interface.h"

#include "KeyStatus.h"

#include <Singleton.h>
#include <Queryable.h>
#include <memory>

class InputManager : public Interface, public CHL::Singelton<InputManager>
{
public:
	InputManager();
	virtual void Init();
	virtual void Update(double realTime, double deltaTime);
	virtual void Work();
	virtual void Shutdown();

	void UpdateKeyStatus(unsigned int, KeyStatus::Status);

	const CHL::MapQueryable<unsigned int, KeyStatus> AllObjects();
protected:	
	CHL::MapQueryable<unsigned int, KeyStatus> objects;
};

#endif //__InputManager__