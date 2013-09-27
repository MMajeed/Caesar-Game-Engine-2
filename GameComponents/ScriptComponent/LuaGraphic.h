#ifndef __LuaGraphic__
#define __LuaGraphic__

#include <Lua.hpp>
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

	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaGraphic::ClearScreen::Register(lua);
	}
};

#endif //__LuaGraphic__