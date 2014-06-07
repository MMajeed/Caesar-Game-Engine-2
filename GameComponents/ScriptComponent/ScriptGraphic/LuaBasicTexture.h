#ifndef __LuaBasicTexture__
#define __LuaBasicTexture__

#include "Linker.h"

#include <lua.hpp>
#include <luabind\luabind.hpp>
#include <GenericLuaObject.h>

class ScriptGraphicDLL_API LuaBasicTexture : public GenericLuaObject
{
public:
	LuaBasicTexture(){};
	LuaBasicTexture(std::string textureFile);
	void Release();

	static void Register(lua_State *lua);
	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaBasicTexture::Register(lua);
	}
};

#endif //__LuaBasicTexture__