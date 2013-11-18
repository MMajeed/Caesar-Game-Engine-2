#include "LuaObject.h"

#include <luabind\luabind.hpp>
#include <string>
#include <Converter.h>
#include <Keys.h>
#include <InfoCommunicator\AddObjectMessage.h>
#include <InfoCommunicator\UpdateObjectMessage.h>
#include <InfoCommunicator\GetObjectINFO.h>
#include <InfoCommunicator\InfoCommunicator.h>
#include <ObjectINFO.h>

LuaObject::LuaObject()
{
	CHL::Vec4 loc;	loc(0) = 0;	loc(1) = 0;	loc(2) = 0;	loc(3) = 0;	
	CHL::Vec4 rot;  rot(0) = 0;	rot(1) = 0;	rot(2) = 0;	rot(3) = 0;	
	CHL::Vec4 sca;  sca(0) = 1.0;	sca(1) = 1.0;	sca(2) = 1.0;	sca(3) = 1.0;	
	CHL::Vec4 col;  col(0) = 1.0;	col(1) = 1.0;	col(2) = 1.0;	col(3) = 1.0;

	std::shared_ptr<ObjectINFO> obj(new ObjectINFO());
	obj->Location = loc;
	obj->Rotation = rot;
	obj->Scale = sca;
	obj->Diffuse = col;
	obj->Ambient = col;
	obj->Specular = col;

	std::shared_ptr<AddObjectMessage> msg(new AddObjectMessage(obj));

	InfoCommunicator::SubmitMessage(msg);

	this->ID = obj->ID;
}
LuaObject::LuaObject(luabind::object const& table)
{
	if (luabind::type(table) != LUA_TTABLE)
		throw std::exception("Wrong paramter for Camera, please send in a table");

	CHL::Vec4 loc;	loc(0) = 0.0; loc(1) = 0.0; loc(2) = 0.0; loc(3) = 0.0;
	CHL::Vec4 rot;	rot(0) = 0.0; rot(1) = 0.0; rot(2) = 0.0; rot(3) = 0.0;
	CHL::Vec4 sca;	sca(0) = 1.0; sca(1) = 1.0; sca(2) = 1.0; sca(3) = 1.0;
	CHL::Vec4 diffuse;	diffuse(0) = 1.0; diffuse(1) = 1.0; diffuse(2) = 1.0; diffuse(3) = 1.0;
	CHL::Vec4 amibent;	amibent(0) = 1.0; amibent(1) = 1.0; amibent(2) = 1.0; amibent(3) = 1.0;
	CHL::Vec4 specular;	specular(0) = 1.0; specular(1) = 1.0; specular(2) = 1.0; specular(3) = 1.0;
	std::string graphicDrawable;
	std::hash_map<unsigned int, std::string>  textures;

	for (luabind::iterator it(table);
		it != luabind::iterator();
		++it)
	{
		std::string key = luabind::object_cast<std::string>(it.key());

			 if (key == Keys::ObjectInfo::LOCATION)		{ loc = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::ObjectInfo::ROTATION)		{ rot = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::ObjectInfo::SCALE)		{ sca = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::ObjectInfo::DIFFUSE)		{ diffuse = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::ObjectInfo::AMBIENT)		{ amibent = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::ObjectInfo::SPECULAR)		{ specular = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::ObjectInfo::DRAWABLEOBJ)	{ graphicDrawable = luabind::object_cast<LuaBasicDrawableObject>(*it).ID; }
		else if (key.compare(0, Keys::ObjectInfo::TEXTUREOBJ.size(), Keys::ObjectInfo::TEXTUREOBJ) == 0)
		{
			std::string textureID = luabind::object_cast<LuaBasicTexture>(*it).ID;
			int textureSlot = 0;
			std::string parse = key.substr(Keys::ObjectInfo::TEXTUREOBJ.size() );
			if (!parse.empty())
			{
				std::stringstream ss;
				ss << parse;
				ss >> textureSlot;
			}
			textures[textureSlot] = textureID;
		}
	}

	std::shared_ptr<ObjectINFO> obj(new ObjectINFO());
	obj->Location = loc;
	obj->Rotation = rot;
	obj->Scale = sca;
	obj->Diffuse = diffuse;
	obj->Ambient = amibent;
	obj->Specular = specular;
	obj->DrawObjID = graphicDrawable;
	obj->TextureVecs = textures;

	std::shared_ptr<AddObjectMessage> msg(new AddObjectMessage(obj));
	InfoCommunicator::SubmitMessage(msg);
	this->ID = obj->ID;
}

void LuaObject::SetGraphic(LuaBasicDrawableObject graphic)
{
	auto obj = this->GetObject();
	obj->DrawObjID = graphic.ID;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}
void LuaObject::RemoveGraphic()
{
	auto obj = this->GetObject();
	obj->DrawObjID = "";

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}

void LuaObject::SetTexture(LuaBasicTexture texture)
{
	auto obj = this->GetObject();
	obj->TextureVecs[0] = texture.ID;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);

}
void LuaObject::SetTextureAndSlot(LuaBasicTexture texture, int slot)
{
	auto obj = this->GetObject();
	obj->TextureVecs[slot] = texture.ID;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}
void LuaObject::RemoveTexture(int textureSlot)
{
	auto obj = this->GetObject();
	obj->TextureVecs.erase(textureSlot);

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}

void LuaObject::SetLocation(LuaMath::Vector4 vec)
{
	auto obj = this->GetObject();
	obj->Location = vec;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}
LuaMath::Vector4 LuaObject::GetLocation()
{
	return this->GetObject()->Location;
}

void LuaObject::SetScale(LuaMath::Vector4 vec)
{
	auto obj = this->GetObject();
	obj->Scale = vec;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}
LuaMath::Vector4 LuaObject::GetScale()
{
	return this->GetObject()->Scale;
}

void LuaObject::SetRotation(LuaMath::Vector4 vec)
{
	auto obj = this->GetObject();
	obj->Rotation = vec;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}
LuaMath::Vector4 LuaObject::GetRotation()
{
	return this->GetObject()->Rotation;
}

void LuaObject::SetDiffuse(LuaMath::Vector4 vec)
{
	auto obj = this->GetObject();
	obj->Diffuse = vec;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}
LuaMath::Vector4 LuaObject::GetDiffuse()
{
	return this->GetObject()->Diffuse;
}

void LuaObject::SetAmibent(LuaMath::Vector4 vec)
{
	auto obj = this->GetObject();
	obj->Ambient = vec;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}
LuaMath::Vector4 LuaObject::GetAmibent()
{
	return this->GetObject()->Ambient;
}

void LuaObject::SetSpecular(LuaMath::Vector4 vec)
{
	auto obj = this->GetObject();
	obj->Specular = vec;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}
LuaMath::Vector4 LuaObject::GetSpecular()
{
	return this->GetObject()->Specular;
}

std::shared_ptr<ObjectINFO> LuaObject::GetObject()
{
	std::shared_ptr<ObjectINFO> returnValue;

	auto obj = GetObjectINFO::GetObject(this->ID);
	if(obj)
	{
		returnValue = std::dynamic_pointer_cast<ObjectINFO>(obj);
		if(!returnValue){ throw std::exception("Attempted to cast an Object to ObjectINFO and failed"); }
	}
	return returnValue;
}

void LuaObject::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::class_<LuaObject>("Object")
			.def(luabind::constructor<>())
			.def(luabind::constructor<luabind::object const&>())
			.def_readonly("ID", &LuaObject::ID)
			.def("SetGraphic", &LuaObject::SetGraphic)
			.def("RemoveGraphic", &LuaObject::RemoveGraphic)
			.def("SetTexture", &LuaObject::SetTexture)
			.def("SetTextureAndSlot", &LuaObject::SetTextureAndSlot)
			.def("RemoveTexture", &LuaObject::RemoveTexture)
			.property("Location", &LuaObject::GetLocation, &LuaObject::SetLocation)
			.property("Scale", &LuaObject::GetScale, &LuaObject::SetScale)
			.property("Rotation", &LuaObject::GetRotation, &LuaObject::SetRotation)
			.property("Diffuse", &LuaObject::GetDiffuse, &LuaObject::SetDiffuse)
			.property("Amibent", &LuaObject::GetAmibent, &LuaObject::SetAmibent)
			.property("Specular", &LuaObject::GetSpecular, &LuaObject::SetSpecular)
	  ];
}