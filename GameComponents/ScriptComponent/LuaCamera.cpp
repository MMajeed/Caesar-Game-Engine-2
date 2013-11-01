#include "LuaCamera.h"

#include <Converter.h>
#include <3DMath.h>
#include <luabind\luabind.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <InfoCommunicator\AddObjectMessage.h>
#include <InfoCommunicator\UpdateObjectMessage.h>
#include <InfoCommunicator\ObjectManagerOutput.h>
#include <InfoCommunicator\InfoCommunicator.h>
#include <Keys.h>

LuaCamera::LuaCamera(LuaUblas::Vector4 eye, LuaUblas::Vector4 targetMagintude, LuaUblas::Vector4 up, double roll, double pitch, double yaw)
{
	CHL::MapQ<std::string, std::shared_ptr<Object>> camera;

	camera[Keys::Class] = GenericObject<std::string>::CreateNew(Keys::ClassType::Camera);
	camera[Keys::EYE] = GenericObject<CHL::Vec4>::CreateNew(eye.vector);
	camera[Keys::TARGETMAGNITUDE] = GenericObject<CHL::Vec4>::CreateNew(targetMagintude.vector);
	camera[Keys::UP] = GenericObject<CHL::Vec4>::CreateNew(up.vector);
	camera[Keys::RADIANROLL] = GenericObject<double>::CreateNew(roll);
	camera[Keys::RADIANPITCH] = GenericObject<double>::CreateNew(pitch);
	camera[Keys::RADIANYAW] = GenericObject<double>::CreateNew(yaw);

	std::shared_ptr<AddObjectMessage> msg(new AddObjectMessage(camera));

	InfoCommunicator::SubmitMessage(msg);

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

	auto newEye = CHL::MoveForward(eye, target, pitch, yaw, roll, distance);
	this->SetEye(newEye);
}

void LuaCamera::SetEye(LuaUblas::Vector4 eye)
{
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(eye.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::EYE, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaUblas::Vector4 LuaCamera::GetEye()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::EYE];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}

void LuaCamera::SetTargetMagintude(LuaUblas::Vector4 targetMagintude)
{	
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(targetMagintude.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::TARGETMAGNITUDE, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaUblas::Vector4 LuaCamera::GetTargetMagintude()
{	
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::TARGETMAGNITUDE];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}

void LuaCamera::SetUp(LuaUblas::Vector4 up)
{	
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(up.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::UP, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaUblas::Vector4 LuaCamera::GetUp()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::UP];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}

void LuaCamera::SetRoll(double roll)
{	
	std::shared_ptr<Object> obj = GenericObject<double>::CreateNew(roll);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::RADIANROLL, obj));
	InfoCommunicator::SubmitMessage(msg);
}
double LuaCamera::GetRoll()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID);
	return GenericObject<double>::GetValue(obj[Keys::RADIANROLL]);
}

void LuaCamera::SetPitch(double pitch)
{
	std::shared_ptr<Object> obj = GenericObject<double>::CreateNew(pitch);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::RADIANPITCH, obj));
	InfoCommunicator::SubmitMessage(msg);
}
double LuaCamera::GetPitch()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID);
	return GenericObject<double>::GetValue(obj[Keys::RADIANPITCH]);
}

void LuaCamera::SetYaw(double yaw)
{
	std::shared_ptr<Object> obj = GenericObject<double>::CreateNew(yaw);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::RADIANYAW, obj));
	InfoCommunicator::SubmitMessage(msg);
}
double LuaCamera::GetYaw()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID);
	return GenericObject<double>::GetValue(obj[Keys::RADIANYAW]);
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