#include "LuaObject.h"

#include <luabind\luabind.hpp>
#include <string>
#include <Converter.h>
#include <Keys.h>
#include <InfoCommunicator\AddObjectMessage.h>
#include <InfoCommunicator\UpdateObjectMessage.h>
#include <InfoCommunicator\ObjectManagerOutput.h>
#include <InfoCommunicator\InfoCommunicator.h>
#include <boost/numeric/ublas/io.hpp>

LuaObject::LuaObject()
{
	std::hash_map<std::string, std::string> mapKeys;

	mapKeys[Keys::GRAPHICDRAWABLEID] = "";

	boost::numeric::ublas::vector<double> loc(4);
	loc(0) = 0;	loc(1) = 0;	loc(2) = 0;	loc(3) = 0;	
	mapKeys[Keys::LOCATION] = CHL::ToString(loc);

	boost::numeric::ublas::vector<double> rot(4);
	rot(0) = 0;	rot(1) = 0;	rot(2) = 0;	rot(3) = 0;	
	mapKeys[Keys::ROTATION] = CHL::ToString(rot);

	boost::numeric::ublas::vector<double> sca(4);
	sca(0) = 1.0;	sca(1) = 1.0;	sca(2) = 1.0;	sca(3) = 1.0;	
	mapKeys[Keys::SCALE] = CHL::ToString(sca);	

	boost::numeric::ublas::vector<double> col(4);
	col(0) = 1.0;	col(1) = 1.0;	col(2) = 1.0;	col(3) = 1.0;	
	mapKeys[Keys::COLOUR] = CHL::ToString(col);

	std::shared_ptr<AddObjectMessage> msg(new AddObjectMessage(mapKeys));

	InfoCommunicator::SubmitMessage(msg);

	msg->WaitTillProcccesed();

	this->ID = msg->ID;
}

void LuaObject::SetGraphic(LuaBasicDrawableObject graphic)
{
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::GRAPHICDRAWABLEID, graphic.ID));
	InfoCommunicator::SubmitMessage(msg);
}
void LuaObject::RemoveGraphic()
{
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::GRAPHICDRAWABLEID, ""));
	InfoCommunicator::SubmitMessage(msg);
}

void LuaObject::SetTexture(LuaBasicTexture texture)
{
	std::string textureID = Keys::TEXTUREFILE + texture.ID;
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, textureID, texture.ID));
	InfoCommunicator::SubmitMessage(msg);
}
void LuaObject::RemoveTexture(LuaBasicTexture texture)
{
	std::string textureID = Keys::TEXTUREFILE + texture.ID;
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, textureID, ""));
	InfoCommunicator::SubmitMessage(msg);
}

void LuaObject::SetLocation(LuaUblas::Vector4 vec)
{
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::LOCATION, CHL::ToString(vec.vector)));
	InfoCommunicator::SubmitMessage(msg);
}
LuaUblas::Vector4 LuaObject::GetLocation()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID);
	return CHL::sstringConverter<boost::numeric::ublas::vector<double>, std::string>(obj[Keys::LOCATION]);
}

void LuaObject::SetScale(LuaUblas::Vector4 vec)
{
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::SCALE, CHL::ToString(vec.vector)));
	InfoCommunicator::SubmitMessage(msg);
}
LuaUblas::Vector4 LuaObject::GetScale()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID);
	return CHL::sstringConverter<boost::numeric::ublas::vector<double>, std::string>(obj[Keys::SCALE]);
}

void LuaObject::SetRotation(LuaUblas::Vector4 vec)
{
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::ROTATION, CHL::ToString(vec.vector)));
	InfoCommunicator::SubmitMessage(msg);
}
LuaUblas::Vector4 LuaObject::GetRotation()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID);
	return CHL::sstringConverter<boost::numeric::ublas::vector<double>, std::string>(obj[Keys::ROTATION]);
}

void LuaObject::SetColour(LuaUblas::Vector4 vec)
{
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::COLOUR, CHL::ToString(vec.vector)));
	InfoCommunicator::SubmitMessage(msg);
}
LuaUblas::Vector4 LuaObject::GetColour()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID);
	return CHL::sstringConverter<boost::numeric::ublas::vector<double>, std::string>(obj[Keys::COLOUR]);
}

void LuaObject::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::class_<LuaObject>("Object")
		  .def(luabind::constructor<>())
		  .def_readonly("ID", &LuaObject::ID)
		  .def("SetGraphic", &LuaObject::SetGraphic)
		  .def("RemoveGraphic", &LuaObject::RemoveGraphic)
		  .def("SetTexture", &LuaObject::SetTexture)
		  .def("RemoveTexture", &LuaObject::RemoveTexture)
		  .property("Location", &LuaObject::GetLocation, &LuaObject::SetLocation)
		  .property("Scale", &LuaObject::GetScale, &LuaObject::SetScale)
		  .property("Rotation", &LuaObject::GetRotation, &LuaObject::SetRotation)
		  .property("Colour", &LuaObject::GetColour, &LuaObject::SetColour)
	  ];
}