#ifndef __LuaObject__
#define __LuaObject__

extern "C" {
#include <lua5.1.0\lua.h>
#include <lua5.1.0\lualib.h>
#include <lua5.1.0\lauxlib.h>
}

#include <luabind\luabind.hpp>

class LuaObject
{
public:
	class Object
	{
	public:
		static std::string AddObject(luabind::object const& table);
		static void Register(lua_State *lua);
	};

	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaObject::Object::Register(lua);
	}
};

#endif //__LuaObject__