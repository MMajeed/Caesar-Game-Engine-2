#ifndef __LuaManager__
#define __LuaManager__

#include "Linker.h"

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include <Singleton.h>
#include <hash_map>
#include <memory>

#include <Interface.h>
#include "LuaProcesses.h"

class LuaManager : public Interface, public CHL::Singleton<LuaManager>
{
protected:
	LuaManager();
	LuaManager(const LuaManager& that) = delete;
	LuaManager& operator=(const LuaManager&) = delete;
	friend CHL::Singleton<LuaManager>;
public:
	virtual void Init();
	virtual void Update(double realTime, double deltaTime);
	virtual void Work();
	virtual void Shutdown();

	lua_State *lua;
	bool FileRun;

	virtual void SubmitProcesses(std::string ID, std::shared_ptr<LuaProcesses> process);
	virtual void RemoveProcesses(std::string ID);
protected:
	std::hash_map<std::string, std::shared_ptr<LuaProcesses>> allProcesses;
};

#endif //__LuaManager__