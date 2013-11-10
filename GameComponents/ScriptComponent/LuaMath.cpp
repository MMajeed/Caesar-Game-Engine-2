#include "LuaMath.h"

#include <luabind\luabind.hpp>

LuaMath::Vector4::Vector4()
{
	this->vector(0) = 0.0;
	this->vector(1) = 0.0;
	this->vector(2) = 0.0;
	this->vector(3) = 0.0;
}
LuaMath::Vector4::Vector4(CHL::Vec4 vecValue)
{
	this->vector = vecValue;
}
LuaMath::Vector4::Vector4(double xValue, double yValue, double zValue, double wValue)
{
	this->vector(0) = xValue;
	this->vector(1) = yValue;
	this->vector(2) = zValue;
	this->vector(3) = wValue;
}
LuaMath::Vector4::operator CHL::Vec4()
{
	return this->vector;
}

double LuaMath::Vector4::GetterX(){ return this->vector(0); }
double LuaMath::Vector4::GetterY(){ return this->vector(1); }
double LuaMath::Vector4::GetterZ(){ return this->vector(2); }
double LuaMath::Vector4::GetterW(){ return this->vector(3); }

void LuaMath::Vector4::SetterX(double value){ this->vector(0) = value; }
void LuaMath::Vector4::SetterY(double value){ this->vector(1) = value; }
void LuaMath::Vector4::SetterZ(double value){ this->vector(2) = value; }
void LuaMath::Vector4::SetterW(double value){ this->vector(3) = value; }

void LuaMath::Vector4::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::class_<LuaMath::Vector4>("Vector4")
		  .def(luabind::constructor<double, double, double, double>())
		  .def(luabind::constructor<double, double, double>())
		  .property("X", &LuaMath::Vector4::GetterX, &LuaMath::Vector4::SetterX)
		  .property("Y", &LuaMath::Vector4::GetterY, &LuaMath::Vector4::SetterY)
		  .property("Z", &LuaMath::Vector4::GetterZ, &LuaMath::Vector4::SetterZ)
		  .property("W", &LuaMath::Vector4::GetterW, &LuaMath::Vector4::SetterW)
	  ];
}