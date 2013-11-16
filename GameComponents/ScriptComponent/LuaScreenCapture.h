#ifndef __LuaScreenCapture__
#define __LuaScreenCapture__

#include <lua.hpp>
#include <luabind\luabind.hpp>
#include "LuaBasicTexture.h"

class LuaScreenCapture
{
public:
	static LuaBasicTexture TakeScreenSnapShot(luabind::object const& table);
	static LuaBasicTexture TakeDepthSnapShot(luabind::object const& table);
	static LuaBasicTexture TakeCubeSnapShot(luabind::object const& table);

	static void Register(lua_State *lua);
	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaScreenCapture::Register(lua);
	}
};

#endif //__LuaScreenCapture__
