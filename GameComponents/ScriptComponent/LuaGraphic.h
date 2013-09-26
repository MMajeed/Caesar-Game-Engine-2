#ifndef __LuaGraphic__
#define __LuaGraphic__

extern "C" {
#include <lua5.1.5\lua.h>
#include <lua5.1.5\lualib.h>
#include <lua5.1.5\lauxlib.h>
}

#include <luabind\luabind.hpp>

class LuaGraphic
{
public:
	class ClearScreen
	{
	public:
		static void Action(double x, double y, double z);
		static void Register(lua_State *lua);
	};

	class AddObject
	{
	public:
		static std::string AddBasicObject(luabind::object const& table);
		static void Register(lua_State *lua);
	};

	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaGraphic::ClearScreen::Register(lua);
		LuaGraphic::AddObject::Register(lua);
	}
};

#endif //__LuaGraphic__