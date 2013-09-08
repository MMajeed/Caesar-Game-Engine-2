#ifndef __LuaManager__
#define __LuaManager__

#include <lua-5.2.2\lua.hpp>
#include <Singleton.h>
#include <MapQueryable.h>

#include "Interface.h"

class LuaManager : public Interface, public CHL::Singelton<LuaManager>
{
public:
	LuaManager();

	virtual void Init();
	virtual void Update(double realTime, double deltaTime);
	virtual void Work();
	virtual void Shutdown();

	lua_State *lua;
};

#endif //__LuaManager__