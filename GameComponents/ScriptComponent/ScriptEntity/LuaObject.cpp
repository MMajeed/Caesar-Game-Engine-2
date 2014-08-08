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
	this->ID = obj->GetID();
}
LuaObject::LuaObject(const luabind::object& table)
{
	if (luabind::type(table) != LUA_TTABLE)
		Logger::LogError("Wrong paramter type");

	std::shared_ptr<ObjectEntity> obj = ObjectEntity::Spawn();
	ObjectEntities::Add(obj);
	this->wp_Obj = obj;
	this->ID = obj->GetID();

	for (luabind::iterator it(table);
		it != luabind::iterator();
		++it)
	{
		std::string key = luabind::object_cast<std::string>(it.key());

			 if(key == Keys::ObjectInfo::LOCATION)		{ this->SetLocation(*it); }
		else if(key == Keys::ObjectInfo::ROTATION)		{ this->SetRotation(*it); }
		else if(key == Keys::ObjectInfo::SCALE)			{ this->SetScale(*it); }
		else if(key == Keys::ObjectInfo::DEPTH)			{ this->SetDepth(*it); }
		else if(key == Keys::ObjectInfo::GRAPHICMODEL)	{ this->SetGraphicModelID(*it); }
		else if(key == Keys::ObjectInfo::VERTEXSHADER)	{ this->SetVertexShaderID(*it); }
		else if(key == Keys::ObjectInfo::GEOMETRYSHADER){ this->SetGeometryShaderID(*it); }
		else if(key == Keys::ObjectInfo::PIXELSHADER)	{ this->SetPixelShaderID(*it); }
		else if(key == Keys::ObjectInfo::ANIMATIONOBJ)	{ this->SetAnimationID(*it); }
		else if(key == Keys::ObjectInfo::ANIMATIONJOINT){ this->SetJointName(*it); }
		else if(key == Keys::ObjectInfo::RIGIDBODY)		{ this->SetRigidBodyID(*it); }
		else if(key == Keys::ObjectInfo::GROUP)			{ this->SetGroupList(*it); }
		else if(key == Keys::ObjectInfo::TEXTURE)		{ this->SetAllTexture(*it); }
		else if(key == Keys::ObjectInfo::USERDATA)		{ this->SetAllUserData(*it); }
		else if(key == Keys::ObjectInfo::FILLMODE)		{ this->SetFillMode(*it); }
		else if(key == Keys::ObjectInfo::CULLMODE)		{ this->SetCullMode(*it); }
	}
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
void LuaObject::SetLocation(const luabind::object& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<LuaMath::Vector4> value = luabind::object_cast_nothrow<LuaMath::Vector4>(v))
			obj->SetLocation(*value);
		else
			Logger::LogError("Wrong paramter type");
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
void LuaObject::SetRotation(const luabind::object& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<LuaMath::Vector4> value = luabind::object_cast_nothrow<LuaMath::Vector4>(v))
			obj->SetRotation(*value);
		else
			Logger::LogError("Wrong paramter type");
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
void LuaObject::SetScale(const luabind::object& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<LuaMath::Vector4> value = luabind::object_cast_nothrow<LuaMath::Vector4>(v))
			obj->SetScale(*value);
		else
			Logger::LogError("Wrong paramter type");
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
void LuaObject::SetDepth(const luabind::object& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<bool> value = luabind::object_cast_nothrow<bool>(v))
			obj->SetDepth(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}

void LuaObject::GetGraphicModelID()
{
	lua_State* lua = ScriptManager::GetInstance().lua;

	std::string id;
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock()){ id = obj->GetGraphicModelID(); }
	
	// We don't have access to the class so we create it using lua
	lua_getglobal(lua, "GraphicModel");		// The class we want
	lua_getglobal(lua, "GenericLuaObject"); // GenericLuaObject will be the paramter 
	lua_pushstring(lua, id.c_str());        // Paramter to GenericLuaObject
	lua_call(lua, 1, 1);					// Creating GenericLuaObject
	lua_call(lua, 1, 1);					// The return value
}
void LuaObject::SetGraphicModelID(const luabind::object& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<GenericLuaObject> value = luabind::object_cast_nothrow<GenericLuaObject>(v))
			obj->SetGraphicModelID(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}
void LuaObject::RemoveGraphicModelID()
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->SetGraphicModelID("");
	}
}

void LuaObject::GetVertexShaderID()
{
	lua_State* lua = ScriptManager::GetInstance().lua;

	std::string id;
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock()){ id = obj->GetVertexShaderID(); }

	// We don't have access to the class so we create it using lua
	lua_getglobal(lua, "VertexShader");		// The class we want
	lua_getglobal(lua, "GenericLuaObject"); // GenericLuaObject will be the paramter 
	lua_pushstring(lua, id.c_str());        // Paramter to GenericLuaObject
	lua_call(lua, 1, 1);					// Creating GenericLuaObject
	lua_call(lua, 1, 1);					// The return value
}
void LuaObject::SetVertexShaderID(const luabind::object& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<GenericLuaObject> value = luabind::object_cast_nothrow<GenericLuaObject>(v))
			obj->SetVertexShaderID(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}
void LuaObject::RemoveVertexShaderID()
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->SetVertexShaderID("");
	}
}

void LuaObject::GetGeometryShaderID()
{
	lua_State* lua = ScriptManager::GetInstance().lua;

	std::string id;
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock()){ id = obj->GetGeometryShaderID(); }

	// We don't have access to the class so we create it using lua
	lua_getglobal(lua, "GeometryShader");		// The class we want
	lua_getglobal(lua, "GenericLuaObject"); // GenericLuaObject will be the paramter 
	lua_pushstring(lua, id.c_str());        // Paramter to GenericLuaObject
	lua_call(lua, 1, 1);					// Creating GenericLuaObject
	lua_call(lua, 1, 1);					// The return value
}
void LuaObject::SetGeometryShaderID(const luabind::object& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<GenericLuaObject> value = luabind::object_cast_nothrow<GenericLuaObject>(v))
			obj->SetGeometryShaderID(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}
void LuaObject::RemoveGeometryShaderID()
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->SetGeometryShaderID("");
	}
}

void LuaObject::GetPixelShaderID()
{
	lua_State* lua = ScriptManager::GetInstance().lua;

	std::string id;
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock()){ id = obj->GetPixelShaderID(); }

	// We don't have access to the class so we create it using lua
	lua_getglobal(lua, "PixelShader");		// The class we want
	lua_getglobal(lua, "GenericLuaObject"); // GenericLuaObject will be the paramter 
	lua_pushstring(lua, id.c_str());        // Paramter to GenericLuaObject
	lua_call(lua, 1, 1);					// Creating GenericLuaObject
	lua_call(lua, 1, 1);					// The return value
}
void LuaObject::SetPixelShaderID(const luabind::object& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<GenericLuaObject> value = luabind::object_cast_nothrow<GenericLuaObject>(v))
			obj->SetPixelShaderID(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}
void LuaObject::RemovePixelShaderID()
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->SetPixelShaderID("");
	}
}

void LuaObject::GetAnimationID()
{
	lua_State* lua = ScriptManager::GetInstance().lua;

	std::string id;
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock()){ id = obj->GetAnimationID(); }

	// We don't have access to the class so we create it using lua
	lua_getglobal(lua, "AnimationController");		// The class we want
	lua_getglobal(lua, "GenericLuaObject"); // GenericLuaObject will be the paramter 
	lua_pushstring(lua, id.c_str());        // Paramter to GenericLuaObject
	lua_call(lua, 1, 1);					// Creating GenericLuaObject
	lua_call(lua, 1, 1);					// The return value
}
void LuaObject::SetAnimationID(const luabind::object& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<GenericLuaObject> value = luabind::object_cast_nothrow<GenericLuaObject>(v))
			obj->SetAnimationID(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}
void LuaObject::RemoveAnimationID()
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->SetAnimationID("");
	}
}

std::string LuaObject::GetJointName()
{
	std::string returnValue;
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		returnValue = obj->GetJointName();
	}
	return returnValue;
}
void LuaObject::SetJointName(const luabind::object& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<std::string> value = luabind::object_cast_nothrow<std::string>(v))
			obj->SetJointName(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}
void LuaObject::RemoveJointName()
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->SetJointName("");
	}
}

void LuaObject::GetRigidBodyID()
{
	lua_State* lua = ScriptManager::GetInstance().lua;

	std::string id;
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock()){ id = obj->GetRigidBodyID(); }

	// We don't have access to the class so we create it using lua
	lua_getglobal(lua, "AnimationController");		// The class we want
	lua_getglobal(lua, "GenericLuaObject"); // GenericLuaObject will be the paramter 
	lua_pushstring(lua, id.c_str());        // Paramter to GenericLuaObject
	lua_call(lua, 1, 1);					// Creating GenericLuaObject
	lua_call(lua, 1, 1);					// The return value
}
void LuaObject::SetRigidBodyID(const luabind::object& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<GenericLuaObject> value = luabind::object_cast_nothrow<GenericLuaObject>(v))
			obj->SetRigidBodyID(*value);
		else
			Logger::LogError("Wrong paramter type");
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
	if(luabind::type(v) != LUA_TTABLE){ Logger::LogError("Wrong paramter type"); }

	this->EmptyGroupList();

	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		for(luabind::iterator it(v);
			it != luabind::iterator();
			++it)
		{
			this->AddGroupList(*it);
		}
	}
}
void LuaObject::AddGroupList(const luabind::object& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<std::string> value = luabind::object_cast_nothrow<std::string>(v))
			obj->AddGroupList(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}
void LuaObject::DeleteGroupList(const luabind::object& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<std::string> value = luabind::object_cast_nothrow<std::string>(v))
			obj->DeleteGroupList(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}
void LuaObject::EmptyGroupList()
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->EmptyGroupList();
	}
}

luabind::object LuaObject::GetAllTexture()
{
	luabind::object luaTexture = luabind::newtable(ScriptManager::GetInstance().lua);
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		auto list = obj->GetTexture();
		for(auto iter = list.begin(); iter != list.end(); ++iter)
		{
			luaTexture[iter->first] = this->FindTexture(iter->first);
		}
	}
	return luaTexture;
}
void LuaObject::SetAllTexture(const luabind::object& v)
{
	if(luabind::type(v) != LUA_TTABLE){ Logger::LogError("Wrong paramter type"); }

	this->EmptyTexture();

	std::hash_map<std::string, std::shared_ptr<Object>> Texture;
	for(luabind::iterator it(v); it != luabind::iterator(); ++it)
	{
		std::string TextureKey = luabind::object_cast<std::string>(it.key());

		this->SetTexture(TextureKey, *it);
	}

}
luabind::object LuaObject::FindTexture(const std::string& ID)
{
	lua_State* lua = ScriptManager::GetInstance().lua;

	luabind::object returnValue;
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		std::string objTexture;
		if(obj->FindTexture(ID, objTexture))
		{
			returnValue = luabind::object(lua, objTexture);
		}
	}
	return returnValue;
}
void LuaObject::SetTexture(const std::string& ID, const luabind::object& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<GenericLuaObject> value = luabind::object_cast_nothrow<GenericLuaObject>(v))
			obj->SetTexture(ID, value->GetID());
		else
			Logger::LogError("Wrong paramter type");
	}
}
void LuaObject::DeleteTexture(const std::string& ID)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->DeleteTexture(ID);
	}
}
void LuaObject::EmptyTexture()
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->EmptyTexture();
	}
}

luabind::object LuaObject::GetAllUserData()
{
	luabind::object luaUserData = luabind::newtable(ScriptManager::GetInstance().lua);
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		auto list = obj->GetUserData();
		for(auto iter = list.begin(); iter != list.end(); ++iter)
		{
			luaUserData[iter->first] = this->FindUserData(iter->first);
		}
	}
	return luaUserData;
}
void LuaObject::SetAllUserData(const luabind::object& v)
{
	if(luabind::type(v) != LUA_TTABLE){ Logger::LogError("Wrong paramter type"); }

	this->EmptyUserData();

	std::hash_map<std::string, std::shared_ptr<Object>> userData;
	for(luabind::iterator it(v); it != luabind::iterator(); ++it)
	{
		std::string userDataKey = luabind::object_cast<std::string>(it.key());

		this->SetUserData(userDataKey, *it);
	}

}
luabind::object LuaObject::FindUserData(const std::string& ID)
{
	lua_State* lua = ScriptManager::GetInstance().lua;

	luabind::object returnValue;
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		if(std::shared_ptr<Object> objUserData = obj->FindUserData(ID))
		{
			if(std::shared_ptr<GenericObj<float>> value = GenericObj<float>::Cast(objUserData))
			{
				float tempV = *value;
				returnValue = luabind::object(lua, tempV);
			}
			else if(std::shared_ptr<GenericObj<CML::Vec4>> value = GenericObj<CML::Vec4>::Cast(objUserData))
			{
				LuaMath::Vector4 tempV = *value;
				returnValue = luabind::object(lua, tempV);
			}
			else if(std::shared_ptr<GenericObj<CML::Matrix4x4>> value = GenericObj<CML::Matrix4x4>::Cast(objUserData))
			{
				LuaMath::Matrix4x4 tempV = *value;
				returnValue = luabind::object(lua, tempV);
			}
		}
	}
	return returnValue;
}
void LuaObject::SetUserData(const std::string& ID, const luabind::object& data)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<float> optionalValue = luabind::object_cast_nothrow<float>(data))
		{
			obj->SetUserData(ID, GenericObj<float>::CreateNew(optionalValue.get()));
		}
		else if(boost::optional<LuaMath::Vector4> optionalValue = luabind::object_cast_nothrow<LuaMath::Vector4>(data))
		{
			obj->SetUserData(ID, GenericObj<CML::Vec4>::CreateNew(optionalValue.get()));
		}
		else if(boost::optional<LuaMath::Matrix4x4> optionalValue = luabind::object_cast_nothrow<LuaMath::Matrix4x4>(data))
		{
			obj->SetUserData(ID, GenericObj<CML::Matrix4x4>::CreateNew(optionalValue.get()));
		}
	}
}
void LuaObject::DeleteUserData(const std::string& ID)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->DeleteUserData(ID);
	}
}
void LuaObject::EmptyUserData()
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		obj->EmptyUserData();
	}
}

int LuaObject::GetFillMode()
{
	int returnValue = 3;
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		returnValue = (int)obj->GetFillMode();
	}
	return returnValue;
}
void LuaObject::SetFillMode(const luabind::object& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<int> value = luabind::object_cast_nothrow<int>(v))
			obj->SetFillMode(static_cast<ObjectEntity::FILL_MODE>(*value));
		else
			Logger::LogError("Wrong paramter type");
	}
}

int LuaObject::GetCullMode()
{
	int returnValue = 3;
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		returnValue = (int)obj->GetCullMode();
	}
	return returnValue;
}
void LuaObject::SetCullMode(const luabind::object& v)
{
	if(std::shared_ptr<ObjectEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<int> value = luabind::object_cast_nothrow<int>(v))
			obj->SetCullMode(static_cast<ObjectEntity::CULL_MODE>(*value));
		else
			Logger::LogError("Wrong paramter type");
	}
}

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
		luabind::class_<LuaObject, GenericLuaObject>("Object")
			.def(luabind::constructor<>())
			.def(luabind::constructor<const luabind::object&>())
			.property("Location", &LuaObject::GetLocation, &LuaObject::SetLocation)
			.property("Rotation", &LuaObject::GetRotation, &LuaObject::SetRotation)
			.property("Scale", &LuaObject::GetScale, &LuaObject::SetScale)
			.property("Depth", &LuaObject::GetDepth, &LuaObject::SetDepth)
			.property("GraphicModel", &LuaObject::GetGraphicModelID, &LuaObject::SetGraphicModelID)
			.def("RemoveGraphicModel", &LuaObject::RemoveGraphicModelID)
			.property("VertexShader", &LuaObject::GetVertexShaderID, &LuaObject::SetVertexShaderID)
			.def("RemoveVertexShader", &LuaObject::RemoveVertexShaderID)
			.property("GeometryShader", &LuaObject::GetGeometryShaderID, &LuaObject::SetGeometryShaderID)
			.def("RemoveGeometryShader", &LuaObject::RemoveGeometryShaderID)
			.property("PixelShader", &LuaObject::GetPixelShaderID, &LuaObject::SetPixelShaderID)
			.def("RemovePixelShader", &LuaObject::RemovePixelShaderID)
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
			.property("Texture", &LuaObject::GetAllTexture, &LuaObject::SetAllTexture)
			.def("FindTexture", &LuaObject::FindTexture)
			.def("SetTexture", &LuaObject::SetTexture)
			.def("DeleteTexture", &LuaObject::DeleteTexture)
			.def("EmptyTexture", &LuaObject::EmptyTexture)
			.property("UserData", &LuaObject::GetAllUserData, &LuaObject::SetAllUserData)
			.def("FindUserData", &LuaObject::FindUserData)
			.def("SetUserData", &LuaObject::SetUserData)
			.def("DeleteUserData", &LuaObject::DeleteUserData)
			.def("EmptyUserData", &LuaObject::EmptyUserData)
			.def("Release", &LuaObject::Release)
	  ];

	luabind::object cullMode = luabind::newtable(lua);
	cullMode["None"] = 1;
	cullMode["Front"] = 2;
	cullMode["Back"] = 3;
	luabind::globals(lua)["CullMode"] = cullMode;

	luabind::object fillMode = luabind::newtable(lua);
	fillMode["Wireframe"] = 2;
	fillMode["Solid"] = 3;
	luabind::globals(lua)["FillMode"] = fillMode;
}