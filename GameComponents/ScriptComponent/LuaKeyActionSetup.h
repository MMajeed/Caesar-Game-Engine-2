#ifndef __LuaKeyActionSetup__
#define __LuaKeyActionSetup__

#include <Lua.hpp>
#include <luabind\luabind.hpp>

#include <string>

class LuaKeyActionSetup
{
public:
	static std::string OnKeyDown(unsigned int key, luabind::object function);
	static std::string OnKeyUp(unsigned int key, luabind::object const& function);
	static void Register(lua_State *lua);

	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaKeyActionSetup::Register(lua);
	}
};

#endif //__LuaKeyActionSetup__
