#ifndef __PhysicsManager__
#define __PhysicsManager__

#include "Linker.h"

#include <unordered_map>
#include <string>
#include <Interface.h>
#include <Singleton.h>

class PhysicsComponentDLL_API PhysicsManager : public Interface, public CHL::Singleton<PhysicsManager>
{
protected:
	PhysicsManager();
	PhysicsManager(const PhysicsManager&) = delete;
	PhysicsManager& operator=(const PhysicsManager&) = delete;
	friend CHL::Singleton<PhysicsManager>;
public:
	virtual void Init();
	virtual void Work(double realTime, double deltaTime);
	virtual void Shutdown();
};

#endif //__PhysicsManager__
