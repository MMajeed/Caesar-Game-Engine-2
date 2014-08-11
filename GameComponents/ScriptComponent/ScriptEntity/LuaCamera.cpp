#include "LuaCamera.h"

#include <Logger.h>
#include <ByteCopy.h>
#include <Converter.h>
#include <Keys.h>
#include <ObjectEntity.h>
#include <EntityList.h>
#include <ScriptManager.h>

LuaCamera::LuaCamera()
{
	std::shared_ptr<CameraEntity> obj = CameraEntity::Spawn();
	CameraEntities::Add(obj);
	this->wp_Obj = obj;
	this->ID = obj->GetID();
}
LuaCamera::LuaCamera(const luabind::object& table)
{
	if(luabind::type(table) != LUA_TTABLE)
		Logger::LogError("Wrong paramter type");

	std::shared_ptr<CameraEntity> obj = CameraEntity::Spawn();
	CameraEntities::Add(obj);
	this->wp_Obj = obj;
	this->ID = obj->GetID();

	for(luabind::iterator it(table);
		it != luabind::iterator();
		++it)
	{
		std::string key = luabind::object_cast<std::string>(it.key());

			 if(key == Keys::Camera::EYE)				{ this->SetEye(*it); }
		else if(key == Keys::Camera::TARGETMAGNITUDE)	{ this->SetTargetMagnitude(*it); }
		else if(key == Keys::Camera::UP)				{ this->SetUp(*it); }
		else if(key == Keys::Camera::ROLL)				{ this->SetRoll(*it); }
		else if(key == Keys::Camera::PITCH)				{ this->SetPitch(*it); }
		else if(key == Keys::Camera::YAW)				{ this->SetYaw(*it); }
		else if(key == Keys::Camera::FOVANGLE)		    { this->SetFovAngleY(*it); }
		else if(key == Keys::Camera::NEARZ)		        { this->SetNearZ(*it); }
		else if(key == Keys::Camera::FARZ)		        { this->SetFarZ(*it); }
		else if(key == Keys::Camera::CLEARCOLOR)		{ this->SetClearColor(*it); }
		else if(key == Keys::Camera::INCLUSIONSTATE)	{ this->SetInclusionState(*it); }
		else if(key == Keys::Camera::INCLUSIONLIST)		{ this->SetInclusionList(*it); }
		else if(key == Keys::Camera::USERDATA)			{ this->SetAllUserData(*it); }
		else if(key == Keys::Camera::TEXTURE)			{ this->SetAllTexture(*it); }
		else if(key == Keys::Camera::VERTEXSHADER)		{ this->SetVertexShaderID(*it); }
		else if(key == Keys::Camera::VERTEXSHADERSTATE)	{ this->SetVertexShaderState(*it); }
		else if(key == Keys::Camera::PIXELSHADER)		{ this->SetPixelShaderID(*it); }
		else if(key == Keys::Camera::PIXELSHADERSTATE)	{ this->SetPixelShaderState(*it); }
	}
}

LuaMath::Vector4 LuaCamera::GetEye()
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
		return obj->GetEye();
	else
		return LuaMath::Vector4();
}
void LuaCamera::SetEye(const luabind::object& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<LuaMath::Vector4> value = luabind::object_cast_nothrow<LuaMath::Vector4>(v))
			obj->SetEye(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}

LuaMath::Vector4 LuaCamera::GetTargetMagnitude()
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
		return obj->GetTargetMagnitude();
	else
		return LuaMath::Vector4();
}
void LuaCamera::SetTargetMagnitude(const luabind::object& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<LuaMath::Vector4> value = luabind::object_cast_nothrow<LuaMath::Vector4>(v))
			obj->SetTargetMagnitude(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}

LuaMath::Vector4 LuaCamera::GetUp()
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
		return obj->GetUp();
	else
		return LuaMath::Vector4();
}
void LuaCamera::SetUp(const luabind::object& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<LuaMath::Vector4> value = luabind::object_cast_nothrow<LuaMath::Vector4>(v))
			obj->SetUp(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}

double LuaCamera::GetRoll()
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
		return obj->GetRoll();
	else
		return 0.0;
}
void LuaCamera::SetRoll(const luabind::object& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<double> value = luabind::object_cast_nothrow<double>(v))
			obj->SetRoll(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}

double LuaCamera::GetPitch()
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
		return obj->GetPitch();
	else
		return 0.0;
}
void LuaCamera::SetPitch(const luabind::object& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<double> value = luabind::object_cast_nothrow<double>(v))
			obj->SetPitch(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}

double LuaCamera::GetYaw()
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
		return obj->GetYaw();
	else
		return 0.0;
}
void LuaCamera::SetYaw(const luabind::object& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<double> value = luabind::object_cast_nothrow<double>(v))
			obj->SetYaw(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}

double LuaCamera::GetFovAngleY()
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
		return obj->GetFovAngleY();
	else
		return 0.0;
}
void LuaCamera::SetFovAngleY(const luabind::object& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<double> value = luabind::object_cast_nothrow<double>(v))
			obj->SetFovAngleY(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}

double LuaCamera::GetNearZ()
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
		return obj->GetNearZ();
	else
		return 0.0;
}
void LuaCamera::SetNearZ(const luabind::object& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<double> value = luabind::object_cast_nothrow<double>(v))
			obj->SetNearZ(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}

double LuaCamera::GetFarZ()
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
		return obj->GetFarZ();
	else
		return 0.0;
}
void LuaCamera::SetFarZ(const luabind::object& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<double> value = luabind::object_cast_nothrow<double>(v))
			obj->SetFarZ(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}

LuaMath::Vector4 LuaCamera::GetClearColor()
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
		return obj->GetClearColor();
	else
		return LuaMath::Vector4();
}
void LuaCamera::SetClearColor(const luabind::object& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<LuaMath::Vector4> value = luabind::object_cast_nothrow<LuaMath::Vector4>(v))
			obj->SetClearColor(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}

int LuaCamera::GetInclusionState()
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
		return static_cast<int>(obj->GetInclusionState());
	else
		return 0;
}
void LuaCamera::SetInclusionState(const luabind::object& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<int> value = luabind::object_cast_nothrow<int>(v))
			obj->SetInclusionState(static_cast<CameraEntity::InclusionType>(*value));
		else
			Logger::LogError("Wrong paramter type");
	}
}

luabind::object LuaCamera::GetInclusionList()
{
	luabind::object luaTextureVec = luabind::newtable(ScriptManager::GetInstance().lua);
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		int keyCounter = 1;
		std::hash_set<std::string> list = obj->GetInclusionList();
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
void LuaCamera::SetInclusionList(const luabind::object& v)
{
	if(luabind::type(v) != LUA_TTABLE){ Logger::LogError("Wrong paramter type"); }

	this->EmptyInclusionList();

	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		for(luabind::iterator it(v);
			it != luabind::iterator();
			++it)
		{
			this->AddInclusionList(*it);
		}
	}
}
void LuaCamera::AddInclusionList(const luabind::object& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<std::string> value = luabind::object_cast_nothrow<std::string>(v))
			obj->AddInclusionList(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}
void LuaCamera::DeleteInclusionList(const luabind::object& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<std::string> value = luabind::object_cast_nothrow<std::string>(v))
			obj->DeleteInclusionList(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}
void LuaCamera::EmptyInclusionList()
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->EmptyInclusionList();
	}
}

luabind::object LuaCamera::GetAllUserData()
{
	luabind::object luaUserData = luabind::newtable(ScriptManager::GetInstance().lua);
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		auto list = obj->GetUserData();
		for(auto iter = list.begin(); iter != list.end(); ++iter)
		{
			luaUserData[iter->first] = this->FindUserData(iter->first);
		}
	}
	return luaUserData;
}
void LuaCamera::SetAllUserData(const luabind::object& v)
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
luabind::object LuaCamera::FindUserData(const std::string& ID)
{
	lua_State* lua = ScriptManager::GetInstance().lua;

	luabind::object returnValue;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
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
void LuaCamera::SetUserData(const std::string& ID, const luabind::object& data)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
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
void LuaCamera::DeleteUserData(const std::string& ID)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->DeleteUserData(ID);
	}
}
void LuaCamera::EmptyUserData()
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->EmptyUserData();
	}
}

luabind::object LuaCamera::GetAllTexture()
{
	luabind::object luaTexture = luabind::newtable(ScriptManager::GetInstance().lua);
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		auto list = obj->GetTexture();
		for(auto iter = list.begin(); iter != list.end(); ++iter)
		{
			luaTexture[iter->first] = this->FindTexture(iter->first);
		}
	}
	return luaTexture;
}
void LuaCamera::SetAllTexture(const luabind::object& v)
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
luabind::object LuaCamera::FindTexture(const std::string& ID)
{
	lua_State* lua = ScriptManager::GetInstance().lua;

	luabind::object returnValue;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		std::string objTexture;
		if(obj->FindTexture(ID, objTexture))
		{
			returnValue = luabind::object(lua, objTexture);
		}
	}
	return returnValue;
}
void LuaCamera::SetTexture(const std::string& ID, const luabind::object& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<GenericLuaObject> value = luabind::object_cast_nothrow<GenericLuaObject>(v))
			obj->SetTexture(ID, value->GetID());
		else
			Logger::LogError("Wrong paramter type");
	}
}
void LuaCamera::DeleteTexture(const std::string& ID)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->DeleteTexture(ID);
	}
}
void LuaCamera::EmptyTexture()
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->EmptyTexture();
	}
}

void LuaCamera::GetVertexShaderID()
{
	lua_State* lua = ScriptManager::GetInstance().lua;

	std::string id;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock()){ id = obj->GetVertexShaderID(); }

	// We don't have access to the class so we create it using lua
	lua_getglobal(lua, "VertexShader");		// The class we want
	lua_getglobal(lua, "GenericLuaObject"); // GenericLuaObject will be the paramter 
	lua_pushstring(lua, id.c_str());        // Paramter to GenericLuaObject
	lua_call(lua, 1, 1);					// Creating GenericLuaObject
	lua_call(lua, 1, 1);					// The return value
}
void LuaCamera::SetVertexShaderID(const luabind::object& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<GenericLuaObject> value = luabind::object_cast_nothrow<GenericLuaObject>(v))
			obj->SetVertexShaderID(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}
void LuaCamera::RemoveVertexShaderID()
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->SetVertexShaderID("");
	}
}

int LuaCamera::GetVertexShaderState()
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
		return static_cast<int>(obj->GetVertexShaderState());
	else
		return 0;
}
void LuaCamera::SetVertexShaderState(const luabind::object& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<int> value = luabind::object_cast_nothrow<int>(v))
			obj->SetVertexShaderState(static_cast<CameraEntity::CAMERA_SHADER_TYPE>(*value));
		else
			Logger::LogError("Wrong paramter type");
	}
}

void LuaCamera::GetPixelShaderID()
{
	lua_State* lua = ScriptManager::GetInstance().lua;

	std::string id;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock()){ id = obj->GetPixelShaderID(); }

	// We don't have access to the class so we create it using lua
	lua_getglobal(lua, "PixelShader");		// The class we want
	lua_getglobal(lua, "GenericLuaObject"); // GenericLuaObject will be the paramter 
	lua_pushstring(lua, id.c_str());        // Paramter to GenericLuaObject
	lua_call(lua, 1, 1);					// Creating GenericLuaObject
	lua_call(lua, 1, 1);					// The return value
}
void LuaCamera::SetPixelShaderID(const luabind::object& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<GenericLuaObject> value = luabind::object_cast_nothrow<GenericLuaObject>(v))
			obj->SetPixelShaderID(*value);
		else
			Logger::LogError("Wrong paramter type");
	}
}
void LuaCamera::RemovePixelShaderID()
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->SetPixelShaderID("");
	}
}

int LuaCamera::GetPixelShaderState()
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
		return static_cast<int>(obj->GetPixelShaderState());
	else
		return 0;
}
void LuaCamera::SetPixelShaderState(const luabind::object& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		if(boost::optional<int> value = luabind::object_cast_nothrow<int>(v))
			obj->SetPixelShaderState(static_cast<CameraEntity::CAMERA_SHADER_TYPE>(*value));
		else
			Logger::LogError("Wrong paramter type");
	}
}

void LuaCamera::Release()
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		ObjectEntities::Remove(obj->GetID());
	}
	this->wp_Obj.reset();
}

void LuaCamera::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::class_<LuaCamera, GenericLuaObject>("Camera")
			.def(luabind::constructor<>())
			.def(luabind::constructor<const luabind::object&>())
			.property("Eye", &LuaCamera::GetEye, &LuaCamera::SetEye)
			.property("TargetMagnitude", &LuaCamera::GetTargetMagnitude, &LuaCamera::SetTargetMagnitude)
			.property("Up", &LuaCamera::GetUp, &LuaCamera::SetUp)
			.property("Roll", &LuaCamera::GetRoll, &LuaCamera::SetRoll)
			.property("Pitch", &LuaCamera::GetPitch, &LuaCamera::SetPitch)
			.property("Yaw", &LuaCamera::GetYaw, &LuaCamera::SetYaw)
			.property("FovAngle", &LuaCamera::GetFovAngleY, &LuaCamera::SetFovAngleY)
			.property("NearZ", &LuaCamera::GetNearZ, &LuaCamera::SetNearZ)
			.property("FarZ", &LuaCamera::GetFarZ, &LuaCamera::SetFarZ)
			.property("ClearColor", &LuaCamera::GetClearColor, &LuaCamera::SetClearColor)
			.property("InclusionState", &LuaCamera::GetInclusionState, &LuaCamera::SetInclusionState)
			.property("InclusionList", &LuaCamera::GetInclusionList, &LuaCamera::SetInclusionList)
			.def("AddInclusionList", &LuaCamera::AddInclusionList)
			.def("DeleteInclusionList", &LuaCamera::DeleteInclusionList)
			.def("EmptyInclusionList", &LuaCamera::EmptyInclusionList)
			.property("UserData", &LuaCamera::GetAllUserData, &LuaCamera::SetAllUserData)
			.def("FindUserData", &LuaCamera::FindUserData)
			.def("SetUserData", &LuaCamera::SetUserData)
			.def("DeleteUserData", &LuaCamera::DeleteUserData)
			.def("EmptyUserData", &LuaCamera::EmptyUserData)
			.property("Texture", &LuaCamera::GetAllTexture, &LuaCamera::SetAllTexture)
			.def("FindTexture", &LuaCamera::FindTexture)
			.def("SetTexture", &LuaCamera::SetTexture)
			.def("DeleteTexture", &LuaCamera::DeleteTexture)
			.def("EmptyTexture", &LuaCamera::EmptyTexture)
			.property("VertexShader", &LuaCamera::GetVertexShaderID, &LuaCamera::SetVertexShaderID)
			.def("RemoveVertexShader", &LuaCamera::RemoveVertexShaderID)
			.property("VertexShaderState", &LuaCamera::GetVertexShaderState, &LuaCamera::SetVertexShaderState)
			.property("PixelShader", &LuaCamera::GetPixelShaderID, &LuaCamera::SetPixelShaderID)
			.def("RemovePixelShader", &LuaCamera::RemovePixelShaderID)
			.property("PixelShaderState", &LuaCamera::GetPixelShaderState, &LuaCamera::SetPixelShaderState)
			.def("Release", &LuaCamera::Release)
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