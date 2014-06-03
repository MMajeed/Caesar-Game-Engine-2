#ifndef __LuaMouse__
#define __LuaMouse__

#include <Lua.hpp>
#include <luabind\luabind.hpp>

#include <string>

namespace LuaMouse
{
	luabind::object Location();

	void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__LuaMouse__
