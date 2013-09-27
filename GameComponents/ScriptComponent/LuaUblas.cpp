#include "LuaUblas.h"

#include <luabind\luabind.hpp>

LuaUblas::Vector4::Vector4()
	: vector(4)
{
	this->vector(0) = 0.0;
	this->vector(1) = 0.0;
	this->vector(2) = 0.0;
	this->vector(3) = 0.0;
}
LuaUblas::Vector4::Vector4(boost::numeric::ublas::vector<double> vecValue)
	: vector(4)
{
	this->vector = vecValue;
}
LuaUblas::Vector4::Vector4(double xValue, double yValue, double zValue, double wValue)
	: vector(4)
{
	this->vector(0) = xValue;
	this->vector(1) = yValue;
	this->vector(2) = zValue;
	this->vector(3) = wValue;
}
LuaUblas::Vector4::operator boost::numeric::ublas::vector<double>()
{
	return this->vector;
}

double LuaUblas::Vector4::GetterX(){ return this->vector(0); }
double LuaUblas::Vector4::GetterY(){ return this->vector(1); }
double LuaUblas::Vector4::GetterZ(){ return this->vector(2); }
double LuaUblas::Vector4::GetterW(){ return this->vector(3); }

void LuaUblas::Vector4::SetterX(double value){ this->vector(0) = value; }
void LuaUblas::Vector4::SetterY(double value){ this->vector(1) = value; }
void LuaUblas::Vector4::SetterZ(double value){ this->vector(2) = value; }
void LuaUblas::Vector4::SetterW(double value){ this->vector(3) = value; }

void LuaUblas::Vector4::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::class_<LuaUblas::Vector4>("Vector4")
		  .def(luabind::constructor<double, double, double, double>())
		  .def(luabind::constructor<double, double, double>())
		  .property("X", &LuaUblas::Vector4::GetterX, &LuaUblas::Vector4::SetterX)
		  .property("Y", &LuaUblas::Vector4::GetterY, &LuaUblas::Vector4::SetterY)
		  .property("Z", &LuaUblas::Vector4::GetterZ, &LuaUblas::Vector4::SetterZ)
		  .property("W", &LuaUblas::Vector4::GetterW, &LuaUblas::Vector4::SetterW)
	  ];
}