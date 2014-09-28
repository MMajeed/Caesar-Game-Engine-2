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
	}

	CameraEntities::Add(obj);
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