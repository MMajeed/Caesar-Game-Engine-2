#ifndef __LuaManager__
#define __LuaManager__

//#include <lua-5.2.2\lua.hpp>
// <<extern "C">> not supplied automatically because Lua also compiles as C++

extern "C" {
#include <lua-5.1.0\lua.h>
#include <lua-5.1.0\\lualib.h>
#include <lua-5.1.0\\lauxlib.h>
}

#include <luabind\luabind.hpp>

#include <Singleton.h>

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
	bool FileRun;
};

#endif //__LuaManager__