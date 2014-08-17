#ifndef __LuaCamera__
#define __LuaCamera__

#include "Linker.h"

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include <LuaMath.h>
#include <CameraEntity.h>
#include <GenericLuaObject.h>

class ScriptEntityDLL_API LuaCamera : public GenericLuaObject
{
protected:
	std::weak_ptr<CameraEntity> wp_Obj;
public:
	LuaCamera();
	LuaCamera(const luabind::object& table);

	LuaMath::Vector4 GetEye();
	void SetEye(const luabind::object& v);

	LuaMath::Vector4 GetTargetMagnitude();
	void SetTargetMagnitude(const luabind::object& v);

	LuaMath::Vector4 GetUp();
	void SetUp(const luabind::object& v);

	double GetRoll();
	void SetRoll(const luabind::object& v);

	double GetPitch();
	void SetPitch(const luabind::object& v);

	double GetYaw();
	void SetYaw(const luabind::object& v);

	double GetFovAngleY();
	void SetFovAngleY(const luabind::object& v);

	double GetNearZ();
	void SetNearZ(const luabind::object& v);

	double GetFarZ();
	void SetFarZ(const luabind::object& v);

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
		LuaCamera::Register(lua);
	}
};

#endif //__LuaCamera__