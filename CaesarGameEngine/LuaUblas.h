#ifndef __Ublas__
#define __Ublas__

extern "C" {
#include <lua-5.1.0\lua.h>
#include <lua-5.1.0\lualib.h>
#include <lua-5.1.0\lauxlib.h>
}

#include <string>
#include <boost/numeric/ublas/matrix.hpp>

class LuaUblas
{
public:
	class Vector4
	{
	public:
		Vector4();
		Vector4(double xValue, double yValue, double zValue, double wValue);
		Vector4(boost::numeric::ublas::vector<double> vecValue);
		boost::numeric::ublas::vector<double> vector;

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

#endif //__Ublas__