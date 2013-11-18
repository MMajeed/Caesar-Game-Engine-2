#include "LuaCamera.h"

#include <Converter.h>
#include <3DMath.h>
#include <luabind\luabind.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <InfoCommunicator\AddObjectMessage.h>
#include <InfoCommunicator\UpdateObjectMessage.h>
#include <InfoCommunicator\GetObjectINFO.h>
#include <InfoCommunicator\InfoCommunicator.h>
#include <GraphicCommunicator\SetGraphicSettings.h>
#include <GraphicCommunicator\GraphicCommunicator.h>
#include <Keys.h>

LuaCamera::LuaCamera(luabind::object const& table)
{
	if (luabind::type(table) != LUA_TTABLE)
		throw std::exception("Wrong paramter for Camera, please send in a table");

	CHL::Vec4 eye;	eye(0) = 0.0; eye(1) = 0.0; eye(2) = 0.0; eye(3) = 0.0;
	CHL::Vec4 TM;	TM(0) = 0.0; TM(1) = 0.0; TM(2) = 1.0; TM(3) = 0.0;
	CHL::Vec4 up;	up(0) = 0.0; up(1) = 1.0; up(2) = 0.0; up(3) = 0.0;
	double roll = 0.0;	double pitch = 0.0;		double yaw = 0.0;

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
		else if (key == Keys::Camera::RADIANYAW)		{ yaw = luabind::object_cast<double>(*it); }
	}

	std::shared_ptr<CameraINFO> obj(new CameraINFO());
	obj->Eye = eye;
	obj->TargetMagnitude = TM;
	obj->Up = up;
	obj->Roll = roll;
	obj->Pitch = pitch;
	obj->Yaw = yaw;

	std::shared_ptr<AddObjectMessage> msg(new AddObjectMessage(obj));
	InfoCommunicator::SubmitMessage(msg);
	this->ID = obj->ID;
}
void LuaCamera::SetAsMain()
{
	std::shared_ptr<SetCameraIDMessage> msg(new SetCameraIDMessage(this->ID));
	GraphicCommunicator::SubmitMessage(msg);
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
	auto obj = this->GetCameraINFO();
	obj->Eye = eye;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}
LuaMath::Vector4 LuaCamera::GetEye()
{
	return this->GetCameraINFO()->Eye;
}

void LuaCamera::SetTargetMagintude(LuaMath::Vector4 targetMagintude)
{
	auto obj = this->GetCameraINFO();
	obj->TargetMagnitude = targetMagintude;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}
LuaMath::Vector4 LuaCamera::GetTargetMagintude()
{
	return this->GetCameraINFO()->TargetMagnitude;
}

void LuaCamera::SetUp(LuaMath::Vector4 up)
{	
	auto obj = this->GetCameraINFO();
	obj->Up = up;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}
LuaMath::Vector4 LuaCamera::GetUp()
{
	return this->GetCameraINFO()->Up;
}

void LuaCamera::SetRoll(double roll)
{
	auto obj = this->GetCameraINFO();
	obj->Roll = roll;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}
double LuaCamera::GetRoll()
{
	return this->GetCameraINFO()->Roll;
}

void LuaCamera::SetPitch(double pitch)
{
	auto obj = this->GetCameraINFO();
	obj->Pitch = pitch;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}
double LuaCamera::GetPitch()
{
	return this->GetCameraINFO()->Pitch;
}

void LuaCamera::SetYaw(double yaw)
{
	auto obj = this->GetCameraINFO();
	obj->Yaw = yaw;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}
double LuaCamera::GetYaw()
{
	return this->GetCameraINFO()->Yaw;
}

std::shared_ptr<CameraINFO> LuaCamera::GetCameraINFO()
{
	std::shared_ptr<CameraINFO> returnValue;

	auto obj = GetObjectINFO::GetObject(this->ID);
	if(obj)
	{
		returnValue = std::dynamic_pointer_cast<CameraINFO>(obj);
		if(!returnValue){ throw std::exception("Attempted to cast an Object to SpotLightINFO and failed"); }
	}
	return returnValue;
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
	  ];
}