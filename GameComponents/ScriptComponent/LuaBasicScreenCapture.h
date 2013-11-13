#ifndef __LuaBasicScreenCapture__
#define __LuaBasicScreenCapture__

#include <lua.hpp>
#include <luabind\luabind.hpp>
#include "LuaBasicTexture.h"

class LuaBasicScreenCapture
{
public:
	LuaBasicScreenCapture(luabind::object const& table);
	LuaBasicTexture LuaBasicScreenCapture::TakeSnapShot(luabind::object const& table);

	std::string ID;

	static void Register(lua_State *lua);
	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaBasicScreenCapture::Register(lua);
	}
};

#endif //__LuaBasicScreenCapture__
