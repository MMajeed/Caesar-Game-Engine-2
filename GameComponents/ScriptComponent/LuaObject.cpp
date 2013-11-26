#include "LuaObject.h"

#include <luabind\luabind.hpp>
#include <string>
#include <Converter.h>
#include <Keys.h>
#include <EntityCommunicator\EntityConfig.h>
#include <ObjectINFO.h>

LuaObject::LuaObject()
{
	CHL::Vec4 loc{0.0, 0.0, 0.0, 1.0};
	CHL::Vec4 rot{0.0, 0.0, 0.0, 1.0};
	CHL::Vec4 sca{1.0, 1.0, 1.0, 1.0};
	CHL::Vec4 col{1.0, 1.0, 1.0, 1.0};

	std::shared_ptr<ObjectINFO> obj(new ObjectINFO());
	obj->Location = loc;
	obj->Rotation = rot;
	obj->Scale = sca;
	obj->Diffuse = col;
	obj->Ambient = col;
	obj->Specular = col;
	obj->Light = true;
	obj->Shadow = true;
	obj->Depth = true;
	EntityConfig::SetEntity(obj);

	this->ID = obj->ID;
}
LuaObject::LuaObject(luabind::object const& table)
{
	if (luabind::type(table) != LUA_TTABLE)
		throw std::exception("Wrong paramter for Camera, please send in a table");

	CHL::Vec4 loc{0.0, 0.0, 0.0, 1.0};
	CHL::Vec4 rot{0.0, 0.0, 0.0, 1.0};
	CHL::Vec4 sca{1.0, 1.0, 1.0, 1.0};
	CHL::Vec4 diffuse{1.0, 1.0, 1.0, 1.0};
	CHL::Vec4 amibent{1.0, 1.0, 1.0, 1.0};
	CHL::Vec4 specular{1.0, 1.0, 1.0, 1.0};
	std::string graphicDrawable;
	std::vector<std::string>  textures2D;
	std::vector<std::string>  texturesCube;
	bool light = true;
	bool shadow = true;
	bool depth = true;

	for (luabind::iterator it(table);
		it != luabind::iterator();
		++it)
	{
		std::string key = luabind::object_cast<std::string>(it.key());

			 if(key == Keys::ObjectInfo::LOCATION)		{ loc = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if(key == Keys::ObjectInfo::ROTATION)		{ rot = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if(key == Keys::ObjectInfo::SCALE)			{ sca = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if(key == Keys::ObjectInfo::DIFFUSE)		{ diffuse = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if(key == Keys::ObjectInfo::AMBIENT)		{ amibent = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if(key == Keys::ObjectInfo::SPECULAR)		{ specular = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if(key == Keys::ObjectInfo::DRAWABLEOBJ)	{ graphicDrawable = luabind::object_cast<LuaBasicDrawableObject>(*it).ID; }
		else if(key == Keys::ObjectInfo::TEXTURE2DOBJ)	{ textures2D.push_back(luabind::object_cast<LuaBasicTexture>(*it).ID); }
		else if(key == Keys::ObjectInfo::TEXTURECUBEOBJ){ texturesCube.push_back(luabind::object_cast<LuaBasicTexture>(*it).ID); }
		else if(key == Keys::ObjectInfo::LIGHT)			{ light = luabind::object_cast<bool>(*it); }
		else if(key == Keys::ObjectInfo::SHADOW)		{ shadow = luabind::object_cast<bool>(*it); }
		else if(key == Keys::ObjectInfo::DEPTH)			{ depth = luabind::object_cast<bool>(*it); }
	}

	std::shared_ptr<ObjectINFO> obj(new ObjectINFO());
	obj->Location = loc;
	obj->Rotation = rot;
	obj->Scale = sca;
	obj->Diffuse = diffuse;
	obj->Ambient = amibent;
	obj->Specular = specular;
	obj->DrawObjID = graphicDrawable;
	obj->Texture2DVecs = textures2D;
	obj->TextureCubeVecs = texturesCube;
	obj->Light = light;
	obj->Shadow = shadow;
	obj->Depth = depth;
	EntityConfig::SetEntity(obj);
	this->ID = obj->ID;
}

void LuaObject::SetGraphic(LuaBasicDrawableObject graphic)
{
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::DRAWABLEOBJ, GenericObj<std::string>::CreateNew(graphic.ID));
}
void LuaObject::RemoveGraphic()
{
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::DRAWABLEOBJ, GenericObj<std::string>::CreateNew(""));
}

void LuaObject::Set2DTexture(LuaBasicTexture texture)
{
	auto obj = this->GetObject();
	obj->Texture2DVecs.push_back(texture.ID);
	EntityConfig::SetEntity(obj);
}
void LuaObject::Remove2DTexture(LuaBasicTexture texture)
{
	auto obj = this->GetObject();
	auto iter = std::find(obj->Texture2DVecs.begin(), obj->Texture2DVecs.end(), texture.ID);
	if(iter != obj->Texture2DVecs.end())
	{
		obj->Texture2DVecs.erase(iter);
	}
	EntityConfig::SetEntity(obj);
}
void LuaObject::RemoveAll2DTexture()
{
	auto obj = this->GetObject();
	obj->Texture2DVecs.erase(obj->Texture2DVecs.begin(), obj->Texture2DVecs.end());
	EntityConfig::SetEntity(obj);;
}

void LuaObject::SetCubeTexture(LuaBasicTexture texture)
{
	auto obj = this->GetObject();
	obj->TextureCubeVecs.push_back(texture.ID); 
	EntityConfig::SetEntity(obj);
}
void LuaObject::RemoveCubeTexture(LuaBasicTexture texture)
{
	auto obj = this->GetObject();
	auto iter = std::find(obj->TextureCubeVecs.begin(), obj->TextureCubeVecs.end(), texture.ID);
	if(iter != obj->TextureCubeVecs.end())
	{
		obj->TextureCubeVecs.erase(iter);
	}
	EntityConfig::SetEntity(obj);
}
void LuaObject::RemoveAllCubeTexture()
{
	auto obj = this->GetObject();
	obj->Texture2DVecs.erase(obj->Texture2DVecs.begin(), obj->Texture2DVecs.end());
	EntityConfig::SetEntity(obj);
}

void LuaObject::SetLocation(LuaMath::Vector4 vec)
{
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::LOCATION, GenericObj<CHL::Vec4>::CreateNew(vec));
}
LuaMath::Vector4 LuaObject::GetLocation()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::ObjectInfo::LOCATION);
	return GenericObj<CHL::Vec4>::GetValue(obj);
}

void LuaObject::SetScale(LuaMath::Vector4 vec)
{
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::SCALE , GenericObj<CHL::Vec4>::CreateNew(vec));
}
LuaMath::Vector4 LuaObject::GetScale()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::ObjectInfo::SCALE);
	return GenericObj<CHL::Vec4>::GetValue(obj);
}

void LuaObject::SetRotation(LuaMath::Vector4 vec)
{
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::ROTATION, GenericObj<CHL::Vec4>::CreateNew(vec));
}
LuaMath::Vector4 LuaObject::GetRotation()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::ObjectInfo::ROTATION);
	return GenericObj<CHL::Vec4>::GetValue(obj);
}

void LuaObject::SetDiffuse(LuaMath::Vector4 vec)
{
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::DIFFUSE, GenericObj<CHL::Vec4>::CreateNew(vec));
}
LuaMath::Vector4 LuaObject::GetDiffuse()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::ObjectInfo::DIFFUSE);
	return GenericObj<CHL::Vec4>::GetValue(obj);
}

void LuaObject::SetAmibent(LuaMath::Vector4 vec)
{
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::AMBIENT, GenericObj<CHL::Vec4>::CreateNew(vec));
}
LuaMath::Vector4 LuaObject::GetAmibent()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::ObjectInfo::AMBIENT);
	return GenericObj<CHL::Vec4>::GetValue(obj);
}

void LuaObject::SetSpecular(LuaMath::Vector4 vec)
{
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::SPECULAR, GenericObj<CHL::Vec4>::CreateNew(vec));
}
LuaMath::Vector4 LuaObject::GetSpecular()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::ObjectInfo::SPECULAR);
	return GenericObj<CHL::Vec4>::GetValue(obj);
}

void LuaObject::SetLight(bool vec)
{
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::LIGHT, GenericObj<bool>::CreateNew(vec));
}
bool LuaObject::GetLight()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::ObjectInfo::SHADOW);
	return GenericObj<bool>::GetValue(obj);
}

void LuaObject::SetShadow(bool vec)
{
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::LIGHT, GenericObj<bool>::CreateNew(vec));
}
bool LuaObject::GetShadow()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::ObjectInfo::SHADOW);
	return GenericObj<bool>::GetValue(obj);
}

void LuaObject::SetDepth(bool vec)
{
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::DEPTH, GenericObj<bool>::CreateNew(vec));
}
bool LuaObject::GetDepth()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::ObjectInfo::DEPTH);
	return GenericObj<bool>::GetValue(obj);
}


std::shared_ptr<ObjectINFO> LuaObject::GetObject()
{
	std::shared_ptr<ObjectINFO> returnValue;

	auto obj = EntityConfig::GetEntity(this->ID);
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
			.def("Set2DTexture", &LuaObject::Set2DTexture)
			.def("Remove2DTexture", &LuaObject::Remove2DTexture)
			.def("RemoveAll2DTexture", &LuaObject::RemoveAll2DTexture)
			.def("SetCubeTexture", &LuaObject::SetCubeTexture)
			.def("RemoveCubeTexture", &LuaObject::RemoveCubeTexture)
			.def("RemoveAllCubeTexture", &LuaObject::RemoveAllCubeTexture)
			.property("Location", &LuaObject::GetLocation, &LuaObject::SetLocation)
			.property("Scale", &LuaObject::GetScale, &LuaObject::SetScale)
			.property("Rotation", &LuaObject::GetRotation, &LuaObject::SetRotation)
			.property("Diffuse", &LuaObject::GetDiffuse, &LuaObject::SetDiffuse)
			.property("Amibent", &LuaObject::GetAmibent, &LuaObject::SetAmibent)
			.property("Specular", &LuaObject::GetSpecular, &LuaObject::SetSpecular)
			.property("Light", &LuaObject::GetLight, &LuaObject::SetLight)
			.property("Shadow", &LuaObject::GetShadow, &LuaObject::SetShadow)
			.property("Depth", &LuaObject::GetDepth, &LuaObject::SetDepth)
	  ];
}
