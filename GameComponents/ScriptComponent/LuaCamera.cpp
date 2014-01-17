#include "LuaCamera.h"
#include <Converter.h>
#include <3DMath.h>
#include <luabind\luabind.hpp>
#include <EntityCommunicator\EntityConfig.h>
#include <EntityCommunicator\ImportantIDConfig.h>
#include <Keys.h>

LuaCamera::LuaCamera(luabind::object const& table)
{
	if (luabind::type(table) != LUA_TTABLE)
		Logger::LogError("Wrong paramter for Camera, please send in a table");

	CHL::Vec4 eye{0.0, 0.0, 0.0, 0.0};
	CHL::Vec4 TM{0.0, 0.0, 1.0, 0.0};
	CHL::Vec4 up{0.0, 1.0, 0.0, 0.0};
	double roll = 0.0;	double pitch = 0.0;		double yaw = 0.0;
	double FovAngleY = 0.785398163;
	double nearZ = 0.01;
	double farZ = 5000.0;
	CHL::Vec4 ClearColor{0.5, 0.5, 0.5, 1.0};
	bool process2D = true;

	for (luabind::iterator it(table);
		it != luabind::iterator();
		++it)
	{
		std::string key = luabind::object_cast<std::string>(it.key());

			 if (key == Keys::Camera::EYE)				{ eye = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Camera::TARGETMAGNITUDE)	{ TM = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Camera::UP)				{ up = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Camera::RADIANROLL)		{ roll = luabind::object_cast<double>(*it); }
		else if (key == Keys::Camera::RADIANPITCH)		{ pitch = luabind::object_cast<double>(*it); }
		else if(key == Keys::Camera::RADIANYAW)		    { yaw = luabind::object_cast<double>(*it); }
		else if(key == Keys::Camera::FOVANGLE)		    { FovAngleY = luabind::object_cast<double>(*it); }
		else if(key == Keys::Camera::NEARZ)		        { nearZ = luabind::object_cast<double>(*it); }
		else if(key == Keys::Camera::FARZ)		        { farZ = luabind::object_cast<double>(*it); }
		else if(key == Keys::Camera::CLEARCOLOR)        { ClearColor = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if(key == Keys::Camera::PROCESS2D)         { process2D = luabind::object_cast<bool>(*it); }
	}

	std::shared_ptr<CameraINFO> obj(new CameraINFO());
	obj->Eye = eye;
	obj->TargetMagnitude = TM;
	obj->Up = up;
	obj->Roll = roll;
	obj->Pitch = pitch;
	obj->Yaw = yaw;
	obj->FovAngleY = FovAngleY;
	obj->nearZ = nearZ;
	obj->farZ = farZ;
	obj->ClearColor = ClearColor;
	obj->process2D = process2D;

	EntityConfig::SetEntity(obj);
	this->ID = obj->ID;
}
void LuaCamera::SetAsMain()
{
	ImportantIDConfig::CameraID::Set(this->ID);
}
		
void LuaCamera::MoveFroward(double distance)
{
	LuaMath::Vector4 eye = this->GetEye();
	LuaMath::Vector4 target = this->GetTargetMagintude();
	double pitch = this->GetPitch();
	double yaw = this->GetYaw();
	double roll = this->GetRoll();

	auto newEye = CHL::MoveForward(eye, target, pitch, yaw, roll, distance);
	this->SetEye(newEye);
}

void LuaCamera::SetEye(LuaMath::Vector4 eye)
{
	EntityConfig::SetEntity(this->ID, Keys::Camera::EYE, GenericObj<CHL::Vec4>::CreateNew(eye));
}
LuaMath::Vector4 LuaCamera::GetEye()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::EYE);
	return GenericObj<CHL::Vec4>::GetValue(obj);
}

void LuaCamera::SetTargetMagintude(LuaMath::Vector4 targetMagintude)
{
	EntityConfig::SetEntity(this->ID, Keys::Camera::TARGETMAGNITUDE, GenericObj<CHL::Vec4>::CreateNew(targetMagintude));
}
LuaMath::Vector4 LuaCamera::GetTargetMagintude()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::TARGETMAGNITUDE);
	return GenericObj<CHL::Vec4>::GetValue(obj);
}

void LuaCamera::SetUp(LuaMath::Vector4 up)
{
	EntityConfig::SetEntity(this->ID, Keys::Camera::UP, GenericObj<CHL::Vec4>::CreateNew(up));
}
LuaMath::Vector4 LuaCamera::GetUp()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::UP);
	return GenericObj<CHL::Vec4>::GetValue(obj);
}

void LuaCamera::SetRoll(double roll)
{
	EntityConfig::SetEntity(this->ID, Keys::Camera::RADIANROLL, GenericObj<double>::CreateNew(roll));
}
double LuaCamera::GetRoll()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::RADIANROLL);
	return GenericObj<double>::GetValue(obj);
}

void LuaCamera::SetPitch(double pitch)
{
	EntityConfig::SetEntity(this->ID, Keys::Camera::RADIANPITCH, GenericObj<double>::CreateNew(pitch));
}
double LuaCamera::GetPitch()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::RADIANPITCH);
	return GenericObj<double>::GetValue(obj);
}

void LuaCamera::SetYaw(double val)
{
	EntityConfig::SetEntity(this->ID, Keys::Camera::RADIANYAW, GenericObj<double>::CreateNew(val));
}
double LuaCamera::GetYaw()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::RADIANYAW);
	return GenericObj<double>::GetValue(obj);
}

void LuaCamera::SetFovAngle(double val)
{
	EntityConfig::SetEntity(this->ID, Keys::Camera::FOVANGLE, GenericObj<double>::CreateNew(val));
}
double LuaCamera::GetFovAngle()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::FOVANGLE);
	return GenericObj<double>::GetValue(obj);
}

void LuaCamera::SetNearZ(double val)
{
	EntityConfig::SetEntity(this->ID, Keys::Camera::NEARZ, GenericObj<double>::CreateNew(val));
}
double LuaCamera::GetNearZ()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::NEARZ);
	return GenericObj<double>::GetValue(obj);
}

void LuaCamera::SetFarZ(double val)
{

	EntityConfig::SetEntity(this->ID, Keys::Camera::RADIANYAW, GenericObj<double>::CreateNew(val));
}
double LuaCamera::GetFarZ()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::FARZ);
	return GenericObj<double>::GetValue(obj);
}

void LuaCamera::SetClearColor(LuaMath::Vector4 val)
{

	EntityConfig::SetEntity(this->ID, Keys::Camera::RADIANYAW, GenericObj<CHL::Vec4>::CreateNew(val));
}
LuaMath::Vector4 LuaCamera::GetClearColor()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::CLEARCOLOR);
	return GenericObj<CHL::Vec4>::GetValue(obj);
}

void LuaCamera::Release()
{
	EntityConfig::DeleteEntity(this->ID);
	this->ID = "";
}

void LuaCamera::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::class_<LuaCamera>("Camera")
			.def(luabind::constructor<luabind::object const&>())
			.property("Eye", &LuaCamera::GetEye, &LuaCamera::SetEye)
			.property("TargetMagintude", &LuaCamera::GetTargetMagintude, &LuaCamera::SetTargetMagintude)
			.property("Up", &LuaCamera::GetUp, &LuaCamera::SetUp)
			.property("Roll", &LuaCamera::GetRoll, &LuaCamera::SetRoll)
			.property("Pitch", &LuaCamera::GetPitch, &LuaCamera::SetPitch)
			.property("Yaw", &LuaCamera::GetYaw, &LuaCamera::SetYaw)
			.def("MoveFroward", &LuaCamera::MoveFroward)
			.def("SetAsMain", &LuaCamera::SetAsMain)
			.def("Release", &LuaCamera::Release)
	  ];
}