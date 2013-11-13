#ifndef __LuaBasicTexture__
#define __LuaBasicTexture__

#include <lua.hpp>
#include <luabind\luabind.hpp>
#include <string>

class LuaBasicTexture
{
public:
	LuaBasicTexture(){};
	LuaBasicTexture(std::string textureFile);

	std::string ID;

	static void Register(lua_State *lua);
	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaBasicTexture::Register(lua);
	}
};

#endif //__LuaBasicTexture__