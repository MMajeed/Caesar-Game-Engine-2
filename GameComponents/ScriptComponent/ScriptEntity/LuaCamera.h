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

	void Release();

	static void Register(lua_State *lua);

	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaCamera::Register(lua);
	}
};

#endif //__LuaCamera__