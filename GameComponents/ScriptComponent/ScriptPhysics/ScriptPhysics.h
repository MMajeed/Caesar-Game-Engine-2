#ifndef __ScriptPhysics__
#define __ScriptPhysics__

#include "Linker.h"

#include <Lua.hpp>
#include <Singleton.h>

class ScriptPhysicsDLL_API ScriptPhysics : public CHL::Singleton<ScriptPhysics>
{
protected:
	ScriptPhysics();
	ScriptPhysics(const ScriptPhysics& that) = delete;
	ScriptPhysics& operator=(const ScriptPhysics&) = delete;
	friend CHL::Singleton<ScriptPhysics>;
public:
	static void Init(lua_State *lua);
};

#endif //__ScriptPhysics__
