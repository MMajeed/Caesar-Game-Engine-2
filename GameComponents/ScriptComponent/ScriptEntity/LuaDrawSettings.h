#ifndef __LuaDrawSettings__
#define __LuaDrawSettings__

#include "Linker.h"

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include <LuaMath.h>
#include <DrawSettingsEntity.h>
#include <GenericLuaObject.h>

class ScriptEntityDLL_API LuaDrawSettings : public GenericLuaObject
{
protected:
	std::weak_ptr<DrawSettingsEntity> wp_Obj;
public:
	LuaDrawSettings();
	LuaDrawSettings(const luabind::object& table);
	
	bool GetClearScreen();
	void SetClearScreen(const luabind::object& v);

	LuaMath::Vector4 GetClearColor();
	void SetClearColor(const luabind::object& v);

	int GetInclusionState();
	void SetInclusionState(const luabind::object& v);

	luabind::object GetInclusionList();
	void SetInclusionList(const luabind::object& v);
	void AddInclusionList(const luabind::object& v);
	void DeleteInclusionList(const luabind::object& v);
	void EmptyInclusionList();

	luabind::object GetAllUserData();
	void SetAllUserData(const luabind::object& v);
	luabind::object FindUserData(const std::string& ID);
	void SetUserData(const std::string& ID, const luabind::object& data);
	void DeleteUserData(const std::string& ID);
	void EmptyUserData();

	luabind::object GetAllTexture();
	void SetAllTexture(const luabind::object& v);
	luabind::object FindTexture(const std::string& ID);
	void SetTexture(const std::string& ID, const luabind::object& v);
	void DeleteTexture(const std::string& ID);
	void EmptyTexture();

	void GetVertexShaderID();
	void SetVertexShaderID(const luabind::object& v);
	void RemoveVertexShaderID();

	int GetVertexShaderState();
	void SetVertexShaderState(const luabind::object& v);

	void GetPixelShaderID();
	void SetPixelShaderID(const luabind::object& v);
	void RemovePixelShaderID();

	int GetPixelShaderState();
	void SetPixelShaderState(const luabind::object& v);

	void Release();

	static void Register(lua_State *lua);

	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaDrawSettings::Register(lua);
	}
};

#endif //__LuaDrawSettings__