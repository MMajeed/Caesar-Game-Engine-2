#ifndef __LuaObject__
#define __LuaObject__

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include "LuaBasicDrawableObject.h"
#include "LuaBasicTexture.h"
#include "LuaMath.h"
#include <ObjectINFO.h>

class LuaObject
{
public:
	LuaObject();
	LuaObject(luabind::object const& table);

	std::string ID;

	void SetGraphic(LuaBasicDrawableObject graphic);
	void RemoveGraphic();

	void Set2DTexture(LuaBasicTexture texture);
	void Remove2DTexture(LuaBasicTexture texture);
	void RemoveAll2DTexture();

	void SetCubeTexture(LuaBasicTexture texture);
	void RemoveCubeTexture(LuaBasicTexture texture);
	void RemoveAllCubeTexture();

	void SetLocation(LuaMath::Vector4 vec);
	LuaMath::Vector4 GetLocation();

	void SetScale(LuaMath::Vector4 vec);
	LuaMath::Vector4 GetScale();

	void SetRotation(LuaMath::Vector4 vec);
	LuaMath::Vector4 GetRotation();

	void SetDiffuse(LuaMath::Vector4 vec);
	LuaMath::Vector4 GetDiffuse();

	void SetAmibent(LuaMath::Vector4 vec);
	LuaMath::Vector4 GetAmibent();

	void SetSpecular(LuaMath::Vector4 vec);
	LuaMath::Vector4 GetSpecular();

	void SetLight(bool vec);
	bool GetLight();

	void SetShadow(bool vec);
	bool GetShadow();

	std::shared_ptr<ObjectINFO> GetObject();

	static void Register(lua_State *lua);
	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaObject::Register(lua);
	}
};

#endif //__LuaObject__