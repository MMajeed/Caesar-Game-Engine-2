#ifndef __LuaUblas__
#define __LuaUblas__

#include <Lua.hpp>
#include <string>
#include <Vector.h>

class LuaUblas
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

	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaUblas::Vector4::Register(lua);
	}
};

#endif //__LuaUblas__