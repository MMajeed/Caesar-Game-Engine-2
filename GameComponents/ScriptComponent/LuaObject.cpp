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

	mapKeys[Keys::BasicDrawable::GRAPHICDRAWABLEID] = GenericObject<std::string>::CreateNew("");

	CHL::Vec4 loc;
	loc(0) = 0;	loc(1) = 0;	loc(2) = 0;	loc(3) = 0;	
	mapKeys[Keys::ObjectInfo::LOCATION] = GenericObject<CHL::Vec4>::CreateNew(loc);

	CHL::Vec4 rot;
	rot(0) = 0;	rot(1) = 0;	rot(2) = 0;	rot(3) = 0;	
	mapKeys[Keys::ObjectInfo::ROTATION] = GenericObject<CHL::Vec4>::CreateNew(rot);

	CHL::Vec4 sca;
	sca(0) = 1.0;	sca(1) = 1.0;	sca(2) = 1.0;	sca(3) = 1.0;	
	mapKeys[Keys::ObjectInfo::SCALE] = GenericObject<CHL::Vec4>::CreateNew(sca);

	CHL::Vec4 col;
	col(0) = 1.0;	col(1) = 1.0;	col(2) = 1.0;	col(3) = 1.0;	
	mapKeys[Keys::ObjectInfo::DIFFUSE] = GenericObject<CHL::Vec4>::CreateNew(col);
	mapKeys[Keys::ObjectInfo::AMBIENT] = GenericObject<CHL::Vec4>::CreateNew(col);
	mapKeys[Keys::ObjectInfo::SPECULAR] = GenericObject<CHL::Vec4>::CreateNew(col);

	std::shared_ptr<AddObjectMessage> msg(new AddObjectMessage(mapKeys));

	InfoCommunicator::SubmitMessage(msg);

	this->ID = msg->ID;
}

void LuaObject::SetGraphic(LuaBasicDrawableObject graphic)
{
	std::shared_ptr<Object> obj = GenericObject<std::string>::CreateNew(graphic.ID);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::BasicDrawable::GRAPHICDRAWABLEID, obj));
	InfoCommunicator::SubmitMessage(msg);
}
void LuaObject::RemoveGraphic()
{
	std::shared_ptr<Object> obj = GenericObject<std::string>::CreateNew("");
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::BasicDrawable::GRAPHICDRAWABLEID, obj));
	InfoCommunicator::SubmitMessage(msg);
}

void LuaObject::SetTexture(LuaBasicTexture texture)
{
	std::shared_ptr<Object> obj = GenericObject<std::string>::CreateNew(texture.ID);
	std::string textureID = Keys::BasicTexture::TEXTUREFILE + texture.ID;
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, textureID, obj));
	InfoCommunicator::SubmitMessage(msg);
}
void LuaObject::RemoveTexture(LuaBasicTexture texture)
{
	std::shared_ptr<Object> obj = GenericObject<std::string>::CreateNew("");
	std::string textureID = Keys::BasicTexture::TEXTUREFILE + texture.ID;
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, textureID, obj));
	InfoCommunicator::SubmitMessage(msg);
}

void LuaObject::SetLocation(LuaMath::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(vec.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::ObjectInfo::LOCATION, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaMath::Vector4 LuaObject::GetLocation()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::ObjectInfo::LOCATION];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}

void LuaObject::SetScale(LuaMath::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(vec.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::ObjectInfo::SCALE, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaMath::Vector4 LuaObject::GetScale()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::ObjectInfo::SCALE];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}

void LuaObject::SetRotation(LuaMath::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(vec.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::ObjectInfo::ROTATION, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaMath::Vector4 LuaObject::GetRotation()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::ObjectInfo::ROTATION];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}

void LuaObject::SetDiffuse(LuaMath::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(vec.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::ObjectInfo::DIFFUSE, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaMath::Vector4 LuaObject::GetDiffuse()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::ObjectInfo::DIFFUSE];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}

void LuaObject::SetAmibent(LuaMath::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(vec.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::ObjectInfo::AMBIENT, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaMath::Vector4 LuaObject::GetAmibent()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::ObjectInfo::AMBIENT];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}

void LuaObject::SetSpecular(LuaMath::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(vec.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::ObjectInfo::SPECULAR, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaMath::Vector4 LuaObject::GetSpecular()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::ObjectInfo::SPECULAR];
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