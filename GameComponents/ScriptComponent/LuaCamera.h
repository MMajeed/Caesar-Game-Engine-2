#ifndef __LuaCamera__
#define __LuaCamera__

#include <Lua.hpp>
#include "LuaUblas.h"

class LuaCamera
{
public:
	LuaCamera(LuaUblas::Vector4 eye, LuaUblas::Vector4 targetMagintude, LuaUblas::Vector4 up, double roll, double pitch, double yaw);
	void SetAsMain();
		
	void MoveFroward(double distance);

	void SetEye(LuaUblas::Vector4 eye);
	LuaUblas::Vector4 GetEye();

	void SetTargetMagintude(LuaUblas::Vector4 targetMagintude);
	LuaUblas::Vector4 GetTargetMagintude();

	void SetUp(LuaUblas::Vector4 up);
	LuaUblas::Vector4 GetUp();

	void SetRoll(double roll);
	double GetRoll();

	void SetPitch(double pitch);
	double GetPitch();

	void SetYaw(double yaw);
	double GetYaw();

	std::string ID;
	static void Register(lua_State *lua);

	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaCamera::Register(lua);
	}
};

#endif //__LuaCamera__