#ifndef __LuaCamera__
#define __LuaCamera__

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include "LuaMath.h"
#include "CameraINFO.h"

class LuaCamera
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

	void Release();

	std::string ID;

	static void Register(lua_State *lua);

	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaCamera::Register(lua);
	}
};

#endif //__LuaCamera__