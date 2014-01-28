#include "LuaCamera.h"
#include <Converter.h>
#include <luabind\luabind.hpp>
#include <EntityCommunicator\EntityConfig.h>
#include <EntityCommunicator\ImportantIDConfig.h>
#include <Keys.h>
#include "LuaManager.h"

LuaCamera::LuaCamera(luabind::object const& table)
{
	if (luabind::type(table) != LUA_TTABLE)
		Logger::LogError("Wrong paramter for Camera, please send in a table");

	CML::Vec4 eye{0.0, 0.0, 0.0, 0.0};
	CML::Vec4 TM{0.0, 0.0, 1.0, 0.0};
	CML::Vec4 up{0.0, 1.0, 0.0, 0.0};
	double roll = 0.0;	double pitch = 0.0;		double yaw = 0.0;
	double FovAngleY = 0.785398163;
	double nearZ = 0.01;
	double farZ = 5000.0;
	CML::Vec4 ClearColor{0.5, 0.5, 0.5, 1.0};
	bool process2D = true;
	std::vector<std::string> global2DTexture;
	std::vector<std::string> globalCubeTexture;
	std::array<float, CameraINFO::GLOBALUSERDATASIZE> globalUserData;
	std::fill(globalUserData.begin(), globalUserData.end(), 0.0f);
	int inclusionType = 0;
	std::set<std::string> objList;

	for (luabind::iterator it(table);
		it != luabind::iterator();
		++it)
	{
		std::string key = luabind::object_cast<std::string>(it.key());

			 if (key == Keys::Camera::EYE)				{ eye = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Camera::TARGETMAGNITUDE)	{ TM = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Camera::UP)				{ up = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Camera::RADIANROLL)		{ roll = luabind::object_cast<double>(*it); }
		else if (key == Keys::Camera::RADIANPITCH)		{ pitch = luabind::object_cast<double>(*it); }
		else if(key == Keys::Camera::RADIANYAW)		    { yaw = luabind::object_cast<double>(*it); }
		else if(key == Keys::Camera::FOVANGLE)		    { FovAngleY = luabind::object_cast<double>(*it); }
		else if(key == Keys::Camera::NEARZ)		        { nearZ = luabind::object_cast<double>(*it); }
		else if(key == Keys::Camera::FARZ)		        { farZ = luabind::object_cast<double>(*it); }
		else if(key == Keys::Camera::CLEARCOLOR)        { ClearColor = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if(key == Keys::Camera::PROCESS2D)         { process2D = luabind::object_cast<bool>(*it); }
		else if(key == Keys::Camera::GLOBAL2DTEXTURE)   { global2DTexture.push_back(luabind::object_cast<LuaBasicTexture>(*it).ID); }
		else if(key == Keys::Camera::GLOBALCUBETEXTURE) { globalCubeTexture.push_back(luabind::object_cast<LuaBasicTexture>(*it).ID); }
		else if(key == Keys::Camera::GLOBALUSERDATA)   
		{
			if(luabind::type(*it) != LUA_TTABLE)
				Logger::LogError("Wrong paramter for Camera::SetGlobalUserData, please send in a table");
			unsigned int iCounter = 0;
			for(luabind::iterator it2(*it);
				it2 != luabind::iterator() && iCounter < CameraINFO::GLOBALUSERDATASIZE;
				++it2, ++iCounter)
			{
				globalUserData[iCounter] = luabind::object_cast<float>(*it2);
			}
		}
		else if(key == Keys::Camera::INCLUSIONSTATE) { inclusionType = luabind::object_cast<int>(*it); }
		else if(key == Keys::Camera::OBJECTLIST)
		{
			if(luabind::type(*it) != LUA_TTABLE)
				Logger::LogError("Wrong paramter for Camera::OBJECTLIST, please send in a table");
			for(luabind::iterator it2(*it);
				it2 != luabind::iterator();
				++it2)
			{
				std::string objID = luabind::object_cast<LuaObject>(*it2).ID;
				objList.insert(objID);
			}
		}
	}

	std::shared_ptr<CameraINFO> obj(new CameraINFO());
	obj->Eye = eye;
	obj->TargetMagnitude = TM;
	obj->Up = up;
	obj->Roll = roll;
	obj->Pitch = pitch;
	obj->Yaw = yaw;
	obj->FovAngleY = FovAngleY;
	obj->NearZ = nearZ;
	obj->FarZ = farZ;
	obj->ClearColor = ClearColor;
	obj->Process2D = process2D;
	obj->Global2DTexture = global2DTexture;
	obj->GlobalCubeTexture = globalCubeTexture;
	obj->GlobalUserData = globalUserData;
	obj->InclusionState = static_cast<CameraINFO::InclusionType>(inclusionType);
	obj->ObjectList = objList;
	EntityConfig::SetEntity(obj);
	this->ID = obj->ID;
}
void LuaCamera::SetAsMain()
{
	ImportantIDConfig::CameraID::Set(this->ID);
}
		
void LuaCamera::MoveFroward(double distance)
{
	LuaMath::Vector4 eye = this->GetEye();
	LuaMath::Vector4 target = this->GetTargetMagintude();
	double pitch = this->GetPitch();
	double yaw = this->GetYaw();
	double roll = this->GetRoll();

	//auto newEye = CHL::MoveForward(eye, target, pitch, yaw, roll, distance);
	//this->SetEye(newEye);
}

void LuaCamera::SetEye(LuaMath::Vector4 eye)
{
	EntityConfig::SetEntity(this->ID, Keys::Camera::EYE, GenericObj<CML::Vec4>::CreateNew(eye));
}
LuaMath::Vector4 LuaCamera::GetEye()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::EYE);
	return GenericObj<CML::Vec4>::GetValue(obj);
}

void LuaCamera::SetTargetMagintude(LuaMath::Vector4 targetMagintude)
{
	EntityConfig::SetEntity(this->ID, Keys::Camera::TARGETMAGNITUDE, GenericObj<CML::Vec4>::CreateNew(targetMagintude));
}
LuaMath::Vector4 LuaCamera::GetTargetMagintude()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::TARGETMAGNITUDE);
	return GenericObj<CML::Vec4>::GetValue(obj);
}

void LuaCamera::SetUp(LuaMath::Vector4 up)
{
	EntityConfig::SetEntity(this->ID, Keys::Camera::UP, GenericObj<CML::Vec4>::CreateNew(up));
}
LuaMath::Vector4 LuaCamera::GetUp()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::UP);
	return GenericObj<CML::Vec4>::GetValue(obj);
}

void LuaCamera::SetRoll(double roll)
{
	EntityConfig::SetEntity(this->ID, Keys::Camera::RADIANROLL, GenericObj<double>::CreateNew(roll));
}
double LuaCamera::GetRoll()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::RADIANROLL);
	return GenericObj<double>::GetValue(obj);
}

void LuaCamera::SetPitch(double pitch)
{
	EntityConfig::SetEntity(this->ID, Keys::Camera::RADIANPITCH, GenericObj<double>::CreateNew(pitch));
}
double LuaCamera::GetPitch()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::RADIANPITCH);
	return GenericObj<double>::GetValue(obj);
}

void LuaCamera::SetYaw(double val)
{
	EntityConfig::SetEntity(this->ID, Keys::Camera::RADIANYAW, GenericObj<double>::CreateNew(val));
}
double LuaCamera::GetYaw()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::RADIANYAW);
	return GenericObj<double>::GetValue(obj);
}

void LuaCamera::SetFovAngle(double val)
{
	EntityConfig::SetEntity(this->ID, Keys::Camera::FOVANGLE, GenericObj<double>::CreateNew(val));
}
double LuaCamera::GetFovAngle()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::FOVANGLE);
	return GenericObj<double>::GetValue(obj);
}

void LuaCamera::SetNearZ(double val)
{
	EntityConfig::SetEntity(this->ID, Keys::Camera::NEARZ, GenericObj<double>::CreateNew(val));
}
double LuaCamera::GetNearZ()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::NEARZ);
	return GenericObj<double>::GetValue(obj);
}

void LuaCamera::SetFarZ(double val)
{

	EntityConfig::SetEntity(this->ID, Keys::Camera::RADIANYAW, GenericObj<double>::CreateNew(val));
}
double LuaCamera::GetFarZ()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::FARZ);
	return GenericObj<double>::GetValue(obj);
}

void LuaCamera::SetClearColor(LuaMath::Vector4 val)
{

	EntityConfig::SetEntity(this->ID, Keys::Camera::RADIANYAW, GenericObj<CML::Vec4>::CreateNew(val));
}
LuaMath::Vector4 LuaCamera::GetClearColor()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::CLEARCOLOR);
	return GenericObj<CML::Vec4>::GetValue(obj);
}

std::shared_ptr<GenericObj<std::vector<std::string>>> LuaCamera::GetRawAll2DTextures()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::GLOBAL2DTEXTURE);
	return GenericObj<std::vector<std::string>>::Cast(obj);
}
void LuaCamera::Add2dTexture(LuaBasicTexture texture)
{
	std::shared_ptr<GenericObj<std::vector<std::string>>> textures = this->GetRawAll2DTextures();
	textures->GetValue().push_back(texture.ID);
	EntityConfig::SetEntity(this->ID, Keys::Camera::GLOBAL2DTEXTURE, textures);
}
void LuaCamera::Remove2Texture(LuaBasicTexture texture)
{
	std::shared_ptr<GenericObj<std::vector<std::string>>> textures = this->GetRawAll2DTextures();
	auto iter = std::find(textures->GetValue().begin(), textures->GetValue().end(), texture.ID);
	if(iter != textures->GetValue().end())
	{
		textures->GetValue().erase(iter);
	}
	EntityConfig::SetEntity(this->ID, Keys::Camera::GLOBAL2DTEXTURE, textures);
}
void LuaCamera::Set2DTexture(const luabind::object& textures)
{
	std::vector<std::string> textureIDs;
	if(luabind::type(textures) != LUA_TTABLE)
		Logger::LogError("Wrong paramter for Camera::Set2DTexture, please send in a table");
	for(luabind::iterator it(textures);
		it != luabind::iterator();
		++it)
	{
		std::string texID = luabind::object_cast<LuaBasicTexture>(*it).ID;
		textureIDs.push_back(texID);
	}
	EntityConfig::SetEntity(this->ID, Keys::Camera::GLOBAL2DTEXTURE, GenericObj<std::vector<std::string>>::CreateNew(textureIDs));
}
luabind::object LuaCamera::All2DTexture()
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

std::shared_ptr<GenericObj<std::vector<std::string>>> LuaCamera::GetRawAllCubeTextures()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::GLOBALCUBETEXTURE);
	return GenericObj<std::vector<std::string>>::Cast(obj);
}
void LuaCamera::AddCubeTexture(LuaBasicTexture texture)
{
	std::shared_ptr<GenericObj<std::vector<std::string>>> textures = this->GetRawAllCubeTextures();
	textures->GetValue().push_back(texture.ID);
	EntityConfig::SetEntity(this->ID, Keys::Camera::GLOBALCUBETEXTURE, textures);
}
void LuaCamera::RemoveCubeTexture(LuaBasicTexture texture)
{
	std::shared_ptr<GenericObj<std::vector<std::string>>> textures = this->GetRawAllCubeTextures();
	auto iter = std::find(textures->GetValue().begin(), textures->GetValue().end(), texture.ID);
	if(iter != textures->GetValue().end())
	{
		textures->GetValue().erase(iter);
	}
	EntityConfig::SetEntity(this->ID, Keys::Camera::GLOBALCUBETEXTURE, textures);
}
void LuaCamera::SetCubeTexture(const luabind::object& textures)
{
	std::vector<std::string> textureIDs;
	if(luabind::type(textures) != LUA_TTABLE)
		Logger::LogError("Wrong paramter for Camera::SetCubeTexture, please send in a table");
	for(luabind::iterator it(textures);
		it != luabind::iterator();
		++it)
	{
		std::string texID = luabind::object_cast<LuaBasicTexture>(*it).ID;
		textureIDs.push_back(texID);
	}
	EntityConfig::SetEntity(this->ID, Keys::Camera::GLOBALCUBETEXTURE, GenericObj<std::vector<std::string>>::CreateNew(textureIDs));
}
luabind::object LuaCamera::AllCubeTexture()
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

void LuaCamera::SetGlobalUserData(const luabind::object& textures)
{
	std::array<float, CameraINFO::GLOBALUSERDATASIZE> userData;
	if(luabind::type(textures) != LUA_TTABLE)
		Logger::LogError("Wrong paramter for Camera::SetGlobalUserData, please send in a table");
	unsigned int iCounter = 0;
	for(luabind::iterator it(textures);
		it != luabind::iterator() && iCounter < CameraINFO::GLOBALUSERDATASIZE;
		++it, ++iCounter)
	{
		userData[iCounter] = luabind::object_cast<float>(*it);
	}
	EntityConfig::SetEntity(this->ID, Keys::Camera::GLOBALUSERDATA, GenericObj<std::array<float, CameraINFO::GLOBALUSERDATASIZE>>::CreateNew(userData));
}
luabind::object LuaCamera::GetGlobalUserData()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::GLOBALUSERDATA);
	std::array<float, CameraINFO::GLOBALUSERDATASIZE> userData = GenericObj<std::array<float, CameraINFO::GLOBALUSERDATASIZE>>::GetValue(obj);

	luabind::object luaUserDataTable = luabind::newtable(LuaManager::GetInstance().lua);
	for(unsigned int i = 0; i < CameraINFO::GLOBALUSERDATASIZE; ++i)
	{
		luaUserDataTable[i + 1] = userData[i];
	}
	return luaUserDataTable;
}

void LuaCamera::SetProccess2D(bool val)
{
	EntityConfig::SetEntity(this->ID, Keys::Camera::PROCESS2D, GenericObj<bool>::CreateNew(val));
}
bool LuaCamera::GetProccess2D()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::PROCESS2D);
	return GenericObj<bool>::GetValue(obj);
}

void LuaCamera::SetInclusionState(int type)
{
	CameraINFO::InclusionType inclusionType = static_cast<CameraINFO::InclusionType>(type);
	EntityConfig::SetEntity(this->ID, Keys::Camera::INCLUSIONSTATE, GenericObj<CameraINFO::InclusionType>::CreateNew(inclusionType));
}
int LuaCamera::GetInclusionState()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::INCLUSIONSTATE);
	CameraINFO::InclusionType inclusionType = GenericObj<CameraINFO::InclusionType >::GetValue(obj);
	return static_cast<int>(inclusionType);;
}

std::shared_ptr<GenericObj<std::set<std::string>>> LuaCamera::GetRawObjectList()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Camera::OBJECTLIST);
	return GenericObj<std::set<std::string>>::Cast(obj);
}
void LuaCamera::AddObject(LuaObject obj)
{
	std::shared_ptr<GenericObj<std::set<std::string>>> objects = this->GetRawObjectList();
	objects->GetValue().insert(obj.ID);
	EntityConfig::SetEntity(this->ID, Keys::Camera::OBJECTLIST, objects);
}
void LuaCamera::RemoveObject(LuaObject obj)
{
	std::shared_ptr<GenericObj<std::set<std::string>>> objectList = this->GetRawObjectList();
	auto iter = std::find(objectList->GetValue().begin(), objectList->GetValue().end(), obj.ID);
	if(iter != objectList->GetValue().end())
	{
		objectList->GetValue().erase(iter);
	}
	EntityConfig::SetEntity(this->ID, Keys::Camera::OBJECTLIST, objectList);
}
void LuaCamera::SetObjectList(const luabind::object& obj)
{
	if(luabind::type(obj) != LUA_TTABLE)
		Logger::LogError("Wrong paramter for Camera::SetObjectList, please send in a table");

	std::set<std::string> objects;
	for(luabind::iterator it(obj);
		it != luabind::iterator();
		++it)
	{
		std::string objID = luabind::object_cast<LuaObject>(*it).ID;
		objects.insert(objID);
	}
	EntityConfig::SetEntity(this->ID, Keys::Camera::OBJECTLIST, GenericObj<std::set<std::string>>::CreateNew(objects));
}
luabind::object LuaCamera::GetObjectList()
{
	std::shared_ptr<GenericObj<std::set<std::string>>> objList = this->GetRawObjectList();

	luabind::object luaObjVec = luabind::newtable(LuaManager::GetInstance().lua);
	int keyCounter = 1;
	for(auto iter = objList->GetValue().begin();
		iter != objList->GetValue().end();
		++iter, ++keyCounter)
	{
		LuaBasicDrawableObject::BasicDrawableObject obj;
		obj.ID = (*iter);
		luaObjVec[keyCounter] = obj;
	}
	return luaObjVec;
}

void LuaCamera::Release()
{
	EntityConfig::DeleteEntity(this->ID);
	this->ID = "";
}

void LuaCamera::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::class_<LuaCamera>("Camera")
			.def(luabind::constructor<luabind::object const&>())
			.property("Eye", &LuaCamera::GetEye, &LuaCamera::SetEye)
			.property("TargetMagintude", &LuaCamera::GetTargetMagintude, &LuaCamera::SetTargetMagintude)
			.property("Up", &LuaCamera::GetUp, &LuaCamera::SetUp)
			.property("Roll", &LuaCamera::GetRoll, &LuaCamera::SetRoll)
			.property("Pitch", &LuaCamera::GetPitch, &LuaCamera::SetPitch)
			.property("Yaw", &LuaCamera::GetYaw, &LuaCamera::SetYaw)
			.property("FovAngle", &LuaCamera::GetFovAngle, &LuaCamera::SetFovAngle)
			.property("NearZ", &LuaCamera::GetNearZ, &LuaCamera::SetNearZ)
			.property("FarZ", &LuaCamera::GetFarZ, &LuaCamera::SetFarZ)
			.property("ClearColor", &LuaCamera::GetClearColor, &LuaCamera::SetClearColor)
			.property("Global2DTexture", &LuaCamera::All2DTexture, &LuaCamera::Set2DTexture)
			.def("AddGlobal2DTexture", &LuaCamera::Add2dTexture)
			.def("RemoveGlobal2DTexture", &LuaCamera::Remove2Texture)
			.property("GlobalCubeTexture", &LuaCamera::AllCubeTexture, &LuaCamera::SetCubeTexture)
			.def("AddGlobalCubeTexture", &LuaCamera::AddCubeTexture)
			.def("RemoveGlobalCubeTexture", &LuaCamera::RemoveCubeTexture)
			.property("GlobalUserData", &LuaCamera::GetGlobalUserData, &LuaCamera::SetGlobalUserData)
			.property("ObjectList", &LuaCamera::GetObjectList, &LuaCamera::SetObjectList)
			.def("AddObject", &LuaCamera::AddObject)
			.def("RemoveObject", &LuaCamera::RemoveObject)
			.def("MoveFroward", &LuaCamera::MoveFroward)
			.def("SetAsMain", &LuaCamera::SetAsMain)
			.def("Release", &LuaCamera::Release)
	  ];

	luabind::object inclusionType = luabind::newtable(lua);
	inclusionType["Exclude"] = 0;
	inclusionType["Include"] = 1;
	luabind::globals(lua)["InclusionType"] = inclusionType;
}