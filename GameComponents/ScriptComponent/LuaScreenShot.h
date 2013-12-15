#ifndef __LuaScreenShot__
#define __LuaScreenShot__

#include <lua.hpp>
#include <luabind\luabind.hpp>
#include "LuaBasicTexture.h"

namespace LuaScreenShot
{
	LuaBasicTexture TakeScreenSnapShot(luabind::object const& table);
	LuaBasicTexture TakeDepthSnapShot(luabind::object const& table);
	LuaBasicTexture TakeCubeSnapShot(luabind::object const& table);

	void Register(lua_State *lua);
	inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaScreenShot::Register(lua);
	}
};

#endif //__LuaScreenShot__
