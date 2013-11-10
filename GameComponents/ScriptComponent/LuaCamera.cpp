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

LuaCamera::LuaCamera(luabind::object const& table)
{
	if (luabind::type(table) != LUA_TTABLE)
		throw std::exception("Wrong paramter for Camera, please send in a table");

	CHL::Vec4 eye;	eye(0) = 0.0; eye(1) = 0.0; eye(2) = 0.0; eye(3) = 0.0;
	CHL::Vec4 TM;	TM(0) = 0.0; TM(1) = 0.0; TM(2) = 1.0; TM(3) = 0.0;
	CHL::Vec4 up;	TM(0) = 0.0; TM(1) = 0.0; TM(2) = 0.0; TM(3) = 0.0;
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

	CHL::MapQ<std::string, std::shared_ptr<Object>> camera;
	camera[Keys::Class] = GenericObject<std::string>::CreateNew(Keys::ClassType::Camera);
	camera[Keys::Camera::EYE] = GenericObject<CHL::Vec4>::CreateNew(eye);
	camera[Keys::Camera::TARGETMAGNITUDE] = GenericObject<CHL::Vec4>::CreateNew(TM);
	camera[Keys::Camera::UP] = GenericObject<CHL::Vec4>::CreateNew(up);
	camera[Keys::Camera::RADIANROLL] = GenericObject<double>::CreateNew(roll);
	camera[Keys::Camera::RADIANPITCH] = GenericObject<double>::CreateNew(pitch);
	camera[Keys::Camera::RADIANYAW] = GenericObject<double>::CreateNew(yaw);
	std::shared_ptr<AddObjectMessage> msg(new AddObjectMessage(camera));
	InfoCommunicator::SubmitMessage(msg);
	this->ID = msg->ID;
}
void LuaCamera::SetAsMain()
{

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
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(eye.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::Camera::EYE, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaMath::Vector4 LuaCamera::GetEye()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::Camera::EYE];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}

void LuaCamera::SetTargetMagintude(LuaMath::Vector4 targetMagintude)
{	
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(targetMagintude.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::Camera::TARGETMAGNITUDE, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaMath::Vector4 LuaCamera::GetTargetMagintude()
{	
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::Camera::TARGETMAGNITUDE];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}

void LuaCamera::SetUp(LuaMath::Vector4 up)
{	
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(up.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::Camera::UP, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaMath::Vector4 LuaCamera::GetUp()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::Camera::UP];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}

void LuaCamera::SetRoll(double roll)
{	
	std::shared_ptr<Object> obj = GenericObject<double>::CreateNew(roll);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::Camera::RADIANROLL, obj));
	InfoCommunicator::SubmitMessage(msg);
}
double LuaCamera::GetRoll()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID);
	return GenericObject<double>::GetValue(obj[Keys::Camera::RADIANROLL]);
}

void LuaCamera::SetPitch(double pitch)
{
	std::shared_ptr<Object> obj = GenericObject<double>::CreateNew(pitch);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::Camera::RADIANPITCH, obj));
	InfoCommunicator::SubmitMessage(msg);
}
double LuaCamera::GetPitch()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID);
	return GenericObject<double>::GetValue(obj[Keys::Camera::RADIANPITCH]);
}

void LuaCamera::SetYaw(double yaw)
{
	std::shared_ptr<Object> obj = GenericObject<double>::CreateNew(yaw);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::Camera::RADIANYAW, obj));
	InfoCommunicator::SubmitMessage(msg);
}
double LuaCamera::GetYaw()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID);
	return GenericObject<double>::GetValue(obj[Keys::Camera::RADIANYAW]);
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
	  ];
}