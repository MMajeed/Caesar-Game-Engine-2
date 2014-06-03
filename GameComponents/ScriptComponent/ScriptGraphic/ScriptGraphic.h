#ifndef __ScriptGraphic__
#define __ScriptGraphic__

#include "Linker.h"

#include <Lua.hpp>
#include <Singleton.h>

class ScriptGraphicDLL_API ScriptGraphic : public CHL::Singleton<ScriptGraphic>
{
protected:
	ScriptGraphic();
	ScriptGraphic(const ScriptGraphic& that) = delete;
	ScriptGraphic& operator=(const ScriptGraphic&) = delete;
	friend CHL::Singleton<ScriptGraphic>;
public:
	static void Init(lua_State *lua);
};

#endif //__ScriptGraphic__
