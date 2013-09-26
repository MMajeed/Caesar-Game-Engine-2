#include "LuaCamera.h"

#include <Converter.h>
#include <luabind\luabind.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <InfoCommunicator\AddObjectMessage.h>
#include <InfoCommunicator\UpdateObjectMessage.h>
#include <InfoCommunicator\ObjectManagerOutput.h>
#include <InfoCommunicator\GetInfoManager.h>
#include <Keys.h>

LuaCameraSetup::LuaCamera::LuaCamera(LuaUblas::Vector4 eye, LuaUblas::Vector4 targetMagintude, LuaUblas::Vector4 up, double roll, double pitch, double yaw)
{
	CHL::MapQ<std::string, std::string> camera;

	camera[Keys::Class] = Keys::ClassType::Camera;
	camera[Keys::EYE] = CHL::ToString(eye.vector);
	camera[Keys::TARGETMAGNITUDE] = CHL::ToString(targetMagintude.vector);
	camera[Keys::UP] = CHL::ToString(up.vector);
	camera[Keys::RADIANROLL] = CHL::ToString(roll);
	camera[Keys::RADIANPITCH] = CHL::ToString(pitch);
	camera[Keys::RADIANYAW] = CHL::ToString(yaw);

	std::shared_ptr<AddObjectMessage> msg(new AddObjectMessage(camera));

	GetInfoManager::GetComponent()->SubmitMessage(msg);

	msg->WaitTillProcccesed();

	this->ID = msg->ID;
}
void LuaCameraSetup::LuaCamera::SetAsMain()
{

}
		
void LuaCameraSetup::LuaCamera::MoveFroward(double distance)
{

}

void LuaCameraSetup::LuaCamera::SetEye(LuaUblas::Vector4 eye)
{
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::EYE, CHL::ToString(eye.vector)));
	GetInfoManager::GetComponent()->SubmitMessage(msg);
}
LuaUblas::Vector4 LuaCameraSetup::LuaCamera::GetEye()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID);
	return CHL::sstringConverter<boost::numeric::ublas::vector<double>, std::string>(obj[Keys::EYE]);
}

void LuaCameraSetup::LuaCamera::SetTargetMagintude(LuaUblas::Vector4 targetMagintude)
{
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::TARGETMAGNITUDE, CHL::ToString(targetMagintude.vector)));
	GetInfoManager::GetComponent()->SubmitMessage(msg);
}
LuaUblas::Vector4 LuaCameraSetup::LuaCamera::GetTargetMagintude()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID);
	return CHL::sstringConverter<boost::numeric::ublas::vector<double>, std::string>(obj[Keys::TARGETMAGNITUDE]);
}

void LuaCameraSetup::LuaCamera::SetUp(LuaUblas::Vector4 up)
{
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::UP, CHL::ToString(up.vector)));
	GetInfoManager::GetComponent()->SubmitMessage(msg);
}
LuaUblas::Vector4 LuaCameraSetup::LuaCamera::GetUp()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID);
	return CHL::sstringConverter<boost::numeric::ublas::vector<double>, std::string>(obj[Keys::UP]);
}

void LuaCameraSetup::LuaCamera::SetRoll(double roll)
{
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::RADIANROLL, CHL::ToString(roll)));
	GetInfoManager::GetComponent()->SubmitMessage(msg);
}
double LuaCameraSetup::LuaCamera::GetRoll()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID);
	return CHL::sstringConverter<double, std::string>(obj[Keys::RADIANROLL]);
}

void LuaCameraSetup::LuaCamera::SetPitch(double pitch)
{
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::RADIANPITCH, CHL::ToString(pitch)));
	GetInfoManager::GetComponent()->SubmitMessage(msg);
}
double LuaCameraSetup::LuaCamera::GetPitch()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID);
	return CHL::sstringConverter<double, std::string>(obj[Keys::RADIANPITCH]);
}

void LuaCameraSetup::LuaCamera::SetYaw(double yaw)
{
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::RADIANYAW, CHL::ToString(yaw)));
	GetInfoManager::GetComponent()->SubmitMessage(msg);
}
double LuaCameraSetup::LuaCamera::GetYaw()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID);
	return CHL::sstringConverter<double, std::string>(obj[Keys::RADIANYAW]);
}

void LuaCameraSetup::LuaCamera::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::class_<LuaCameraSetup::LuaCamera>("Camera")
		  .def(luabind::constructor<LuaUblas::Vector4, LuaUblas::Vector4, LuaUblas::Vector4, double, double, double>())
		  .property("Eye", &LuaCameraSetup::LuaCamera::GetEye, &LuaCameraSetup::LuaCamera::SetEye)
		  .property("TargetMagintude", &LuaCameraSetup::LuaCamera::GetTargetMagintude, &LuaCameraSetup::LuaCamera::SetTargetMagintude)
		  .property("Up", &LuaCameraSetup::LuaCamera::GetUp, &LuaCameraSetup::LuaCamera::SetUp)
		  .property("Roll", &LuaCameraSetup::LuaCamera::GetRoll, &LuaCameraSetup::LuaCamera::SetRoll)
		  .property("Pitch", &LuaCameraSetup::LuaCamera::GetPitch, &LuaCameraSetup::LuaCamera::SetPitch)
		  .property("Yaw", &LuaCameraSetup::LuaCamera::GetYaw, &LuaCameraSetup::LuaCamera::SetYaw)
	  ];
}