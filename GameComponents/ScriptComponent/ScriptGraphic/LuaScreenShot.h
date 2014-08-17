#ifndef __LuaScreenShot__
#define __LuaScreenShot__

#include "Linker.h"

#include <lua.hpp>
#include <luabind\luabind.hpp>
#include "LuaBasicTexture.h"

namespace LuaScreenShot
{
	ScriptGraphicDLL_API luabind::object TakeScreenSnapShot(luabind::object const& table);
	ScriptGraphicDLL_API LuaBasicTexture TakeDepthSnapShot(luabind::object const& table);
	ScriptGraphicDLL_API LuaBasicTexture TakeCubeSnapShot(luabind::object const& table);

	ScriptGraphicDLL_API void Register(lua_State *lua);
	inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaScreenShot::Register(lua);
	}
};

#endif //__LuaScreenShot__
