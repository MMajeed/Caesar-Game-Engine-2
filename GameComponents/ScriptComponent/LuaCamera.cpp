#include "LuaCamera.h"

#include <Converter.h>
#include <MathOperations.h>
#include <luabind\luabind.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <InfoCommunicator\AddObjectMessage.h>
#include <InfoCommunicator\UpdateObjectMessage.h>
#include <InfoCommunicator\ObjectManagerOutput.h>
#include <InfoCommunicator\InfoCommunicator.h>
#include <Keys.h>

LuaCamera::LuaCamera(LuaUblas::Vector4 eye, LuaUblas::Vector4 targetMagintude, LuaUblas::Vector4 up, double roll, double pitch, double yaw)
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

	InfoCommunicator::SubmitMessage(msg);

	msg->WaitTillProcccesed();

	this->ID = msg->ID;
}
void LuaCamera::SetAsMain()
{

}
		
void LuaCamera::MoveFroward(double distance)
{
	LuaUblas::Vector4 eye = this->GetEye();
	LuaUblas::Vector4 target = this->GetTargetMagintude();
	double pitch = this->GetPitch();
	double yaw = this->GetYaw();
	double roll = this->GetRoll();

	auto newEye = MathOperations::MoveForward(eye, target, pitch, yaw, roll, distance);
	this->SetEye(newEye);
}

void LuaCamera::SetEye(LuaUblas::Vector4 eye)
{
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::EYE, CHL::ToString(eye.vector)));
	InfoCommunicator::SubmitMessage(msg);
}
LuaUblas::Vector4 LuaCamera::GetEye()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID);
	return CHL::sstringConverter<boost::numeric::ublas::vector<double>, std::string>(obj[Keys::EYE]);
}

void LuaCamera::SetTargetMagintude(LuaUblas::Vector4 targetMagintude)
{
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::TARGETMAGNITUDE, CHL::ToString(targetMagintude.vector)));
	InfoCommunicator::SubmitMessage(msg);
}
LuaUblas::Vector4 LuaCamera::GetTargetMagintude()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID);
	return CHL::sstringConverter<boost::numeric::ublas::vector<double>, std::string>(obj[Keys::TARGETMAGNITUDE]);
}

void LuaCamera::SetUp(LuaUblas::Vector4 up)
{
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::UP, CHL::ToString(up.vector)));
	InfoCommunicator::SubmitMessage(msg);
}
LuaUblas::Vector4 LuaCamera::GetUp()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID);
	return CHL::sstringConverter<boost::numeric::ublas::vector<double>, std::string>(obj[Keys::UP]);
}

void LuaCamera::SetRoll(double roll)
{
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::RADIANROLL, CHL::ToString(roll)));
	InfoCommunicator::SubmitMessage(msg);
}
double LuaCamera::GetRoll()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID);
	return CHL::sstringConverter<double, std::string>(obj[Keys::RADIANROLL]);
}

void LuaCamera::SetPitch(double pitch)
{
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::RADIANPITCH, CHL::ToString(pitch)));
	InfoCommunicator::SubmitMessage(msg);
}
double LuaCamera::GetPitch()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID);
	return CHL::sstringConverter<double, std::string>(obj[Keys::RADIANPITCH]);
}

void LuaCamera::SetYaw(double yaw)
{
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::RADIANYAW, CHL::ToString(yaw)));
	InfoCommunicator::SubmitMessage(msg);
}
double LuaCamera::GetYaw()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID);
	return CHL::sstringConverter<double, std::string>(obj[Keys::RADIANYAW]);
}

void LuaCamera::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::class_<LuaCamera>("Camera")
		  .def(luabind::constructor<LuaUblas::Vector4, LuaUblas::Vector4, LuaUblas::Vector4, double, double, double>())
		  .property("Eye", &LuaCamera::GetEye, &LuaCamera::SetEye)
		  .property("TargetMagintude", &LuaCamera::GetTargetMagintude, &LuaCamera::SetTargetMagintude)
		  .property("Up", &LuaCamera::GetUp, &LuaCamera::SetUp)
		  .property("Roll", &LuaCamera::GetRoll, &LuaCamera::SetRoll)
		  .property("Pitch", &LuaCamera::GetPitch, &LuaCamera::SetPitch)
		  .property("Yaw", &LuaCamera::GetYaw, &LuaCamera::SetYaw)
		  .def("MoveFroward", &LuaCamera::MoveFroward)
	  ];
}