#ifndef __LuaMath__
#define __LuaMath__

#include <Lua.hpp>
#include <string>
#include <Vector.h>

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

	static inline void RegisterAllLuaFunction(lua_State *lua)
	{
		LuaMath::Vector4::Register(lua);
	}
};

#endif //__LuaMath__