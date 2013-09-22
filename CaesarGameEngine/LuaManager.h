#ifndef __LuaManager__
#define __LuaManager__

//#include <lua-5.2.2\lua.hpp>
// <<extern "C">> not supplied automatically because Lua also compiles as C++

extern "C" {
#include <lua5.1.5\lua.h>
#include <lua5.1.5\lualib.h>
#include <lua5.1.5\lauxlib.h>
}

#include <luabind\luabind.hpp>
#include <Singleton.h>
#include <Queryable.h>
#include <memory>

#include "Interface.h"
#include "LuaProcesses.h"

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

	virtual void SubmitProcesses(std::shared_ptr<LuaProcesses> process);
protected:
	CHL::VectorQueryable<std::shared_ptr<LuaProcesses>> allProcesses;
};

#endif //__LuaManager__