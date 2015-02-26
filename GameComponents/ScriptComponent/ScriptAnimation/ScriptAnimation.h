#ifndef __ScriptAnimation__
#define __ScriptAnimation__

#include "Linker.h"

#include <Lua.hpp>
#include <Singleton.h>

class ScriptAnimationDLL_API ScriptAnimation : public CHL::Singleton<ScriptAnimation>
{
protected:
	ScriptAnimation();
	ScriptAnimation(const ScriptAnimation& that) = delete;
	ScriptAnimation& operator=(const ScriptAnimation&) = delete;
	friend CHL::Singleton<ScriptAnimation>;
public:
	static void Init(lua_State *lua);
};

static ScriptAnimation& ScriptAnimationEntity = ScriptAnimation::GetInstance();

#endif //__ScriptAnimation__