#ifndef __ScriptManager__
#define __ScriptManager__

#include "Linker.h"

#include <Singleton.h>
#include <unordered_map>
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

	virtual void ActivateLuaClassesNFunction();

	virtual void SubmitProcesses(std::string ID, std::shared_ptr<LuaProcesses> process);
	virtual void RemoveProcesses(std::string ID);
};

#endif //__ScriptManager__