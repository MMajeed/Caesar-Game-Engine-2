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

	void SetGraphic(LuaBasicDrawableObject::BasicDrawableObject graphic);
	void RemoveGraphic();

	std::shared_ptr<GenericObj<std::vector<std::string>>> GetRawAll2DTextures();
	void Add2DTexture(LuaBasicTexture texture);
	void Remove2DTexture(LuaBasicTexture texture);
	void Set2DTexture(const luabind::object& textures);
	luabind::object All2DTexture();

	std::shared_ptr<GenericObj<std::vector<std::string>>> GetRawAllCubeTextures();
	void AddCubeTexture(LuaBasicTexture texture);
	void RemoveCubeTexture(LuaBasicTexture texture);
	void SetCubeTexture(const luabind::object& textures);
	luabind::object AllCubeTexture();

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

	void SetDepth(bool vec);
	bool GetDepth();

	void SetUserData(const luabind::object& textures);
	luabind::object GetUserData();

	void Release();

	std::shared_ptr<ObjectINFO> GetObject();

	static void Register(lua_State *lua);
	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaObject::Register(lua);
	}
};

#endif //__LuaObject__