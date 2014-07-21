#include "LuaObject.h"

#include <Logger.h>
#include <ByteCopy.h>
#include <Converter.h>
#include <Keys.h>
#include <ObjectEntity.h>
#include <EntityList.h>
#include <ScriptManager.h>

LuaObject::LuaObject()
{
	std::shared_ptr<ObjectEntity> obj = ObjectEntity::Spawn();
	ObjectEntities::Add(obj);
	this->wp_Obj = obj;
}
LuaObject::LuaObject(const luabind::object& table)
{
	if (luabind::type(table) != LUA_TTABLE)
		Logger::LogError("Wrong paramter for Camera, please send in a table");

	CML::Vec4 loc{0.0, 0.0, 0.0, 1.0};
	CML::Vec4 rot{0.0, 0.0, 0.0, 1.0};
	CML::Vec4 sca{1.0, 1.0, 1.0, 1.0};
	bool depth = true;
	std::string drawObjID;
	std::string animationID;
	std::string jointName;
	std::string rigidBodyID;
	std::hash_set<std::string> groupList;
	std::hash_set<std::string> texture2D;
	std::hash_set<std::string> textureCube;
	std::hash_map<std::string, std::vector<char>> userData;

	for (luabind::iterator it(table);
		it != luabind::iterator();
		++it)
	{
		std::string key = luabind::object_cast<std::string>(it.key());

			 if(key == Keys::ObjectInfo::LOCATION)		{ loc = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if(key == Keys::ObjectInfo::ROTATION)		{ rot = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if(key == Keys::ObjectInfo::SCALE)			{ sca = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if(key == Keys::ObjectInfo::DEPTH)			{ depth = luabind::object_cast<bool>(*it); }
		else if(key == Keys::ObjectInfo::DRAWABLEOBJ)	{ drawObjID = luabind::object_cast<GenericLuaObject>(*it).ID; }
		else if(key == Keys::ObjectInfo::ANIMATIONOBJ)	{ animationID = luabind::object_cast<GenericLuaObject>(*it).ID; }
		else if(key == Keys::ObjectInfo::ANIMATIONJOINT){ jointName = luabind::object_cast<GenericLuaObject>(*it).ID; }
		else if(key == Keys::ObjectInfo::RIGIDBODY)		{ rigidBodyID = luabind::object_cast<GenericLuaObject>(*it).ID; }
		else if(key == Keys::ObjectInfo::TEXTURE2DOBJ)	
		{
			if(luabind::type(*it) != LUA_TTABLE)
				Logger::LogError("Wrong paramter for " + Keys::ObjectInfo::TEXTURE2DOBJ + " , please send in a table");
			
			for(luabind::iterator txIter(*it); txIter != luabind::iterator(); ++txIter)
			{
				texture2D.insert(luabind::object_cast<GenericLuaObject>(*txIter).ID);
			}
		}
		else if(key == Keys::ObjectInfo::GROUP)
		{
			if(luabind::type(*it) != LUA_TTABLE)
				Logger::LogError("Wrong paramter for " + Keys::ObjectInfo::GROUP + " , please send in a table");

			for(luabind::iterator txIter(*it); txIter != luabind::iterator(); ++txIter)
			{
				groupList.insert(luabind::object_cast<GenericLuaObject>(*txIter).ID);
			}
		}
		else if(key == Keys::ObjectInfo::TEXTURECUBEOBJ)
		{
			if(luabind::type(*it) != LUA_TTABLE)
				Logger::LogError("Wrong paramter for " + Keys::ObjectInfo::TEXTURECUBEOBJ + " , please send in a table");

			for(luabind::iterator txIter(*it); txIter != luabind::iterator(); ++txIter)
			{
				textureCube.insert(luabind::object_cast<GenericLuaObject>(*txIter).ID);
			}
		}
		else if(key == Keys::ObjectInfo::USERDATA)
		{
			if(luabind::type(*it) != LUA_TTABLE)
				Logger::LogError("Wrong paramter for " + Keys::ObjectInfo::TEXTURECUBEOBJ + " , please send in a table");

			for(luabind::iterator txIter(*it); txIter != luabind::iterator(); ++txIter)
			{
				std::string userDataKey = luabind::object_cast<std::string>(it.key());

				if(boost::optional<float> optionalValue = luabind::object_cast_nothrow<float>(*txIter))
				{
					std::vector<char> byteValue;
					CHL::ByteCopy(optionalValue.get(), byteValue);
					userData[userDataKey] = byteValue;
				}
			}
		}
	}

	std::shared_ptr<ObjectEntity> obj = ObjectEntity::Spawn(); 
	ObjectEntities::Add(obj);
	this->wp_Obj = obj;

	obj->SetLocation(loc);
	obj->SetRotation(rot);
	obj->SetScale(sca);
	obj->SetDepth(depth);
	obj->SetDrawObjID(drawObjID);
	obj->SetAnimationID(animationID);
	obj->SetJointName(jointName);
	obj->SetRigidBodyID(rigidBodyID);
	obj->SetGroupList(groupList);
	obj->SetTexture2D(texture2D);
	obj->SetTextureCube(textureCube);
	obj->SetUserData(userData);
}

LuaMath::Vector4 LuaObject::GetLocation()
{
	LuaMath::Vector4 returnValue;
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		returnValue = obj->GetLocation();
	}
	return returnValue;
}
void LuaObject::SetLocation(const LuaMath::Vector4& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->SetLocation(v.vector);
	}
}

LuaMath::Vector4 LuaObject::GetRotation()
{
	LuaMath::Vector4 returnValue;
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		returnValue = obj->GetRotation();
	}
	return returnValue;
}
void LuaObject::SetRotation(const LuaMath::Vector4& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->SetRotation(v.vector);
	}
}

LuaMath::Vector4 LuaObject::GetScale()
{
	LuaMath::Vector4 returnValue;
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		returnValue = obj->GetScale();
	}
	return returnValue;
}
void LuaObject::SetScale(const LuaMath::Vector4& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->SetScale(v.vector);
	}
}

bool LuaObject::GetDepth()
{
	bool returnValue = true;
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		returnValue = obj->GetDepth();
	}
	return returnValue;
}
void LuaObject::SetDepth(bool v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->SetDepth(v);
	}
}

GenericLuaObject LuaObject::GetDrawObjID()
{
	std::string returnValue;
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		returnValue = obj->GetDrawObjID();
	}
	return returnValue;
}
void LuaObject::SetDrawObjID(const GenericLuaObject& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->SetDrawObjID(v.ID);
	}
}
void LuaObject::RemoveDrawObjID()
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->SetDrawObjID("");
	}
}

GenericLuaObject LuaObject::GetAnimationID()
{
	std::string returnValue;
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		returnValue = obj->GetAnimationID();
	}
	return returnValue;
}
void LuaObject::SetAnimationID(const GenericLuaObject& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->SetAnimationID(v.ID);
	}
}
void LuaObject::RemoveAnimationID()
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->SetAnimationID("");
	}
}

GenericLuaObject LuaObject::GetJointName()
{
	std::string returnValue;
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		returnValue = obj->GetJointName();
	}
	return returnValue;
}
void LuaObject::SetJointName(const GenericLuaObject& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->SetJointName(v.ID);
	}
}
void LuaObject::RemoveJointName()
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->SetJointName("");
	}
}

GenericLuaObject LuaObject::GetRigidBodyID()
{
	std::string returnValue;
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		returnValue = obj->GetRigidBodyID();
	}
	return returnValue;
}
void LuaObject::SetRigidBodyID(const GenericLuaObject& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->SetRigidBodyID(v.ID);
	}
}
void LuaObject::RemoveRigidBodyID()
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->SetRigidBodyID("");
	}
}

luabind::object LuaObject::GetGroupList()
{
	luabind::object luaTextureVec = luabind::newtable(ScriptManager::GetInstance().lua);
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		int keyCounter = 1;
		std::hash_set<std::string> list = obj->GetGroupList();
		for(auto iter = list.begin();
			iter != list.end();
			++iter, ++keyCounter)
		{
			GenericLuaObject texture(*iter);
			luaTextureVec[keyCounter] = texture;
		}
	}
	return luaTextureVec;
}
void LuaObject::SetGroupList(const luabind::object& v)
{
	if(luabind::type(v) != LUA_TTABLE)
		Logger::LogError("Wrong paramter for LuaObject::SetGroupList, please send in a table");
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		std::hash_set<std::string> list;
		for(luabind::iterator it(v);
			it != luabind::iterator();
			++it)
		{
			std::string id = luabind::object_cast<GenericLuaObject>(*it).ID;
			list.insert(id);
		}
		obj->SetGroupList(list);
	}
}
void LuaObject::AddGroupList(const GenericLuaObject& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->AddGroupList(v.ID);
	}
}
void LuaObject::DeleteGroupList(const GenericLuaObject& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->DeleteGroupList(v.ID);
	}
}
void LuaObject::EmptyGroupList()
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->EmptyGroupList();
	}
}

luabind::object LuaObject::GetTexture2D()
{
	luabind::object luaTextureVec = luabind::newtable(ScriptManager::GetInstance().lua);
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		int keyCounter = 1;
		std::hash_set<std::string> list = obj->GetTexture2D();
		for(auto iter = list.begin();
			iter != list.end();
			++iter, ++keyCounter)
		{
			GenericLuaObject texture(*iter);
			luaTextureVec[keyCounter] = texture;
		}
	}
	return luaTextureVec;
}
void LuaObject::SetTexture2D(const luabind::object& v)
{
	if(luabind::type(v) != LUA_TTABLE)
		Logger::LogError("Wrong paramter for LuaObject::SetGroupList, please send in a table");
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		std::hash_set<std::string> list;
		for(luabind::iterator it(v);
			it != luabind::iterator();
			++it)
		{
			std::string id = luabind::object_cast<GenericLuaObject>(*it).ID;
			list.insert(id);
		}
		obj->SetTexture2D(list);
	}
}
void LuaObject::AddTexture2D(const GenericLuaObject& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->AddTexture2D(v.ID);
	}
}
void LuaObject::DeleteTexture2D(const GenericLuaObject& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->DeleteTexture2D(v.ID);
	}
}
void LuaObject::EmptyTexture2D()
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->EmptyTexture2D();
	}
}

luabind::object LuaObject::GetTextureCube()
{
	luabind::object luaTextureVec = luabind::newtable(ScriptManager::GetInstance().lua);
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		int keyCounter = 1;
		std::hash_set<std::string> list = obj->GetTextureCube();
		for(auto iter = list.begin();
			iter != list.end();
			++iter, ++keyCounter)
		{
			GenericLuaObject texture(*iter);
			luaTextureVec[keyCounter] = texture;
		}
	}
	return luaTextureVec;
}
void LuaObject::SetTextureCube(const luabind::object& v)
{
	if(luabind::type(v) != LUA_TTABLE)
		Logger::LogError("Wrong paramter for LuaObject::SetGroupList, please send in a table");
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		std::hash_set<std::string> list;
		for(luabind::iterator it(v);
			it != luabind::iterator();
			++it)
		{
			std::string id = luabind::object_cast<GenericLuaObject>(*it).ID;
			list.insert(id);
		}
		obj->SetTextureCube(list);
	}
}
void LuaObject::AddTextureCube(const GenericLuaObject& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->AddTextureCube(v.ID);
	}
}
void LuaObject::DeleteTextureCube(const GenericLuaObject& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->DeleteTextureCube(v.ID);
	}
}
void LuaObject::EmptyTextureCube()
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->EmptyTextureCube();
	}
}

//luabind::object LuaObject::GetUserData()
//{
//
//}
//void LuaObject::SetUserData(const luabind::object& v)
//{
//
//}
//bool LuaObject::FindUserData(const std::string& ID, std::vector<char>& v)
//{
//
//}
//void LuaObject::SetUserData(const std::string& ID, const std::vector<char>& data)
//{
//
//}
//void LuaObject::DeleteUserData(const std::string& ID)
//{
//
//}
//void LuaObject::EmptyUserData()
//{
//
//}

void LuaObject::Release()
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		ObjectEntities::Remove(obj->GetID());
	}
	this->wp_Obj.reset();
}

void LuaObject::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::class_<LuaObject>("Object")
			.def(luabind::constructor<>())
			.def(luabind::constructor<const luabind::object&>())
			.property("Location", &LuaObject::GetLocation, &LuaObject::SetLocation)
			.property("Rotation", &LuaObject::GetRotation, &LuaObject::SetRotation)
			.property("Scale", &LuaObject::GetScale, &LuaObject::SetScale)
			.property("Depth", &LuaObject::GetDepth, &LuaObject::SetDepth)
			.property("DrawObj", &LuaObject::GetDrawObjID, &LuaObject::SetDrawObjID)
			.def("RemoveDrawObj", &LuaObject::RemoveDrawObjID)
			.property("Animation", &LuaObject::GetAnimationID, &LuaObject::SetAnimationID)
			.def("RemoveAnimation", &LuaObject::RemoveAnimationID)
			.property("JointName", &LuaObject::GetJointName, &LuaObject::SetJointName)
			.def("RemoveJointName", &LuaObject::RemoveJointName)
			.property("RigidBody", &LuaObject::GetRigidBodyID, &LuaObject::SetRigidBodyID)
			.def("RemoveJointName", &LuaObject::RemoveRigidBodyID)
			.property("GroupList", &LuaObject::GetGroupList, &LuaObject::SetGroupList)
			.def("AddGroupList", &LuaObject::AddGroupList)
			.def("DeleteGroupList", &LuaObject::DeleteGroupList)
			.def("EmptyGroupList", &LuaObject::EmptyGroupList)
			.property("Texture2D", &LuaObject::GetTexture2D, &LuaObject::SetTexture2D)
			.def("AddTexture2D", &LuaObject::AddTexture2D)
			.def("DeleteTexture2D", &LuaObject::DeleteTexture2D)
			.def("EmptyTexture2D", &LuaObject::EmptyTexture2D)
			.property("TextureCube", &LuaObject::GetTextureCube, &LuaObject::SetTextureCube)
			.def("AddTextureCube", &LuaObject::AddTextureCube)
			.def("DeleteTextureCube", &LuaObject::DeleteTextureCube)
			.def("EmptyTextureCube", &LuaObject::EmptyTextureCube)
			.def("Release", &LuaObject::Release)
	  ];

}
