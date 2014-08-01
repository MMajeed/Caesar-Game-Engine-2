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
}
LuaCamera::LuaCamera(const luabind::object& table)
{
	if(luabind::type(table) != LUA_TTABLE)
		Logger::LogError("Wrong paramter for Camera, please send in a table");

	CML::Vec4 eye{0.0, 0.0, 0.0, 0.0};
	CML::Vec4 targetMagnitude{0.0, 0.0, 1.0, 0.0};
	CML::Vec4 up{0.0, 1.0, 0.0, 0.0};
	double roll = 0.0;	double pitch = 0.0;		double yaw = 0.0;
	double FovAngleY = 0.785398163;
	double nearZ = 0.01;
	double farZ = 5000.0;
	CML::Vec4 clearColor{0.5, 0.5, 0.5, 1.0};
	std::hash_set<std::string> texture2D;
	std::hash_set<std::string> textureCube;
	int inclusionType = 0;
	std::hash_set<std::string> InclusionList;
	std::hash_map<std::string, std::vector<char>> userData;

	for(luabind::iterator it(table);
		it != luabind::iterator();
		++it)
	{
		std::string key = luabind::object_cast<std::string>(it.key());

			 if(key == Keys::Camera::EYE)				{ eye = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if(key == Keys::Camera::TARGETMAGNITUDE)	{ targetMagnitude = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if(key == Keys::Camera::UP)				{ up = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if(key == Keys::Camera::ROLL)				{ roll = luabind::object_cast<double>(*it); }
		else if(key == Keys::Camera::PITCH)				{ pitch = luabind::object_cast<double>(*it); }
		else if(key == Keys::Camera::YAW)				{ yaw = luabind::object_cast<double>(*it); }
		else if(key == Keys::Camera::FOVANGLE)		    { FovAngleY = luabind::object_cast<double>(*it); }
		else if(key == Keys::Camera::NEARZ)		        { nearZ = luabind::object_cast<double>(*it); }
		else if(key == Keys::Camera::FARZ)		        { farZ = luabind::object_cast<double>(*it); }
		else if(key == Keys::Camera::CLEARCOLOR)        { clearColor = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if(key == Keys::Camera::GLOBAL2DTEXTURE)
		{
			if(luabind::type(*it) != LUA_TTABLE)
				Logger::LogError("Wrong paramter for " + Keys::Camera::GLOBAL2DTEXTURE + " , please send in a table");

			for(luabind::iterator txIter(*it); txIter != luabind::iterator(); ++txIter)
			{
				texture2D.insert(luabind::object_cast<GenericLuaObject>(*txIter).GetID());
			}
		}
		else if(key == Keys::Camera::GLOBALCUBETEXTURE)
		{
			if(luabind::type(*it) != LUA_TTABLE)
				Logger::LogError("Wrong paramter for " + Keys::Camera::GLOBALCUBETEXTURE + " , please send in a table");

			for(luabind::iterator txIter(*it); txIter != luabind::iterator(); ++txIter)
			{
				textureCube.insert(luabind::object_cast<GenericLuaObject>(*txIter).GetID());
			}
		}
		else if(key == Keys::ObjectInfo::USERDATA)
		{
			if(luabind::type(*it) != LUA_TTABLE)
				Logger::LogError("Wrong paramter for " + Keys::ObjectInfo::USERDATA + " , please send in a table");

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
		else if(key == Keys::Camera::INCLUSIONSTATE) { inclusionType = luabind::object_cast<int>(*it); }
		else if(key == Keys::Camera::INCLUSIONLIST)
		{
			if(luabind::type(*it) != LUA_TTABLE)
				Logger::LogError("Wrong paramter for Camera::OBJECTLIST, please send in a table");
			for(luabind::iterator it2(*it);
				it2 != luabind::iterator();
				++it2)
			{
				std::string c = luabind::object_cast<std::string>(*it2);
				InclusionList.insert(c);
			}
		}
	}

	std::shared_ptr<CameraEntity> obj = CameraEntity::Spawn();
	CameraEntities::Add(obj);
	this->wp_Obj = obj;

	obj->SetEye(eye);
	obj->SetTargetMagnitude(targetMagnitude);
	obj->SetUp(up);
	obj->SetRoll(roll);		obj->SetPitch(pitch);		obj->SetYaw(yaw);
	obj->SetFovAngleY(FovAngleY);
	obj->SetNearZ(nearZ);
	obj->SetFarZ(farZ);
	obj->SetClearColor(clearColor);
	obj->SetGlobalTexture2D(texture2D);
	obj->SetGlobalTextureCube(textureCube);
	obj->SetInclusionState(static_cast<CameraEntity::InclusionType>(inclusionType));
	obj->SetInclusionList(InclusionList);
	obj->SetUserData(userData);
}

LuaMath::Vector4 LuaCamera::GetEye()
{
	LuaMath::Vector4 returnValue;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = obj->GetEye();
	}
	return returnValue;
}
void LuaCamera::SetEye(const LuaMath::Vector4& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->SetEye(v.vector);
	}
}

LuaMath::Vector4 LuaCamera::GetTargetMagnitude()
{
	LuaMath::Vector4 returnValue;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = obj->GetTargetMagnitude();
	}
	return returnValue;
}
void LuaCamera::SetTargetMagnitude(const LuaMath::Vector4& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->SetTargetMagnitude(v.vector);
	}
}

LuaMath::Vector4 LuaCamera::GetUp()
{
	LuaMath::Vector4 returnValue;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = obj->GetUp();
	}
	return returnValue;
}
void LuaCamera::SetUp(const LuaMath::Vector4& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->SetUp(v.vector);
	}
}

double LuaCamera::GetRoll()
{
	double returnValue = 0.0;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = obj->GetRoll();
	}
	return returnValue;
}
void LuaCamera::SetRoll(double v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->SetRoll(v);
	}
}

double LuaCamera::GetPitch()
{
	double returnValue = 0.0;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = obj->GetPitch();
	}
	return returnValue;
}
void LuaCamera::SetPitch(double v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->SetPitch(v);
	}
}

double LuaCamera::GetYaw()
{
	double returnValue = 0.0;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = obj->GetYaw();
	}
	return returnValue;
}
void LuaCamera::SetYaw(double v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->SetYaw(v);
	}
}

double LuaCamera::GetFovAngle()
{
	double returnValue = 0.0;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = obj->GetFovAngleY();
	}
	return returnValue;
}
void LuaCamera::SetFovAngle(double v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->SetFovAngleY(v);
	}
}

double LuaCamera::GetNearZ()
{
	double returnValue = 0.0;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = obj->GetNearZ();
	}
	return returnValue;
}
void LuaCamera::SetNearZ(double v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->SetNearZ(v);
	}
}

double LuaCamera::GetFarZ()
{
	double returnValue = 0.0;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = obj->GetFarZ();
	}
	return returnValue;
}
void LuaCamera::SetFarZ(double v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->SetFarZ(v);
	}
}

LuaMath::Vector4 LuaCamera::GetClearColor()
{
	LuaMath::Vector4 returnValue;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = obj->GetClearColor();
	}
	return returnValue;
}
void LuaCamera::SetClearColor(const LuaMath::Vector4& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->SetClearColor(v.vector);
	}
}

luabind::object LuaCamera::GetGlobalTexture2D()
{
	luabind::object luaTextureVec = luabind::newtable(ScriptManager::GetInstance().lua);
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		int keyCounter = 1;
		std::hash_set<std::string> list = obj->GetGlobalTexture2D();
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
void LuaCamera::SetGlobalTexture2D(const luabind::object& v)
{
	if(luabind::type(v) != LUA_TTABLE)
		Logger::LogError("Wrong paramter for LuaObject::SetGroupList, please send in a table");
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		std::hash_set<std::string> list;
		for(luabind::iterator it(v);
			it != luabind::iterator();
			++it)
		{
			std::string id = luabind::object_cast<GenericLuaObject>(*it).GetID();
			list.insert(id);
		}
		obj->SetGlobalTexture2D(list);
	}
}
void LuaCamera::AddGlobalTexture2D(const GenericLuaObject& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->AddGlobalTexture2D(GenericLuaObject(v.GetID()));
	}
}
void LuaCamera::DeleteGlobalTexture2D(const GenericLuaObject& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->DeleteGlobalTexture2D(v.GetID());
	}
}
void LuaCamera::EmptyGlobalTexture2D()
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->EmptyGlobalTexture2D();
	}
}

luabind::object LuaCamera::GetGlobalTextureCube()
{
	luabind::object luaTextureVec = luabind::newtable(ScriptManager::GetInstance().lua);
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		int keyCounter = 1;
		std::hash_set<std::string> list = obj->GetGlobalTextureCube();
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
void LuaCamera::SetGlobalTextureCube(const luabind::object& v)
{
	if(luabind::type(v) != LUA_TTABLE)
		Logger::LogError("Wrong paramter for LuaObject::SetGroupList, please send in a table");
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		std::hash_set<std::string> list;
		for(luabind::iterator it(v);
			it != luabind::iterator();
			++it)
		{
			std::string id = luabind::object_cast<GenericLuaObject>(*it).GetID();
			list.insert(id);
		}
		obj->SetGlobalTextureCube(list);
	}
}
void LuaCamera::AddGlobalTextureCube(const GenericLuaObject& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->AddGlobalTextureCube(v.GetID());
	}
}
void LuaCamera::DeleteGlobalTextureCube(const GenericLuaObject& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->DeleteGlobalTextureCube(v.GetID());
	}
}
void LuaCamera::EmptyGlobalTextureCube()
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->EmptyGlobalTextureCube();
	}
}

/*luabind::object LuaCamera::GetUserData()
void LuaCamera::SetUserData(const luabind::object& v)
bool LuaCamera::FindUserData(const std::string& ID, std::vector<char>& v)
void LuaCamera::SetUserData(const std::string& ID, const std::vector<char>& data)
void LuaCamera::DeleteUserData(const std::string& ID)
void LuaCamera::EmptyUserData()*/

int LuaCamera::GetInclusionState()
{
	int returnValue = 0;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = static_cast<int>(obj->GetInclusionState());
	}
	return returnValue;
}
void LuaCamera::SetInclusionState(int v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->SetInclusionState(static_cast<CameraEntity::InclusionType>(v));
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
	if(luabind::type(v) != LUA_TTABLE)
		Logger::LogError("Wrong paramter for LuaObject::SetGroupList, please send in a table");
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		std::hash_set<std::string> list;
		for(luabind::iterator it(v);
			it != luabind::iterator();
			++it)
		{
			std::string id = luabind::object_cast<GenericLuaObject>(*it).GetID();
			list.insert(id);
		}
		obj->SetInclusionList(list);
	}
}
void LuaCamera::AddInclusionList(const GenericLuaObject& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->AddInclusionList(v.GetID());
	}
}
void LuaCamera::DeleteInclusionList(const GenericLuaObject& v)
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->DeleteInclusionList(v.GetID());
	}
}
void LuaCamera::EmptyInclusionList()
{
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		obj->EmptyInclusionList();
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

std::string LuaCamera::GetID() const
{
	std::string returnValue;
	if(std::shared_ptr<CameraEntity> obj = this->wp_Obj.lock())
	{
		returnValue = obj->GetID();
	}
	return returnValue;
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
			.property("FovAngle", &LuaCamera::GetFovAngle, &LuaCamera::SetFovAngle)
			.property("NearZ", &LuaCamera::GetNearZ, &LuaCamera::SetNearZ)
			.property("FarZ", &LuaCamera::GetFarZ, &LuaCamera::SetFarZ)
			.property("ClearColor", &LuaCamera::GetClearColor, &LuaCamera::SetClearColor)
			.property("GlobalTexture2D", &LuaCamera::GetGlobalTexture2D, &LuaCamera::SetGlobalTexture2D)
			.def("AddGlobalTexture2D", &LuaCamera::AddGlobalTexture2D)
			.def("DeleteGlobalTexture2D", &LuaCamera::DeleteGlobalTexture2D)
			.def("EmptyGlobalTexture2D", &LuaCamera::EmptyGlobalTexture2D)
			.property("GlobalTextureCube", &LuaCamera::GetGlobalTextureCube, &LuaCamera::SetGlobalTextureCube)
			.def("AddGlobalTextureCube", &LuaCamera::AddGlobalTextureCube)
			.def("DeleteGlobalTextureCube", &LuaCamera::DeleteGlobalTextureCube)
			.def("EmptyGlobalTextureCube", &LuaCamera::EmptyGlobalTextureCube)
			.property("InclusionState", &LuaCamera::GetInclusionState, &LuaCamera::SetInclusionState)
			.property("InclusionList", &LuaCamera::GetInclusionList, &LuaCamera::SetInclusionList)
			.def("AddInclusionList", &LuaCamera::AddInclusionList)
			.def("DeleteInclusionList", &LuaCamera::DeleteInclusionList)
			.def("EmptyInclusionList", &LuaCamera::EmptyInclusionList)
			.def("Release", &LuaCamera::Release)
	  ];

	luabind::object inclusionType = luabind::newtable(lua);
	inclusionType["Exclude"] = 0;
	inclusionType["Include"] = 1;
	luabind::globals(lua)["InclusionType"] = inclusionType;
}