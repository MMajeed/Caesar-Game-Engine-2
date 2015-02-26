#ifndef __ScriptEntity__
#define __ScriptEntity__

#include "Linker.h"

#include <Lua.hpp>
#include <Singleton.h>

class ScriptEntityDLL_API ScriptEntity : public CHL::Singleton<ScriptEntity>
{
protected:
	ScriptEntity();
	ScriptEntity(const ScriptEntity& that) = delete;
	ScriptEntity& operator=(const ScriptEntity&) = delete;
	friend CHL::Singleton<ScriptEntity>;
public:
	static void Init(lua_State *lua);
};

static ScriptEntity& ScriptEntityTemp = ScriptEntity::GetInstance();

#endif //__ScriptEntity__
