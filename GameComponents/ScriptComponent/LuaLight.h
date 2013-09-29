#ifndef __LuaObject__
#define __LuaObject__

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include "LuaBasicDrawableObject.h"
#include "LuaBasicTexture.h"
#include "LuaUblas.h"

class LuaObject
{
public:
	LuaObject();

	std::string ID;

	void SetGraphic(LuaBasicDrawableObject graphic);
	void RemoveGraphic();

	void SetTexture(LuaBasicTexture texture);
	void RemoveTexture(LuaBasicTexture texture);

	void SetLocation(LuaUblas::Vector4 vec);
	LuaUblas::Vector4 GetLocation();

	void SetScale(LuaUblas::Vector4 vec);
	LuaUblas::Vector4 GetScale();

	void SetRotation(LuaUblas::Vector4 vec);
	LuaUblas::Vector4 GetRotation();

	void SetDiffuse(LuaUblas::Vector4 vec);
	LuaUblas::Vector4 GetDiffuse();

	void SetAmibent(LuaUblas::Vector4 vec);
	LuaUblas::Vector4 GetAmibent();

	void SetSpecular(LuaUblas::Vector4 vec);
	LuaUblas::Vector4 GetSpecular();

	static void Register(lua_State *lua);
	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaObject::Register(lua);
	}
};

#endif //__LuaObject__