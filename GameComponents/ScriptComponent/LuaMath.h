#ifndef __LuaMath__
#define __LuaMath__

#include "Linker.h"

#include <Lua.hpp>
#include <luabind\luabind.hpp>
#include <string>
#include <Vector.h>
#include <Vector.h>
#include <Matrix.h>

namespace LuaMath
{
	class Vector4
	{
	public:
		Vector4();
		Vector4(double xValue, double yValue, double zValue, double wValue = 0.0);
		Vector4(CML::Vec4 vecValue);

		operator CML::Vec4();

		CML::Vec4 vector;

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
		Matrix4x4(CML::Matrix4x4 mat);
		operator CML::Matrix4x4();

		double GetValue(int x, int y);
		void SetValue(int x, int y, double value);
		
		CML::Matrix4x4 matrix;
		static void Register(lua_State *lua);
	};

	Vector4 MoveObject(Vector4 Location, Vector4 target, double pitch, double yaw, double roll, double magintude);
	//Vector4 RotateVector(Vector4 target, double pitch, double yaw, double roll);
	Vector4 RotateVector(Vector4 Vector, Vector4 QuaRotation);

	void RegisterAllLuaFunction(lua_State *lua);
};

#endif //__LuaMath__