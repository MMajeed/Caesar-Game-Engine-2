#ifndef __LuaManager__
#define __LuaManager__

#include "Linker.h"

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include <Singleton.h>
#include <vector>
#include <memory>

#include <Interface.h>
#include "LuaProcesses.h"

class LuaManager : public Interface, public CHL::Singleton<LuaManager>
{
protected:
	LuaManager();
	LuaManager(const LuaManager& that) = delete;
	LuaManager& operator=(const LuaManager&) = delete;
public:
	virtual void Init();
	virtual void Update(double realTime, double deltaTime);
	virtual void Work();
	virtual void Shutdown();

	lua_State *lua;
	bool FileRun;

	virtual void SubmitProcesses(std::shared_ptr<LuaProcesses> process);
protected:
	std::vector<std::shared_ptr<LuaProcesses>> allProcesses;

	friend CHL::Singleton<LuaManager>;
};

#endif //__LuaManager__