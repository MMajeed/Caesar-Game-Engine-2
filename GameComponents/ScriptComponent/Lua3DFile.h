#ifndef __Lua3DFile__
#define __Lua3DFile__

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include <string>

namespace Lua3DFile
{
	luabind::object LoadScene(std::string fileName);

	void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__Lua3DFile__