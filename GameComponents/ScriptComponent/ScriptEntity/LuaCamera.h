#ifndef __LuaCamera__
#define __LuaCamera__

#include "Linker.h"

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include <GenericLuaObject.h>
#include <LuaMath.h>
#include "CameraINFO.h"
#include <set>

class ScriptEntityDLL_API LuaCamera : public GenericLuaObject
{
public:
	LuaCamera(luabind::object const& table);
	void SetAsMain();
		
	void MoveFroward(double distance);

	void SetEye(LuaMath::Vector4 eye);
	LuaMath::Vector4 GetEye();

	void SetTargetMagintude(LuaMath::Vector4 targetMagintude);
	LuaMath::Vector4 GetTargetMagintude();

	void SetUp(LuaMath::Vector4 up);
	LuaMath::Vector4 GetUp();

	void SetRoll(double roll);
	double GetRoll();

	void SetPitch(double pitch);
	double GetPitch();

	void SetYaw(double yaw);
	double GetYaw();

	void SetFovAngle(double val);
	double GetFovAngle();

	void SetNearZ(double val);
	double GetNearZ();

	void SetFarZ(double val);
	double GetFarZ();

	void SetClearColor(LuaMath::Vector4 val);
	LuaMath::Vector4 GetClearColor();

	std::shared_ptr<GenericObj<std::vector<std::string>>> GetRawAll2DTextures();
	void Add2dTexture(GenericLuaObject texture);
	void Remove2Texture(GenericLuaObject texture);
	void Set2DTexture(const luabind::object& textures );
	luabind::object All2DTexture();
	
	std::shared_ptr<GenericObj<std::vector<std::string>>> GetRawAllCubeTextures();
	void AddCubeTexture(GenericLuaObject texture);
	void RemoveCubeTexture(GenericLuaObject texture);
	void SetCubeTexture(const luabind::object& textures);
	luabind::object AllCubeTexture();

	void SetGlobalUserData(const luabind::object& textures);
	luabind::object GetGlobalUserData();

	void SetProccess2D(bool val);
	bool GetProccess2D();

	void SetInclusionState(int type);
	int GetInclusionState();

	std::shared_ptr<GenericObj<std::set<std::string>>> GetRawObjectList();
	void AddObject(GenericLuaObject obj);
	void RemoveObject(GenericLuaObject obj);
	void SetObjectList(const luabind::object& obj);
	luabind::object GetObjectList();

	void Release();

	static void Register(lua_State *lua);

	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaCamera::Register(lua);
	}
};

#endif //__LuaCamera__