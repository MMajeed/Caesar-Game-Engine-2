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
	std::hash_map<std::string, std::shared_ptr<Object>> mapKeys;

	mapKeys[Keys::GRAPHICDRAWABLEID] = std::shared_ptr<Object>(new GenericObject<std::string>(""));

	CHL::Vec4 loc;
	loc(0) = 0;	loc(1) = 0;	loc(2) = 0;	loc(3) = 0;	
	mapKeys[Keys::LOCATION] = GenericObject<CHL::Vec4>::CreateNew(loc);

	CHL::Vec4 rot;
	rot(0) = 0;	rot(1) = 0;	rot(2) = 0;	rot(3) = 0;	
	mapKeys[Keys::ROTATION] = GenericObject<CHL::Vec4>::CreateNew(rot);

	CHL::Vec4 sca;
	sca(0) = 1.0;	sca(1) = 1.0;	sca(2) = 1.0;	sca(3) = 1.0;	
	mapKeys[Keys::SCALE] = GenericObject<CHL::Vec4>::CreateNew(sca);

	CHL::Vec4 col;
	col(0) = 1.0;	col(1) = 1.0;	col(2) = 1.0;	col(3) = 1.0;	
	mapKeys[Keys::DIFFUSE] = GenericObject<CHL::Vec4>::CreateNew(col);
	mapKeys[Keys::AMBIENT] = GenericObject<CHL::Vec4>::CreateNew(col);
	mapKeys[Keys::SPECULAR] = GenericObject<CHL::Vec4>::CreateNew(col);

	std::shared_ptr<AddObjectMessage> msg(new AddObjectMessage(mapKeys));

	InfoCommunicator::SubmitMessage(msg);

	msg->WaitTillProcccesed();

	this->ID = msg->ID;
}

void LuaObject::SetGraphic(LuaBasicDrawableObject graphic)
{
	std::shared_ptr<Object> obj = GenericObject<std::string>::CreateNew(graphic.ID);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::GRAPHICDRAWABLEID, obj));
	InfoCommunicator::SubmitMessage(msg);
}
void LuaObject::RemoveGraphic()
{
	std::shared_ptr<Object> obj = GenericObject<std::string>::CreateNew("");
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::GRAPHICDRAWABLEID, obj));
	InfoCommunicator::SubmitMessage(msg);
}

void LuaObject::SetTexture(LuaBasicTexture texture)
{
	std::shared_ptr<Object> obj = GenericObject<std::string>::CreateNew(texture.ID);
	std::string textureID = Keys::TEXTUREFILE + texture.ID;
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, textureID, obj));
	InfoCommunicator::SubmitMessage(msg);
}
void LuaObject::RemoveTexture(LuaBasicTexture texture)
{
	std::shared_ptr<Object> obj = GenericObject<std::string>::CreateNew("");
	std::string textureID = Keys::TEXTUREFILE + texture.ID;
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, textureID, obj));
	InfoCommunicator::SubmitMessage(msg);
}

void LuaObject::SetLocation(LuaUblas::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(vec.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::LOCATION, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaUblas::Vector4 LuaObject::GetLocation()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::LOCATION];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}

void LuaObject::SetScale(LuaUblas::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(vec.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::SCALE, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaUblas::Vector4 LuaObject::GetScale()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::SCALE];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}

void LuaObject::SetRotation(LuaUblas::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(vec.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::ROTATION, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaUblas::Vector4 LuaObject::GetRotation()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::ROTATION];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}

void LuaObject::SetDiffuse(LuaUblas::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(vec.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::DIFFUSE, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaUblas::Vector4 LuaObject::GetDiffuse()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::DIFFUSE];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}

void LuaObject::SetAmibent(LuaUblas::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(vec.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::AMBIENT, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaUblas::Vector4 LuaObject::GetAmibent()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::AMBIENT];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}

void LuaObject::SetSpecular(LuaUblas::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(vec.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::SPECULAR, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaUblas::Vector4 LuaObject::GetSpecular()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::SPECULAR];
	return GenericObject<CHL::Vec4>::GetValue(obj);
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
		  .property("Diffuse", &LuaObject::GetDiffuse, &LuaObject::SetDiffuse)
		  .property("Amibent", &LuaObject::GetAmibent, &LuaObject::SetAmibent)
		  .property("Specular", &LuaObject::GetSpecular, &LuaObject::SetSpecular)
	  ];
}