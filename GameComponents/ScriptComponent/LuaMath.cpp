#include "LuaMath.h"
#include <MathFunctions.h>
#include <VecOperators.h>

namespace LuaMath
{
	Vector4::Vector4(){}
	Vector4::Vector4(CML::Vec4 vecValue){ this->vector = vecValue; }
	Vector4::Vector4(double xValue, double yValue, double zValue, double wValue)
		: vector({xValue, yValue, zValue, wValue})
	{
	}
	Vector4::operator CML::Vec4(){ return this->vector; }
	double Vector4::GetterX(){ return this->vector(0); }
	double Vector4::GetterY(){ return this->vector(1); }
	double Vector4::GetterZ(){ return this->vector(2); }
	double Vector4::GetterW(){ return this->vector(3); }
	void Vector4::SetterX(double value){ this->vector(0) = value; }
	void Vector4::SetterY(double value){ this->vector(1) = value; }
	void Vector4::SetterZ(double value){ this->vector(2) = value; }
	void Vector4::SetterW(double value){ this->vector(3) = value; }

	void Vector4::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<Vector4>("Vector4")
				.def(luabind::constructor<double, double, double, double>())
				.def(luabind::constructor<double, double, double>())
				.property("X", &Vector4::GetterX, &Vector4::SetterX)
				.property("Y", &Vector4::GetterY, &Vector4::SetterY)
				.property("Z", &Vector4::GetterZ, &Vector4::SetterZ)
				.property("W", &Vector4::GetterW, &Vector4::SetterW)
				.property("x", &Vector4::GetterX, &Vector4::SetterX)
				.property("y", &Vector4::GetterY, &Vector4::SetterY)
				.property("z", &Vector4::GetterZ, &Vector4::SetterZ)
				.property("w", &Vector4::GetterW, &Vector4::SetterW)
		];
	}

	Matrix4x4::Matrix4x4(){}
	Matrix4x4::Matrix4x4(CML::Matrix4x4 mat){ this->matrix = mat; }
	Matrix4x4::operator CML::Matrix4x4(){ return this->matrix; }
	double Matrix4x4::GetValue(int x, int y){ return this->matrix(x, y); }
	void Matrix4x4::SetValue(int x, int y, double value){ this->matrix(x, y) = value; }
	void Matrix4x4::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<Matrix4x4>("Matrix4x4")
				.def(luabind::constructor<>())
				.def("GetValue", &Matrix4x4::GetValue)
				.def("SetValue", &Matrix4x4::SetValue)
		];
	}

	Vector4 MoveObject(Vector4 Location, Vector4 target, double pitch, double yaw, double roll, double Magnitude)
	{
		CML::Matrix4x4 rotation = CML::RotationMatrix(pitch, yaw, roll);
		target = CML::Normalize(target);

		CML::Vec4 targetRotation = CML::Multiple(target, rotation);
		targetRotation = CML::Normalize(targetRotation);

		CML::Vec4 newEye = Location.vector + (targetRotation * Magnitude);

		return newEye;
	}

	/*Vector4 RotateVector(Vector4 target, double pitch, double yaw, double roll)
	{
		CML::Matrix4x4 rotation = CML::RotationMatrix(pitch, yaw, roll);
		target = CML::Normalize(target);

		CML::Vec4 targetRotation = CML::Multiple(target, rotation);

		return targetRotation;
	}*/
	Vector4 RotateVector(Vector4 Vector, Vector4 QuaRotation)
	{
		QuaRotation = CML::QuaNormalize(QuaRotation);
		CML::Matrix4x4 rotation = CML::RotationMatrix(QuaRotation);

		CML::Vec4 targetRotation = CML::Multiple(Vector, rotation);

		return targetRotation;
	}

	void RegisterAllLuaFunction(lua_State *lua)
	{
		Vector4::Register(lua);
		Matrix4x4::Register(lua);
		luabind::module(lua)[
			luabind::def("MoveObject", LuaMath::MoveObject),
			luabind::def("RotateVector", LuaMath::RotateVector)
		];
	}
}