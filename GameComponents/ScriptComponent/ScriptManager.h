#ifndef __ScriptManager__
#define __ScriptManager__

#include "Linker.h"

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include <Singleton.h>
#include <hash_map>
#include <memory>
#include <functional>
#include <Interface.h>
#include "LuaProcesses.h"

class ScriptComponentDLL_API ScriptManager : public Interface, public CHL::Singleton<ScriptManager>
{
protected:
	ScriptManager();
	ScriptManager(const ScriptManager& that) = delete;
	ScriptManager& operator=(const ScriptManager&) = delete;
	friend CHL::Singleton<ScriptManager>;
public:
	virtual void Init();
	virtual void Work(double realTime, double deltaTime);
	virtual void Shutdown();

	lua_State *lua;

	virtual void ActivateLuaClassesNFunction();

	virtual void SubmitProcesses(std::string ID, std::shared_ptr<LuaProcesses> process);
	virtual void RemoveProcesses(std::string ID);

protected:
	std::hash_map<std::string, std::shared_ptr<LuaProcesses>> allProcesses;
};

#endif //__ScriptManager__