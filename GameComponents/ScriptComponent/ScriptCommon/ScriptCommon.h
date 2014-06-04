#ifndef __ScriptCommon__
#define __ScriptCommon__

#include "Linker.h"

#include <Lua.hpp>
#include <Singleton.h>

class ScriptCommonDLL_API ScriptCommon : public CHL::Singleton<ScriptCommon>
{
protected:
	ScriptCommon();
	ScriptCommon(const ScriptCommon& that) = delete;
	ScriptCommon& operator=(const ScriptCommon&) = delete;
	friend CHL::Singleton<ScriptCommon>;
public:
	static void Init(lua_State *lua);
};

#endif //__ScriptCommon__
