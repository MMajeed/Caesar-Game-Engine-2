#ifndef __ScriptInput__
#define __ScriptInput__

#include "Linker.h"

#include <Lua.hpp>
#include <Singleton.h>

class ScriptInputDLL_API ScriptInput : public CHL::Singleton<ScriptInput>
{
protected:
	ScriptInput();
	ScriptInput(const ScriptInput& that) = delete;
	ScriptInput& operator=(const ScriptInput&) = delete;
	friend CHL::Singleton<ScriptInput>;
public:
	static void Init(lua_State *lua);
};

static ScriptInput& ScriptInputEntity = ScriptInput::GetInstance();

#endif //__ScriptInput__