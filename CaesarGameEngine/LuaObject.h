#ifndef __LuaObject__
#define __LuaObject__

extern "C" {
#include <lua-5.1.0\lua.h>
#include <lua-5.1.0\lualib.h>
#include <lua-5.1.0\lauxlib.h>
}

#include <string>
#include "LuaUblas.h"
#include <string>

class LuaObject
{
public:
	class Object
	{
	public:
		Object();
		std::string GetID();

		std::string GetGraphicID();
		void SetGraphicID(std::string);

		void SetLocation(LuaUblas::Vector4 vec);
		LuaUblas::Vector4 GetLocation();

		void SetRotation(LuaUblas::Vector4 vec);
		LuaUblas::Vector4 GetRotation();

		void SetScale(LuaUblas::Vector4 vec);
		LuaUblas::Vector4 GetScale();

		static void Register(lua_State *lua);

		std::string ID;
	};

	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaObject::Object::Register(lua);
	}
};

#endif //__LuaObject__