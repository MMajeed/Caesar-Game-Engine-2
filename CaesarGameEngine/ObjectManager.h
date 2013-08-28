#ifndef __ObjectManager__
#define __ObjectManager__

#include <Singleton.h>
#include <MapQueryable.h>

#include "Interface.h"
#include "Object.h"

class ObjectManager : public Interface, public CHL::Singelton<ObjectManager>
{
public:
	CHL::MapQuerable<std::string, Object> objects;

	virtual void Init();
	virtual void Update(double realTime, double deltaTime);
	virtual void Run();
	virtual void Shutdown();
};

#endif //__ObjectManager__