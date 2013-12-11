#include "LuaMath.h"
#include <3DMath.h>

LuaMath::Vector4::Vector4(){}
LuaMath::Vector4::Vector4(CHL::Vec4 vecValue){	this->vector = vecValue; }
LuaMath::Vector4::Vector4(double xValue, double yValue, double zValue, double wValue)
: vector({ xValue, yValue, zValue, wValue })
{
}
LuaMath::Vector4::operator CHL::Vec4(){	return this->vector;}

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
		  .property("x", &LuaMath::Vector4::GetterX, &LuaMath::Vector4::SetterX)
		  .property("y", &LuaMath::Vector4::GetterY, &LuaMath::Vector4::SetterY)
		  .property("z", &LuaMath::Vector4::GetterZ, &LuaMath::Vector4::SetterZ)
		  .property("w", &LuaMath::Vector4::GetterW, &LuaMath::Vector4::SetterW)
	  ];
}

LuaMath::Matrix4x4::Matrix4x4(){}
LuaMath::Matrix4x4::Matrix4x4(CHL::Matrix4x4 mat){	this->matrix = mat;	}

LuaMath::Matrix4x4::operator CHL::Matrix4x4(){	return this->matrix; }

double LuaMath::Matrix4x4::GetValue(int x, int y){ return this->matrix(x, y); }
void LuaMath::Matrix4x4::SetValue(int x, int y, double value){ this->matrix(x, y) = value; }


void LuaMath::Matrix4x4::Register(lua_State *lua)
{
	luabind::module(lua)[
		luabind::class_<LuaMath::Matrix4x4>("Matrix4x4")
			.def(luabind::constructor<>())
			.def("GetValue", &LuaMath::Matrix4x4::GetValue)
			.def("SetValue", &LuaMath::Matrix4x4::SetValue)
	];
}

LuaMath::Matrix4x4 LuaMath::LuaViewCalculation
	(LuaMath::Vector4 eye, LuaMath::Vector4 vTM, LuaMath::Vector4 vUp, double pitch, double yaw, double roll)
{
	return CHL::ViewCalculation(eye, vTM, vUp, pitch, yaw, roll);
}