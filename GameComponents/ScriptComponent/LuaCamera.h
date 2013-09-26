#ifndef __LuaCamera__
#define __LuaCamera__

extern "C" {
#include <lua5.1.5\lua.h>
#include <lua5.1.5\lualib.h>
#include <lua5.1.5\lauxlib.h>
}

#include "LuaUblas.h"

class LuaCameraSetup
{
public:
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
	};

	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaCameraSetup::LuaCamera::Register(lua);
	}
};

#endif //__LuaCamera__