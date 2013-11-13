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

	mapKeys[Keys::Class] = GenericObj<std::string>::CreateNew(Keys::ClassType::Object);

	mapKeys[Keys::BasicDrawable::DRAWABLEOBJ] = GenericObj<std::string>::CreateNew("");

	CHL::Vec4 loc;	loc(0) = 0;	loc(1) = 0;	loc(2) = 0;	loc(3) = 0;	
	mapKeys[Keys::ObjectInfo::LOCATION] = GenericObj<CHL::Vec4>::CreateNew(loc);

	CHL::Vec4 rot;  rot(0) = 0;	rot(1) = 0;	rot(2) = 0;	rot(3) = 0;	
	mapKeys[Keys::ObjectInfo::ROTATION] = GenericObj<CHL::Vec4>::CreateNew(rot);

	CHL::Vec4 sca;  sca(0) = 1.0;	sca(1) = 1.0;	sca(2) = 1.0;	sca(3) = 1.0;	
	mapKeys[Keys::ObjectInfo::SCALE] = GenericObj<CHL::Vec4>::CreateNew(sca);

	CHL::Vec4 col;  col(0) = 1.0;	col(1) = 1.0;	col(2) = 1.0;	col(3) = 1.0;	
	mapKeys[Keys::ObjectInfo::DIFFUSE] = GenericObj<CHL::Vec4>::CreateNew(col);
	mapKeys[Keys::ObjectInfo::AMBIENT] = GenericObj<CHL::Vec4>::CreateNew(col);
	mapKeys[Keys::ObjectInfo::SPECULAR] = GenericObj<CHL::Vec4>::CreateNew(col);

	std::shared_ptr<AddObjectMessage> msg(new AddObjectMessage(mapKeys));

	InfoCommunicator::SubmitMessage(msg);

	this->ID = msg->ID;
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
	std::vector< std::pair<std::string, int> > textures;

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
			textures.push_back(std::make_pair(textureID, textureSlot));
		}
	}

	std::hash_map<std::string, std::shared_ptr<Object>> objectInfo;
	objectInfo[Keys::Class] = GenericObj<std::string>::CreateNew(Keys::ClassType::Object);
	objectInfo[Keys::ObjectInfo::LOCATION] = GenericObj<CHL::Vec4>::CreateNew(loc);
	objectInfo[Keys::ObjectInfo::ROTATION] = GenericObj<CHL::Vec4>::CreateNew(rot);
	objectInfo[Keys::ObjectInfo::SCALE] = GenericObj<CHL::Vec4>::CreateNew(sca);
	objectInfo[Keys::ObjectInfo::DIFFUSE] = GenericObj<CHL::Vec4>::CreateNew(diffuse);
	objectInfo[Keys::ObjectInfo::AMBIENT] = GenericObj<CHL::Vec4>::CreateNew(amibent);
	objectInfo[Keys::ObjectInfo::SPECULAR] = GenericObj<CHL::Vec4>::CreateNew(specular);
	objectInfo[Keys::ObjectInfo::DRAWABLEOBJ] = GenericObj<std::string>::CreateNew(graphicDrawable);
	for (auto iter = textures.begin();
		iter != textures.end();
		++iter)
	{
		std::string textureIDKey = Keys::ObjectInfo::TEXTUREOBJ + iter->first;
		std::string texutureSlotKey = Keys::ObjectInfo::TEXTURESLOT + iter->first;

		objectInfo[textureIDKey] = GenericObj<std::string>::CreateNew(iter->first);
		objectInfo[texutureSlotKey] = GenericObj<int>::CreateNew(iter->second);
	}
	
	std::shared_ptr<AddObjectMessage> msg(new AddObjectMessage(objectInfo));
	InfoCommunicator::SubmitMessage(msg);
	this->ID = msg->ID;
}

void LuaObject::SetGraphic(LuaBasicDrawableObject graphic)
{
	std::shared_ptr<Object> obj = GenericObj<std::string>::CreateNew(graphic.ID);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::BasicDrawable::DRAWABLEOBJ, obj));
	InfoCommunicator::SubmitMessage(msg);
}
void LuaObject::RemoveGraphic()
{
	std::shared_ptr<DeleteInfoMessgae> msg(new DeleteInfoMessgae(this->ID, Keys::BasicDrawable::DRAWABLEOBJ));
	InfoCommunicator::SubmitMessage(msg);
}

void LuaObject::SetTexture(LuaBasicTexture texture)
{
	std::shared_ptr<Object> objTexture = GenericObj<std::string>::CreateNew(texture.ID);
	std::string textureID = Keys::ObjectInfo::TEXTUREOBJ + texture.ID;
	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, textureID, objTexture));
	InfoCommunicator::SubmitMessage(msg1);

	std::shared_ptr<Object> objSlot = GenericObj<int>::CreateNew(0);
	std::string textureSlotID = Keys::ObjectInfo::TEXTURESLOT + texture.ID;
	std::shared_ptr<UpdateObjectMessage> msg2(new UpdateObjectMessage(this->ID, textureSlotID, objSlot));
	InfoCommunicator::SubmitMessage(msg2);
}
void LuaObject::SetTextureAndSlot(LuaBasicTexture texture, int slot)
{
	std::shared_ptr<Object> objTexture = GenericObj<std::string>::CreateNew(texture.ID);
	std::string textureID = Keys::ObjectInfo::TEXTUREOBJ + texture.ID;
	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, textureID, objTexture));
	InfoCommunicator::SubmitMessage(msg1);

	std::shared_ptr<Object> objSlot = GenericObj<int>::CreateNew(slot);
	std::string textureSlotID = Keys::ObjectInfo::TEXTURESLOT + texture.ID;
	std::shared_ptr<UpdateObjectMessage> msg2(new UpdateObjectMessage(this->ID, textureSlotID, objSlot));
	InfoCommunicator::SubmitMessage(msg2);
}
void LuaObject::RemoveTexture(LuaBasicTexture texture)
{
	std::string textureID = Keys::ObjectInfo::TEXTUREOBJ + texture.ID;
	std::shared_ptr<DeleteInfoMessgae> msg1(new DeleteInfoMessgae(this->ID, textureID));
	InfoCommunicator::SubmitMessage(msg1);

	std::string textureSlot = Keys::ObjectInfo::TEXTURESLOT + texture.ID;
	std::shared_ptr<DeleteInfoMessgae> msg(new DeleteInfoMessgae(this->ID, textureSlot));
	InfoCommunicator::SubmitMessage(msg);
}

void LuaObject::SetLocation(LuaMath::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObj<CHL::Vec4>::CreateNew(vec.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::ObjectInfo::LOCATION, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaMath::Vector4 LuaObject::GetLocation()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::ObjectInfo::LOCATION];
	return GenericObj<CHL::Vec4>::GetValue(obj);
}

void LuaObject::SetScale(LuaMath::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObj<CHL::Vec4>::CreateNew(vec.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::ObjectInfo::SCALE, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaMath::Vector4 LuaObject::GetScale()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::ObjectInfo::SCALE];
	return GenericObj<CHL::Vec4>::GetValue(obj);
}

void LuaObject::SetRotation(LuaMath::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObj<CHL::Vec4>::CreateNew(vec.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::ObjectInfo::ROTATION, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaMath::Vector4 LuaObject::GetRotation()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::ObjectInfo::ROTATION];
	return GenericObj<CHL::Vec4>::GetValue(obj);
}

void LuaObject::SetDiffuse(LuaMath::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObj<CHL::Vec4>::CreateNew(vec.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::ObjectInfo::DIFFUSE, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaMath::Vector4 LuaObject::GetDiffuse()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::ObjectInfo::DIFFUSE];
	return GenericObj<CHL::Vec4>::GetValue(obj);
}

void LuaObject::SetAmibent(LuaMath::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObj<CHL::Vec4>::CreateNew(vec.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::ObjectInfo::AMBIENT, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaMath::Vector4 LuaObject::GetAmibent()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::ObjectInfo::AMBIENT];
	return GenericObj<CHL::Vec4>::GetValue(obj);
}

void LuaObject::SetSpecular(LuaMath::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObj<CHL::Vec4>::CreateNew(vec.vector);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::ObjectInfo::SPECULAR, obj));
	InfoCommunicator::SubmitMessage(msg);
}
LuaMath::Vector4 LuaObject::GetSpecular()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::ObjectInfo::SPECULAR];
	return GenericObj<CHL::Vec4>::GetValue(obj);
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