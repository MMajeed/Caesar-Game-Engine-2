#ifndef __LuaGraphic__
#define __LuaGraphic__

extern "C" {
#include <lua-5.1.0\lua.h>
#include <lua-5.1.0\\lualib.h>
#include <lua-5.1.0\\lauxlib.h>
}

#include <string>

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
		static std::string AddBasicObject(std::string modleFileName,
						    std::string	vertexFileName,
							std::string	pixelFileName,
							std::string texture);
		static void Register(lua_State *lua);
	};

	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaGraphic::ClearScreen::Register(lua);
		LuaGraphic::AddObject::Register(lua);
	}
};

#endif //__LuaGraphic__