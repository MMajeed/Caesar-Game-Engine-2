#ifndef __LuaMath__
#define __LuaMath__

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include <string>
#include <Vector.h>
#include <Matrix.h>

class LuaMath
{
public:
	class Vector4
	{
	public:
		Vector4();
		Vector4(double xValue, double yValue, double zValue, double wValue = 0.0);
		Vector4(CHL::Vec4 vecValue);

		operator CHL::Vec4();

		CHL::Vec4 vector;

		double GetterX();
		double GetterY();
		double GetterZ();
		double GetterW();

		void SetterX(double value);
		void SetterY(double value);
		void SetterZ(double value);
		void SetterW(double value);

		static void Register(lua_State *lua);
	};

	class Matrix4x4
	{
	public:
		Matrix4x4();
		Matrix4x4(CHL::Matrix4x4 mat);
		operator CHL::Matrix4x4();

		double GetValue(int x, int y);
		void SetValue(int x, int y, double value);
		
		CHL::Matrix4x4 matrix;
		static void Register(lua_State *lua);
	};

	static Matrix4x4 LuaViewCalculation(Vector4 eye, Vector4 vTM, Vector4 vUp, double pitch, double yaw, double roll);

	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaMath::Vector4::Register(lua);
		LuaMath::Matrix4x4::Register(lua);
		luabind::module(lua)[
			luabind::def("ViewCalculation", LuaMath::LuaViewCalculation)
		];
	}
};

#endif //__LuaMath__