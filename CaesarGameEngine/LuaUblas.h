#ifndef __LuaUblas__
#define __LuaUblas__

extern "C" {
#include <lua5.1.5\lua.h>
#include <lua5.1.5\lualib.h>
#include <lua5.1.5\lauxlib.h>
}

#include <string>
#include <boost/numeric/ublas/vector.hpp>

class LuaUblas
{
public:
	class Vector4
	{
	public:
		Vector4();
		Vector4(double xValue, double yValue, double zValue, double wValue);
		Vector4(boost::numeric::ublas::vector<double> vecValue);

		operator boost::numeric::ublas::vector<double>();

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

#endif //__LuaUblas__