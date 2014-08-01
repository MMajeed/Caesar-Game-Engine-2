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
	void SetEye(const LuaMath::Vector4& v);

	LuaMath::Vector4 GetTargetMagnitude();
	void SetTargetMagnitude(const LuaMath::Vector4& v);

	LuaMath::Vector4 GetUp();
	void SetUp(const LuaMath::Vector4& v);

	double GetRoll();
	void SetRoll(double v);

	double GetPitch();
	void SetPitch(double v);

	double GetYaw();
	void SetYaw(double v);

	double GetFovAngle();
	void SetFovAngle(double v);

	double GetNearZ();
	void SetNearZ(double v);

	double GetFarZ();
	void SetFarZ(double v);

	LuaMath::Vector4 GetClearColor();
	void SetClearColor(const LuaMath::Vector4& v);

	luabind::object GetGlobalTexture2D();
	void SetGlobalTexture2D(const luabind::object& v);
	void AddGlobalTexture2D(const GenericLuaObject& v);
	void DeleteGlobalTexture2D(const GenericLuaObject& v);
	void EmptyGlobalTexture2D();

	luabind::object GetGlobalTextureCube();
	void SetGlobalTextureCube(const luabind::object& v);
	void AddGlobalTextureCube(const GenericLuaObject& v);
	void DeleteGlobalTextureCube(const GenericLuaObject& v);
	void EmptyGlobalTextureCube();

	/*luabind::object GetUserData();
	void SetUserData(const luabind::object& v)
	bool FindUserData(const std::string& ID, std::vector<char>& v);
	void SetUserData(const std::string& ID, const std::vector<char>& data);
	void DeleteUserData(const std::string& ID);
	void EmptyUserData();*/
	
	int GetInclusionState();
	void SetInclusionState(int v);

	luabind::object GetInclusionList();
	void SetInclusionList(const luabind::object& v);
	void AddInclusionList(const GenericLuaObject& v);
	void DeleteInclusionList(const GenericLuaObject& v);
	void EmptyInclusionList();

	void Release();

	std::string GetID() const;

	static void Register(lua_State *lua);

	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaCamera::Register(lua);
	}
};

#endif //__LuaCamera__