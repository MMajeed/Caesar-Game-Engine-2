#include "LuaDrawSettings.h"

#include <Logger.h>
#include <ByteCopy.h>
#include <Converter.h>
#include <Keys.h>
#include <ObjectEntity.h>
#include <EntityList.h>
#include <ScriptManager.h>
#include <Resource.h>

LuaDrawSettings::LuaDrawSettings()
{
	std::shared_ptr<DrawSettingsEntity> obj = DrawSettingsEntity::Spawn();
	DrawSettingsEntities::Add(obj);
	this->wp_Obj = obj;
	this->ID = obj->GetID();
}
LuaDrawSettings::LuaDrawSettings(const luabind::object& table)
{
	if(luabind::type(table) != LUA_TTABLE)
		Logger::LogError("Wrong paramter type");

	std::shared_ptr<DrawSettingsEntity> obj = DrawSettingsEntity::Spawn();
	this->wp_Obj = obj;
	this->ID = obj->GetID();

	for(luabind::iterator it(table);
		it != luabind::iterator();
		++it)
	{
		std::string key = luabind::object_cast<std::string>(it.key());

			 if(key == Keys::DrawSettings::CLEARSCREEN)		{ this->SetClearScreen(*it); }
		else if(key == Keys::DrawSettings::CLEARCOLOR)		{ this->SetClearColor(*it); }
		else if(key == Keys::DrawSettings::INCLUSIONSTATE)	{ this->SetInclusionState(*it); }
		else if(key == Keys::DrawSettings::INCLUSIONLIST)	{ this->SetInclusionList(*it); }
		else if(key == Keys::DrawSettings::USERDATA)		{ this->SetAllUserData(*it); }
		else if(key == Keys::DrawSettings::TEXTURE)			{ this->SetAllTexture(*it); }
		else if(key == Keys::DrawSettings::VERTEXSHADER)	{ this->SetVertexShaderID(*it); }
		else if(key == Keys::DrawSettings::VERTEXSHADERSTATE){ this->SetVertexShaderState(*it); }
		else if(key == Keys::DrawSettings::PIXELSHADER)		{ this->SetPixelShaderID(*it); }
		else if(key == Keys::DrawSettings::PIXELSHADERSTATE){ this->SetPixelShaderState(*it); }
	}

	DrawSettingsEntities::Add(obj);
}

bool LuaDrawSettings::GetClearScreen()
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
		return obj->GetClearScreen();
	else
		return bool();
}
void LuaDrawSettings::SetClearScreen(const luabind::object& v)
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<bool> value = luabind::object_cast_nothrow<bool>(v))
			obj->SetClearScreen(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}

LuaMath::Vector4 LuaDrawSettings::GetClearColor()
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
		return obj->GetClearColor();
	else
		return LuaMath::Vector4();
}
void LuaDrawSettings::SetClearColor(const luabind::object& v)
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<LuaMath::Vector4> value = luabind::object_cast_nothrow<LuaMath::Vector4>(v))
			obj->SetClearColor(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}

int LuaDrawSettings::GetInclusionState()
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
		return static_cast<int>(obj->GetInclusionState());
	else
		return 0;
}
void LuaDrawSettings::SetInclusionState(const luabind::object& v)
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<int> value = luabind::object_cast_nothrow<int>(v))
			obj->SetInclusionState(static_cast<DrawSettingsEntity::InclusionType>(*value));
		else
			Logger::LogError("Wrong paramter type");
	}
}

luabind::object LuaDrawSettings::GetInclusionList()
{
	luabind::object luaTextureVec = luabind::newtable(Resource::lua);
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		int keyCounter = 1;
		std::set<std::string> list = obj->GetInclusionList();
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
void LuaDrawSettings::SetInclusionList(const luabind::object& v)
{
	if(luabind::type(v) != LUA_TTABLE){ Logger::LogError("Wrong paramter type"); }

	this->EmptyInclusionList();

	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		for(luabind::iterator it(v);
			it != luabind::iterator();
			++it)
		{
			this->AddInclusionList(*it);
		}
	}
}
void LuaDrawSettings::AddInclusionList(const luabind::object& v)
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<std::string> value = luabind::object_cast_nothrow<std::string>(v))
			obj->AddInclusionList(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}
void LuaDrawSettings::DeleteInclusionList(const luabind::object& v)
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<std::string> value = luabind::object_cast_nothrow<std::string>(v))
			obj->DeleteInclusionList(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}
void LuaDrawSettings::EmptyInclusionList()
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		obj->EmptyInclusionList();
	}
}

luabind::object LuaDrawSettings::GetAllUserData()
{
	luabind::object luaUserData = luabind::newtable(Resource::lua);
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		auto list = obj->GetUserData();
		for(auto iter = list.begin(); iter != list.end(); ++iter)
		{
			luaUserData[iter->first] = this->FindUserData(iter->first);
		}
	}
	return luaUserData;
}
void LuaDrawSettings::SetAllUserData(const luabind::object& v)
{
	if(luabind::type(v) != LUA_TTABLE){ Logger::LogError("Wrong paramter type"); }

	this->EmptyUserData();

	std::unordered_map<std::string, std::shared_ptr<Object>> userData;
	for(luabind::iterator it(v); it != luabind::iterator(); ++it)
	{
		std::string userDataKey = luabind::object_cast<std::string>(it.key());

		this->SetUserData(userDataKey, *it);
	}

}
luabind::object LuaDrawSettings::FindUserData(const std::string& ID)
{
	lua_State* lua = Resource::lua;

	luabind::object returnValue;
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
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
void LuaDrawSettings::SetUserData(const std::string& ID, const luabind::object& data)
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
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
void LuaDrawSettings::DeleteUserData(const std::string& ID)
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		obj->DeleteUserData(ID);
	}
}
void LuaDrawSettings::EmptyUserData()
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		obj->EmptyUserData();
	}
}

luabind::object LuaDrawSettings::GetAllTexture()
{
	luabind::object luaTexture = luabind::newtable(Resource::lua);
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		auto list = obj->GetTexture();
		for(auto iter = list.begin(); iter != list.end(); ++iter)
		{
			luaTexture[iter->first] = this->FindTexture(iter->first);
		}
	}
	return luaTexture;
}
void LuaDrawSettings::SetAllTexture(const luabind::object& v)
{
	if(luabind::type(v) != LUA_TTABLE){ Logger::LogError("Wrong paramter type"); }

	this->EmptyTexture();

	for(luabind::iterator it(v); it != luabind::iterator(); ++it)
	{
		std::string TextureKey = luabind::object_cast<std::string>(it.key());

		this->SetTexture(TextureKey, *it);
	}

}
luabind::object LuaDrawSettings::FindTexture(const std::string& ID)
{
	lua_State* lua = Resource::lua;

	luabind::object returnValue;
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		std::string objTexture;
		if(obj->FindTexture(ID, objTexture))
		{
			returnValue = luabind::object(lua, GenericLuaObject(objTexture));
		}
	}
	return returnValue;
}
void LuaDrawSettings::SetTexture(const std::string& ID, const luabind::object& v)
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<GenericLuaObject> value = luabind::object_cast_nothrow<GenericLuaObject>(v))
			obj->SetTexture(ID, value->GetID());
		else
			Logger::LogError("Wrong paramter type");
	}
}
void LuaDrawSettings::DeleteTexture(const std::string& ID)
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		obj->DeleteTexture(ID);
	}
}
void LuaDrawSettings::EmptyTexture()
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		obj->EmptyTexture();
	}
}

void LuaDrawSettings::GetVertexShaderID()
{
	lua_State* lua = Resource::lua;

	std::string id;
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock()){ id = obj->GetVertexShaderID(); }

	// We don't have access to the class so we create it using lua
	lua_getglobal(lua, "VertexShader");		// The class we want
	lua_getglobal(lua, "GenericLuaObject"); // GenericLuaObject will be the paramter 
	lua_pushstring(lua, id.c_str());        // Paramter to GenericLuaObject
	lua_call(lua, 1, 1);					// Creating GenericLuaObject
	lua_call(lua, 1, 1);					// The return value
}
void LuaDrawSettings::SetVertexShaderID(const luabind::object& v)
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<GenericLuaObject> value = luabind::object_cast_nothrow<GenericLuaObject>(v))
			obj->SetVertexShaderID(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}
void LuaDrawSettings::RemoveVertexShaderID()
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		obj->SetVertexShaderID("");
	}
}

int LuaDrawSettings::GetVertexShaderState()
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
		return static_cast<int>(obj->GetVertexShaderState());
	else
		return 0;
}
void LuaDrawSettings::SetVertexShaderState(const luabind::object& v)
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<int> value = luabind::object_cast_nothrow<int>(v))
			obj->SetVertexShaderState(static_cast<DrawSettingsEntity::DRAWSETTINGS_TYPE>(*value));
		else
			Logger::LogError("Wrong paramter type");
	}
}

void LuaDrawSettings::GetPixelShaderID()
{
	lua_State* lua = Resource::lua;

	std::string id;
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock()){ id = obj->GetPixelShaderID(); }

	// We don't have access to the class so we create it using lua
	lua_getglobal(lua, "PixelShader");		// The class we want
	lua_getglobal(lua, "GenericLuaObject"); // GenericLuaObject will be the paramter 
	lua_pushstring(lua, id.c_str());        // Paramter to GenericLuaObject
	lua_call(lua, 1, 1);					// Creating GenericLuaObject
	lua_call(lua, 1, 1);					// The return value
}
void LuaDrawSettings::SetPixelShaderID(const luabind::object& v)
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<GenericLuaObject> value = luabind::object_cast_nothrow<GenericLuaObject>(v))
			obj->SetPixelShaderID(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}
void LuaDrawSettings::RemovePixelShaderID()
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		obj->SetPixelShaderID("");
	}
}

int LuaDrawSettings::GetPixelShaderState()
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
		return static_cast<int>(obj->GetPixelShaderState());
	else
		return 0;
}
void LuaDrawSettings::SetPixelShaderState(const luabind::object& v)
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<int> value = luabind::object_cast_nothrow<int>(v))
			obj->SetPixelShaderState(static_cast<DrawSettingsEntity::DRAWSETTINGS_TYPE>(*value));
		else
			Logger::LogError("Wrong paramter type");
	}
}

void LuaDrawSettings::Release()
{
	if(std::shared_ptr<DrawSettingsEntity> obj = this->wp_Obj.lock())
	{
		ObjectEntities::Remove(obj->GetID());
	}
	this->wp_Obj.reset();
}

void LuaDrawSettings::Register(lua_State *lua)
{
	luabind::module(lua)[
		luabind::class_<LuaDrawSettings, GenericLuaObject>("DrawSettings")
			.def(luabind::constructor<>())
			.def(luabind::constructor<const luabind::object&>())
			.property("ClearScreen", &LuaDrawSettings::GetClearScreen, &LuaDrawSettings::SetClearScreen)
			.property("ClearColor", &LuaDrawSettings::GetClearColor, &LuaDrawSettings::SetClearColor)
			.property("InclusionState", &LuaDrawSettings::GetInclusionState, &LuaDrawSettings::SetInclusionState)
			.property("InclusionList", &LuaDrawSettings::GetInclusionList, &LuaDrawSettings::SetInclusionList)
			.def("AddInclusionList", &LuaDrawSettings::AddInclusionList)
			.def("DeleteInclusionList", &LuaDrawSettings::DeleteInclusionList)
			.def("EmptyInclusionList", &LuaDrawSettings::EmptyInclusionList)
			.property("UserData", &LuaDrawSettings::GetAllUserData, &LuaDrawSettings::SetAllUserData)
			.def("FindUserData", &LuaDrawSettings::FindUserData)
			.def("SetUserData", &LuaDrawSettings::SetUserData)
			.def("DeleteUserData", &LuaDrawSettings::DeleteUserData)
			.def("EmptyUserData", &LuaDrawSettings::EmptyUserData)
			.property("Texture", &LuaDrawSettings::GetAllTexture, &LuaDrawSettings::SetAllTexture)
			.def("FindTexture", &LuaDrawSettings::FindTexture)
			.def("SetTexture", &LuaDrawSettings::SetTexture)
			.def("DeleteTexture", &LuaDrawSettings::DeleteTexture)
			.def("EmptyTexture", &LuaDrawSettings::EmptyTexture)
			.property("VertexShader", &LuaDrawSettings::GetVertexShaderID, &LuaDrawSettings::SetVertexShaderID)
			.def("RemoveVertexShader", &LuaDrawSettings::RemoveVertexShaderID)
			.property("VertexShaderState", &LuaDrawSettings::GetVertexShaderState, &LuaDrawSettings::SetVertexShaderState)
			.property("PixelShader", &LuaDrawSettings::GetPixelShaderID, &LuaDrawSettings::SetPixelShaderID)
			.def("RemovePixelShader", &LuaDrawSettings::RemovePixelShaderID)
			.property("PixelShaderState", &LuaDrawSettings::GetPixelShaderState, &LuaDrawSettings::SetPixelShaderState)
			.def("Release", &LuaDrawSettings::Release)
	];

	luabind::object inclusionType = luabind::newtable(lua);
	inclusionType["Exclude"] = 0;
	inclusionType["Include"] = 1;
	luabind::globals(lua)["InclusionType"] = inclusionType;

	luabind::object shaderType = luabind::newtable(lua);
	shaderType["Default"] = 0;
	shaderType["Force"] = 1;
	luabind::globals(lua)["ShaderType"] = shaderType;
}