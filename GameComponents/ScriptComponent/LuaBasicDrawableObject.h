#ifndef __LuaBasicDrawableObject__
#define __LuaBasicDrawableObject__

#include <lua.hpp>
#include <luabind\luabind.hpp>
#include <string>

class LuaBasicDrawableObject
{
public:
	LuaBasicDrawableObject(luabind::object const& table);
	void ChangeRastersizerState(int cullMode, int fillMode, bool antialiasedLine, bool multisampleEnable);
	std::string ID;

	static void Register(lua_State *lua);
	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaBasicDrawableObject::Register(lua);
	}
};

#endif //__LuaBasicDrawableObject__
