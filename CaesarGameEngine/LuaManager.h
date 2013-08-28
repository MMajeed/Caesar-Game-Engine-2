#ifndef __LuaManager__
#define __LuaManager__

#include <Singleton.h>
#include <MapQueryable.h>

#include "Interface.h"

class LuaManager : public Interface, public CHL::Singelton<LuaManager>
{
public:
	virtual void Init();
	virtual void Update(double realTime, double deltaTime);
	virtual void Run();
	virtual void Shutdown();
};

#endif //__LuaManager__