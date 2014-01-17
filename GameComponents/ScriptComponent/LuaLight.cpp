#include "LuaLight.h"
#include <Object.h>
#include <EntityCommunicator\EntityConfig.h>
#include <boost/numeric/ublas/vector.hpp>
#include <Keys.h>
#include <Logger.h>

// Light Class
LuaMath::Vector4 LuaLight::Light::GetDiffuse()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Light::DIFFUSE);
	return GenericObj<CHL::Vec4>::GetValue(obj);
}
void LuaLight::Light::SetDiffuse(LuaMath::Vector4 vec)
{
	EntityConfig::SetEntity(this->ID, Keys::Light::DIFFUSE, GenericObj<CHL::Vec4>::CreateNew(vec));
}

LuaMath::Vector4 LuaLight::Light::GetAmient()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Light::AMBIENT);
	return GenericObj<CHL::Vec4>::GetValue(obj);
}
void LuaLight::Light::SetAmbient(LuaMath::Vector4 vec)
{
	EntityConfig::SetEntity(this->ID, Keys::Light::AMBIENT, GenericObj<CHL::Vec4>::CreateNew(vec));
}

LuaMath::Vector4 LuaLight::Light::GetSpecular()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Light::SPECULAR);
	return GenericObj<CHL::Vec4>::GetValue(obj);
}
void LuaLight::Light::SetSpecular(LuaMath::Vector4 vec)
{
	EntityConfig::SetEntity(this->ID, Keys::Light::SPECULAR, GenericObj<CHL::Vec4>::CreateNew(vec));
}

void LuaLight::Light::Release()
{
	EntityConfig::DeleteEntity(this->ID);
	this->ID = "";
}
// Light Class End

// DirectionalLight class
LuaLight::DirectionalLight::DirectionalLight(luabind::object const& table)
{
	if(luabind::type(table) != LUA_TTABLE)
		Logger::LogError("Wrong paramter for DirectionalLight, please send in a table");

	CHL::Vec4 diffuse;	CHL::Vec4 ambient;	CHL::Vec4 specular;
	CHL::Vec4 direction;
	bool hasShadow = false;

	for(luabind::iterator it(table);
		it != luabind::iterator();
		++it)
	{
		std::string key = luabind::object_cast<std::string>( it.key() );

			 if(key == Keys::Light::DIFFUSE)		{ diffuse = luabind::object_cast<LuaMath::Vector4>( *it ); }
		else if(key == Keys::Light::AMBIENT)		{ ambient = luabind::object_cast<LuaMath::Vector4>( *it ); }
		else if(key == Keys::Light::SPECULAR)		{ specular = luabind::object_cast<LuaMath::Vector4>( *it ); }
		else if(key == Keys::Light::DIRECTION)		{ direction = luabind::object_cast<LuaMath::Vector4>( *it ); }
		else if(key == Keys::Light::HASHADOW)		{ hasShadow = luabind::object_cast<bool>( *it ); }
	}

	std::shared_ptr<DirectionalLightINFO> obj(new DirectionalLightINFO());
	obj->Diffuse = diffuse;
	obj->Ambient = ambient;
	obj->Specular = specular;
	obj->Direction = direction;
	obj->HasShadow = hasShadow;

	EntityConfig::SetEntity(obj);
	this->ID = obj->ID;
}

LuaMath::Vector4 LuaLight::DirectionalLight::GetDirection()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Light::DIRECTION);
	return GenericObj<CHL::Vec4>::GetValue(obj);
}
void LuaLight::DirectionalLight::SetDirection(LuaMath::Vector4 vec)
{
	EntityConfig::SetEntity(this->ID, Keys::Light::DIRECTION, GenericObj<CHL::Vec4>::CreateNew(vec));
}

void LuaLight::DirectionalLight::Register(lua_State *lua)
{
	luabind::module(lua)[
		luabind::class_<LuaLight::DirectionalLight>("DirectionalLight")
			.def(luabind::constructor<luabind::object const&>())
			.def_readonly("ID", &LuaLight::DirectionalLight::ID)
			.property("Diffuse", &LuaLight::DirectionalLight::GetDiffuse, &LuaLight::DirectionalLight::SetDiffuse)
			.property("Ambient", &LuaLight::DirectionalLight::GetAmient, &LuaLight::DirectionalLight::SetAmbient)
			.property("Specular", &LuaLight::DirectionalLight::GetSpecular, &LuaLight::DirectionalLight::SetSpecular)
			.property("Direction", &LuaLight::DirectionalLight::GetDirection, &LuaLight::DirectionalLight::SetDirection)
			.def("Release", &LuaLight::DirectionalLight::Release)
	];
}

// DirectionalLight end

// PointLight
LuaLight::PointLight::PointLight(luabind::object const& table)
{
	if(luabind::type(table) != LUA_TTABLE)
		Logger::LogError("Wrong paramter for PointLight, please send in a table");

	CHL::Vec4 diffuse;	CHL::Vec4 ambient;	CHL::Vec4 specular;
	CHL::Vec4 position;	CHL::Vec4 att; double range = 0.0;

	for(luabind::iterator it(table);
		it != luabind::iterator();
		++it)
	{
		std::string key = luabind::object_cast<std::string>( it.key() );

			 if(key == Keys::Light::DIFFUSE)		{ diffuse = luabind::object_cast<LuaMath::Vector4>( *it ); }
		else if(key == Keys::Light::AMBIENT)		{ ambient = luabind::object_cast<LuaMath::Vector4>( *it ); }
		else if(key == Keys::Light::SPECULAR)		{ specular = luabind::object_cast<LuaMath::Vector4>( *it ); }
		else if(key == Keys::Light::POSITION)		{ position = luabind::object_cast<LuaMath::Vector4>( *it ); }
		else if(key == Keys::Light::ATTENUATION)	{ att = luabind::object_cast<LuaMath::Vector4>( *it ); }
		else if(key == Keys::Light::RANGE)			{ range = luabind::object_cast<double>( *it ); }
	}

	std::shared_ptr<PointLightINFO> obj(new PointLightINFO());
	obj->Diffuse = diffuse;
	obj->Ambient = ambient;
	obj->Specular = specular;
	obj->Position = position;
	obj->Attenuation = att;
	obj->Range = range;
	EntityConfig::SetEntity(obj);
	this->ID = obj->ID;
}

LuaMath::Vector4 LuaLight::PointLight::GetPosition()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Light::POSITION);
	return GenericObj<CHL::Vec4>::GetValue(obj);
}
void LuaLight::PointLight::SetPosition(LuaMath::Vector4 vec)
{
	EntityConfig::SetEntity(this->ID, Keys::Light::POSITION, GenericObj<CHL::Vec4>::CreateNew(vec));
}

double LuaLight::PointLight::GetRange()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Light::RANGE);
	return GenericObj<double>::GetValue(obj);
}
void LuaLight::PointLight::SetRange(double val)
{
	EntityConfig::SetEntity(this->ID, Keys::Light::RANGE, GenericObj<double>::CreateNew(val));
}

LuaMath::Vector4 LuaLight::PointLight::GetAttenuation()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Light::ATTENUATION);
	return GenericObj<CHL::Vec4>::GetValue(obj);
}
void LuaLight::PointLight::SetAttenuation(LuaMath::Vector4 vec)
{
	EntityConfig::SetEntity(this->ID, Keys::Light::ATTENUATION, GenericObj<CHL::Vec4>::CreateNew(vec));
}

void LuaLight::PointLight::Register(lua_State *lua)
{
	luabind::module(lua)[
		luabind::class_<LuaLight::PointLight>("PointLight")
			.def(luabind::constructor<luabind::object const&>())
			.def_readonly("ID", &LuaLight::PointLight::ID)
			.property("Diffuse", &LuaLight::PointLight::GetDiffuse, &LuaLight::PointLight::SetDiffuse)
			.property("Ambient", &LuaLight::PointLight::GetAmient, &LuaLight::PointLight::SetAmbient)
			.property("Specular", &LuaLight::PointLight::GetSpecular, &LuaLight::PointLight::SetSpecular)
			.property("Position", &LuaLight::PointLight::GetPosition, &LuaLight::PointLight::SetPosition)
			.property("Range", &LuaLight::PointLight::GetRange, &LuaLight::PointLight::SetRange)
			.property("Attenuation", &LuaLight::PointLight::GetAttenuation, &LuaLight::PointLight::SetAttenuation)
			.def("Release", &LuaLight::PointLight::Release)
	];
}

// PointLight end

// SpotLight class
LuaLight::SpotLight::SpotLight(luabind::object const& table)
{
	if(luabind::type(table) != LUA_TTABLE)
		Logger::LogError("Wrong paramter for SpotLight, please send in a table");

	int slot = 0;
	CHL::Vec4 diffuse;	CHL::Vec4 ambient;	CHL::Vec4 specular;
	CHL::Vec4 position; CHL::Vec4 direction; CHL::Vec4 att;
	double spot = 0.0;	double range = 0.0;
	bool hasShadow = false;

	for(luabind::iterator it(table);
		it != luabind::iterator();
		++it)
	{
		std::string key = luabind::object_cast<std::string>( it.key() );

			 if(key == Keys::Light::DIFFUSE)		{ diffuse = luabind::object_cast<LuaMath::Vector4>( *it ); }
		else if(key == Keys::Light::AMBIENT)		{ ambient = luabind::object_cast<LuaMath::Vector4>( *it ); }
		else if(key == Keys::Light::SPECULAR)		{ specular = luabind::object_cast<LuaMath::Vector4>( *it ); }
		else if(key == Keys::Light::POSITION)		{ position = luabind::object_cast<LuaMath::Vector4>( *it ); }
		else if(key == Keys::Light::DIRECTION)		{ direction = luabind::object_cast<LuaMath::Vector4>( *it ); }
		else if(key == Keys::Light::ATTENUATION)	{ att = luabind::object_cast<LuaMath::Vector4>( *it ); }
		else if(key == Keys::Light::SPOT)			{ spot = luabind::object_cast<double>( *it ); }
		else if(key == Keys::Light::RANGE)			{ range = luabind::object_cast<double>( *it ); }
		else if(key == Keys::Light::HASHADOW)		{ hasShadow = luabind::object_cast<bool>( *it ); }
	}

	std::shared_ptr<SpotLightINFO> obj(new SpotLightINFO());
	obj->Diffuse = diffuse;
	obj->Ambient = ambient;
	obj->Specular = specular;
	obj->Position = position;
	obj->Direction = direction;
	obj->Attenuation = att;
	obj->Spot = spot;
	obj->Range = range;
	obj->HasShadow = hasShadow;
	EntityConfig::SetEntity(obj);
	this->ID = obj->ID;
}

LuaMath::Vector4 LuaLight::SpotLight::GetPosition()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Light::POSITION);
	return GenericObj<CHL::Vec4>::GetValue(obj);
}
void LuaLight::SpotLight::SetPosition(LuaMath::Vector4 vec)
{
	EntityConfig::SetEntity(this->ID, Keys::Light::POSITION, GenericObj<CHL::Vec4>::CreateNew(vec));
}

double LuaLight::SpotLight::GetRange()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Light::RANGE);
	return GenericObj<double>::GetValue(obj);
}
void LuaLight::SpotLight::SetRange(double val)
{
	EntityConfig::SetEntity(this->ID, Keys::Light::RANGE, GenericObj<double>::CreateNew(val));
}

LuaMath::Vector4 LuaLight::SpotLight::GetDirection()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Light::DIRECTION);
	return GenericObj<CHL::Vec4>::GetValue(obj);
}
void LuaLight::SpotLight::SetDirection(LuaMath::Vector4 vec)
{
	EntityConfig::SetEntity(this->ID, Keys::Light::DIRECTION, GenericObj<CHL::Vec4>::CreateNew(vec));
}

double LuaLight::SpotLight::GetSpot()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Light::SPOT);
	return GenericObj<double>::GetValue(obj);
}
void LuaLight::SpotLight::SetSpot(double val)
{
	EntityConfig::SetEntity(this->ID, Keys::Light::SPOT, GenericObj<double>::CreateNew(val));
}

LuaMath::Vector4 LuaLight::SpotLight::GetAttenuation()
{
	auto obj = EntityConfig::GetEntity(this->ID, Keys::Light::ATTENUATION);
	return GenericObj<CHL::Vec4>::GetValue(obj);
}
void LuaLight::SpotLight::SetAttenuation(LuaMath::Vector4 vec)
{
	EntityConfig::SetEntity(this->ID, Keys::Light::ATTENUATION, GenericObj<CHL::Vec4>::CreateNew(vec));
}

void LuaLight::SpotLight::Register(lua_State *lua)
{
	luabind::module(lua)[
		luabind::class_<LuaLight::SpotLight>("SpotLight")
			.def(luabind::constructor<luabind::object const&>())
			.def_readonly("ID", &LuaLight::SpotLight::ID)
			.property("Diffuse", &LuaLight::SpotLight::GetDiffuse, &LuaLight::SpotLight::SetDiffuse)
			.property("Ambient", &LuaLight::SpotLight::GetAmient, &LuaLight::SpotLight::SetAmbient)
			.property("Specular", &LuaLight::SpotLight::GetSpecular, &LuaLight::SpotLight::SetSpecular)
			.property("Position", &LuaLight::SpotLight::GetPosition, &LuaLight::SpotLight::SetPosition)
			.property("Range", &LuaLight::SpotLight::GetRange, &LuaLight::SpotLight::SetRange)
			.property("Direction", &LuaLight::SpotLight::GetDirection, &LuaLight::SpotLight::SetDirection)
			.property("Spot", &LuaLight::SpotLight::GetSpot, &LuaLight::SpotLight::SetSpot)
			.property("Attenuation", &LuaLight::SpotLight::GetAttenuation, &LuaLight::SpotLight::SetAttenuation)
			.def("Release", &LuaLight::SpotLight::Release)
	];
}
// SpotLight end