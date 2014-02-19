#include "LuaObject.h"

#include <luabind\luabind.hpp>
#include <string>
#include <Converter.h>
#include <Keys.h>
#include <EntityCommunicator\EntityConfig.h>
#include <ObjectINFO.h>
#include "LuaManager.h"
#include "LuaAnimationObject.h"

LuaObject::LuaObject()
{
	CML::Vec4 loc{0.0, 0.0, 0.0, 1.0};
	CML::Vec4 rot{0.0, 0.0, 0.0, 1.0};
	CML::Vec4 sca{1.0, 1.0, 1.0, 1.0};
	CML::Vec4 col{1.0, 1.0, 1.0, 1.0};

	std::shared_ptr<ObjectINFO> obj(new ObjectINFO());
	obj->SetLocation(loc);
	obj->SetRotation(rot);
	obj->SetScale(sca);
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
		Logger::LogError("Wrong paramter for Camera, please send in a table");

	CML::Vec4 loc{0.0, 0.0, 0.0, 1.0};
	CML::Vec4 rot{0.0, 0.0, 0.0, 1.0};
	CML::Vec4 sca{1.0, 1.0, 1.0, 1.0};
	CML::Vec4 diffuse{1.0, 1.0, 1.0, 1.0};
	CML::Vec4 amibent{1.0, 1.0, 1.0, 1.0};
	CML::Vec4 specular{1.0, 1.0, 1.0, 1.0};
	std::string graphicDrawable;
	std::vector<std::string>  textures2D;
	std::vector<std::string>  texturesCube;
	bool light = true;
	bool shadow = true;
	bool depth = true;
	std::array<float, ObjectINFO::USERDATASIZE> userData;
	std::fill(userData.begin(), userData.end(), 0.0f);
	ObjectINFO::sAnimationJoint animJoint;
	std::string rigidBodyID;

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
		else if(key == Keys::ObjectInfo::DRAWABLEOBJ)	{ graphicDrawable = luabind::object_cast<LuaBasicDrawableObject::BasicDrawableObject>(*it).ID; }
		else if(key == Keys::ObjectInfo::TEXTURE2DOBJ)	{ textures2D.push_back(luabind::object_cast<LuaBasicTexture>(*it).ID); }
		else if(key == Keys::ObjectInfo::TEXTURECUBEOBJ){ texturesCube.push_back(luabind::object_cast<LuaBasicTexture>(*it).ID); }
		else if(key == Keys::ObjectInfo::LIGHT)			{ light = luabind::object_cast<bool>(*it); }
		else if(key == Keys::ObjectInfo::SHADOW)		{ shadow = luabind::object_cast<bool>(*it); }
		else if(key == Keys::ObjectInfo::DEPTH)			{ depth = luabind::object_cast<bool>(*it); }
		else if(key == Keys::ObjectInfo::RIGIDBODY)		{ rigidBodyID = luabind::object_cast<LuaRigidBody::RididBody>(*it).ID; }
		else if(key == Keys::ObjectInfo::OBJUSERDATA)
		{
			if(luabind::type(*it) != LUA_TTABLE)
				Logger::LogError("Wrong paramter for ObjectInfo::SetGlobalUserData, please send in a table");
			unsigned int iCounter = 0;
			for(luabind::iterator userDataIt(*it);
				userDataIt != luabind::iterator() && iCounter < ObjectINFO::USERDATASIZE;
				++userDataIt, ++iCounter)
			{
				userData[iCounter] = luabind::object_cast<float>(*userDataIt);
			}
		}
		else if(key == Keys::ObjectInfo::ANIMATIONJOINT)
		{
			if(luabind::type(*it) != LUA_TTABLE)
				Logger::LogError("Wrong paramter for ObjectInfo::AnimationJoint, please send in a table");
			luabind::iterator it(*it);
			animJoint.AnimationID = luabind::object_cast<LuaAnimationObject::AnimationController>(*it).ID;
			++it;
			animJoint.JointName = luabind::object_cast<std::string>(*it);
		}
	}

	std::shared_ptr<ObjectINFO> obj(new ObjectINFO());
	obj->SetLocation(loc);
	obj->SetRotation(rot);
	obj->SetScale(sca);
	obj->Diffuse = diffuse;
	obj->Ambient = amibent;
	obj->Specular = specular;
	obj->DrawObjID = graphicDrawable;
	obj->Texture2DVecs = textures2D;
	obj->TextureCubeVecs = texturesCube;
	obj->Light = light;
	obj->Shadow = shadow;
	obj->Depth = depth;
	obj->UserData = userData;
	obj->AnimationJoint = animJoint;
	obj->PhysicsRigidBodyID = rigidBodyID;
	EntityConfig::SetEntity(obj);
	this->ID = obj->ID;
}

void LuaObject::SetGraphic(LuaBasicDrawableObject::BasicDrawableObject graphic)
{
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::DRAWABLEOBJ, GenericObj<std::string>::CreateNew(graphic.ID));
}
void LuaObject::RemoveGraphic()
{
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::DRAWABLEOBJ, GenericObj<std::string>::CreateNew(""));
}

std::shared_ptr<GenericObj<std::vector<std::string>>> LuaObject::GetRawAll2DTextures()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::ObjectInfo::TEXTURE2DOBJ);
	return GenericObj<std::vector<std::string>>::Cast(obj);
}
void LuaObject::Add2DTexture(LuaBasicTexture texture)
{
	std::shared_ptr<GenericObj<std::vector<std::string>>> textures = this->GetRawAll2DTextures();
	textures->GetValue().push_back(texture.ID);
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::TEXTURE2DOBJ, textures);
}
void LuaObject::Remove2DTexture(LuaBasicTexture texture)
{
	std::shared_ptr<GenericObj<std::vector<std::string>>> textures = this->GetRawAll2DTextures();
	auto iter = std::find(textures->GetValue().begin(), textures->GetValue().end(), texture.ID);
	if(iter != textures->GetValue().end())
	{
		textures->GetValue().erase(iter);
	}
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::TEXTURE2DOBJ, textures);
}
void LuaObject::Set2DTexture(const luabind::object& textures)
{
	std::vector<std::string> textureIDs;
	if(luabind::type(textures) != LUA_TTABLE)
		Logger::LogError("Wrong paramter for Object::Set2DTexture, please send in a table");
	for(luabind::iterator it(textures);
		it != luabind::iterator();
		++it)
	{
		std::string texID = luabind::object_cast<LuaBasicTexture>(*it).ID;
		textureIDs.push_back(texID);
	}
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::TEXTURE2DOBJ, GenericObj<std::vector<std::string>>::CreateNew(textureIDs));
}
luabind::object LuaObject::All2DTexture()
{
	std::shared_ptr<GenericObj<std::vector<std::string>>> textures = this->GetRawAll2DTextures();

	luabind::object luaTextureVec = luabind::newtable(LuaManager::GetInstance().lua);
	int keyCounter = 1;
	for(auto iter = textures->GetValue().begin();
		iter != textures->GetValue().end();
		++iter, ++keyCounter)
	{
		LuaBasicTexture texture;
		texture.ID = (*iter);
		luaTextureVec[keyCounter] = texture;
	}
	return luaTextureVec;
}

std::shared_ptr<GenericObj<std::vector<std::string>>> LuaObject::GetRawAllCubeTextures()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::ObjectInfo::TEXTURECUBEOBJ);
	return GenericObj<std::vector<std::string>>::Cast(obj);
}
void LuaObject::AddCubeTexture(LuaBasicTexture texture)
{
	std::shared_ptr<GenericObj<std::vector<std::string>>> textures = this->GetRawAllCubeTextures();
	textures->GetValue().push_back(texture.ID);
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::TEXTURECUBEOBJ, textures);
}
void LuaObject::RemoveCubeTexture(LuaBasicTexture texture)
{
	std::shared_ptr<GenericObj<std::vector<std::string>>> textures = this->GetRawAllCubeTextures();
	auto iter = std::find(textures->GetValue().begin(), textures->GetValue().end(), texture.ID);
	if(iter != textures->GetValue().end())
	{
		textures->GetValue().erase(iter);
	}
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::TEXTURECUBEOBJ, textures);
}
void LuaObject::SetCubeTexture(const luabind::object& textures)
{
	std::vector<std::string> textureIDs;
	if(luabind::type(textures) != LUA_TTABLE)
		Logger::LogError("Wrong paramter for Object::SetCubeTexture, please send in a table");
	for(luabind::iterator it(textures);
		it != luabind::iterator();
		++it)
	{
		std::string texID = luabind::object_cast<LuaBasicTexture>(*it).ID;
		textureIDs.push_back(texID);
	}
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::TEXTURECUBEOBJ, GenericObj<std::vector<std::string>>::CreateNew(textureIDs));
}
luabind::object LuaObject::AllCubeTexture()
{
	std::shared_ptr<GenericObj<std::vector<std::string>>> textures = this->GetRawAllCubeTextures();

	luabind::object luaTextureVec = luabind::newtable(LuaManager::GetInstance().lua);
	int keyCounter = 1;
	for(auto iter = textures->GetValue().begin();
		iter != textures->GetValue().end();
		++iter, ++keyCounter)
	{
		LuaBasicTexture texture;
		texture.ID = (*iter);
		luaTextureVec[keyCounter] = texture;
	}
	return luaTextureVec;
}

void LuaObject::SetLocation(LuaMath::Vector4 vec)
{
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::LOCATION, GenericObj<CML::Vec4>::CreateNew(vec));
}
LuaMath::Vector4 LuaObject::GetLocation()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::ObjectInfo::LOCATION);
	return GenericObj<CML::Vec4>::GetValue(obj);
}

void LuaObject::SetScale(LuaMath::Vector4 vec)
{
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::SCALE , GenericObj<CML::Vec4>::CreateNew(vec));
}
LuaMath::Vector4 LuaObject::GetScale()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::ObjectInfo::SCALE);
	return GenericObj<CML::Vec4>::GetValue(obj);
}

void LuaObject::SetRotation(LuaMath::Vector4 vec)
{
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::ROTATION, GenericObj<CML::Vec4>::CreateNew(vec));
}
LuaMath::Vector4 LuaObject::GetRotation()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::ObjectInfo::ROTATION);
	return GenericObj<CML::Vec4>::GetValue(obj);
}

void LuaObject::SetDiffuse(LuaMath::Vector4 vec)
{
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::DIFFUSE, GenericObj<CML::Vec4>::CreateNew(vec));
}
LuaMath::Vector4 LuaObject::GetDiffuse()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::ObjectInfo::DIFFUSE);
	return GenericObj<CML::Vec4>::GetValue(obj);
}

void LuaObject::SetAmibent(LuaMath::Vector4 vec)
{
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::AMBIENT, GenericObj<CML::Vec4>::CreateNew(vec));
}
LuaMath::Vector4 LuaObject::GetAmibent()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::ObjectInfo::AMBIENT);
	return GenericObj<CML::Vec4>::GetValue(obj);
}

void LuaObject::SetSpecular(LuaMath::Vector4 vec)
{
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::SPECULAR, GenericObj<CML::Vec4>::CreateNew(vec));
}
LuaMath::Vector4 LuaObject::GetSpecular()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::ObjectInfo::SPECULAR);
	return GenericObj<CML::Vec4>::GetValue(obj);
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

void LuaObject::SetUserData(const luabind::object& textures)
{
	std::array<float, ObjectINFO::USERDATASIZE> userData;
	if(luabind::type(textures) != LUA_TTABLE)
		Logger::LogError("Wrong paramter for Camera::SetGlobalUserData, please send in a table");
	unsigned int iCounter = 0;
	for(luabind::iterator it(textures);
		it != luabind::iterator() && iCounter < ObjectINFO::USERDATASIZE;
		++it, ++iCounter)
	{
		userData[iCounter] = luabind::object_cast<float>(*it);
	}
	EntityConfig::SetEntity(this->ID, Keys::ObjectInfo::OBJUSERDATA, GenericObj<std::array<float, ObjectINFO::USERDATASIZE>>::CreateNew(userData));
}
luabind::object LuaObject::GetUserData()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::ObjectInfo::OBJUSERDATA);
	std::array<float, ObjectINFO::USERDATASIZE> userData = GenericObj<std::array<float, ObjectINFO::USERDATASIZE>>::GetValue(obj);

	luabind::object luaUserDataTable = luabind::newtable(LuaManager::GetInstance().lua);
	for(unsigned int i = 0; i < ObjectINFO::USERDATASIZE; ++i)
	{
		luaUserDataTable[i + 1] = userData[i];
	}
	return luaUserDataTable;
}

void LuaObject::Release()
{
	EntityConfig::DeleteEntity(this->ID);
	this->ID = "";
}

std::shared_ptr<ObjectINFO> LuaObject::GetObject()
{
	std::shared_ptr<ObjectINFO> returnValue;

	auto obj = EntityConfig::GetEntity(this->ID);
	if(obj)
	{
		returnValue = std::dynamic_pointer_cast<ObjectINFO>(obj);
		if(!returnValue){ Logger::LogError("Attempted to cast an Object to ObjectINFO and failed"); }
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
			.property("Texture2D", &LuaObject::All2DTexture, &LuaObject::Set2DTexture)
			.def("Add2DTexture", &LuaObject::Add2DTexture)
			.def("Remove2DTexture", &LuaObject::Remove2DTexture)
			.property("CubeTexture", &LuaObject::AllCubeTexture, &LuaObject::SetCubeTexture)
			.def("AddCubeTexture", &LuaObject::AddCubeTexture)
			.def("RemoveCubeTexture", &LuaObject::RemoveCubeTexture)
			.def("Release", &LuaObject::Release)
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
