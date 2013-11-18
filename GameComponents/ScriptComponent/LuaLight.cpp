#include "LuaLight.h"
#include <Object.h>
#include <InfoCommunicator\AddObjectMessage.h>
#include <InfoCommunicator\UpdateObjectMessage.h>
#include <InfoCommunicator\GetObjectINFO.h>
#include <InfoCommunicator\InfoCommunicator.h>
#include <boost/numeric/ublas/vector.hpp>
#include <Keys.h>

//**********************************************************************//
// Light Class
//**********************************************************************//
LuaMath::Vector4 LuaLight::Light::GetDiffuse()
{
	return this->GetGenericLightInfo()->Diffuse;
}
void LuaLight::Light::SetDiffuse(LuaMath::Vector4 vec)
{
	auto obj = this->GetGenericLightInfo();
	obj->Diffuse = vec;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}

LuaMath::Vector4 LuaLight::Light::GetAmient()
{
	return this->GetGenericLightInfo()->Ambient;
}
void LuaLight::Light::SetAmbient(LuaMath::Vector4 vec)
{
	auto obj = this->GetGenericLightInfo();
	obj->Ambient = vec;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}

LuaMath::Vector4 LuaLight::Light::GetSpecular()
{
	return this->GetGenericLightInfo()->Specular;
}
void LuaLight::Light::SetSpecular(LuaMath::Vector4 vec)
{
	auto obj = this->GetGenericLightInfo();
	obj->Specular = vec;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}

std::shared_ptr<LightINFO> LuaLight::Light::GetGenericLightInfo()
{
	std::shared_ptr<LightINFO> returnValue;

	auto obj = GetObjectINFO::GetObject(this->ID);
	if(obj)
	{
		returnValue = std::dynamic_pointer_cast<LightINFO>(obj);
		if(!returnValue){ throw std::exception("Attempted to cast an Object to LightINFO and failed"); }
	}
	return returnValue;
}
//**********************************************************************//
// Light Class End
//**********************************************************************//

//**********************************************************************//
// DirectionalLight class
//**********************************************************************//
LuaLight::DirectionalLight::DirectionalLight(luabind::object const& table)
{
	if (luabind::type(table) != LUA_TTABLE)
		throw std::exception("Wrong paramter for DirectionalLight, please send in a table");

	CHL::Vec4 diffuse;	CHL::Vec4 ambient;	CHL::Vec4 specular;
	CHL::Vec4 direction;

	for (luabind::iterator it(table);
		it != luabind::iterator();
		++it)
	{
		std::string key = luabind::object_cast<std::string>(it.key());

			 if (key == Keys::Light::DIFFUSE)		{ diffuse = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::AMBIENT)		{ ambient = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::SPECULAR)		{ specular = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::DIRECTION)		{ direction = luabind::object_cast<LuaMath::Vector4>(*it); }
	}

	std::shared_ptr<DirectionalLightINFO> obj(new DirectionalLightINFO());
	obj->Diffuse = diffuse;
	obj->Ambient = ambient;
	obj->Specular = specular;
	obj->Direction = direction;

	std::shared_ptr<AddObjectMessage> msg(new AddObjectMessage(obj));
	InfoCommunicator::SubmitMessage(msg);
	this->ID = obj->ID;
}
		
LuaMath::Vector4 LuaLight::DirectionalLight::GetDirection()
{
	return this->GetLightInfo()->Direction;
}
void LuaLight::DirectionalLight::SetDirection(LuaMath::Vector4 vec)
{
	auto obj = this->GetLightInfo();
	obj->Direction = vec;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}

std::shared_ptr<DirectionalLightINFO> LuaLight::DirectionalLight::GetLightInfo()
{
	std::shared_ptr<DirectionalLightINFO> returnValue;

	auto obj = GetObjectINFO::GetObject(this->ID);
	if(obj)
	{
		returnValue = std::dynamic_pointer_cast<DirectionalLightINFO>(obj);
		if(!returnValue){ throw std::exception("Attempted to cast an Object to DirectionalLight and failed"); }
	}
	return returnValue;
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
	];
}


//**********************************************************************//
// DirectionalLight end
//**********************************************************************//

//**********************************************************************//
// PointLight
//**********************************************************************//
LuaLight::PointLight::PointLight(luabind::object const& table)
{
	if (luabind::type(table) != LUA_TTABLE)
		throw std::exception("Wrong paramter for PointLight, please send in a table");

	CHL::Vec4 diffuse;	CHL::Vec4 ambient;	CHL::Vec4 specular;	
	CHL::Vec4 position;	CHL::Vec4 att; double range = 0.0;

	for (luabind::iterator it(table);
		it != luabind::iterator();
		++it)
	{
		std::string key = luabind::object_cast<std::string>(it.key());

			 if (key == Keys::Light::DIFFUSE)		{ diffuse = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::AMBIENT)		{ ambient = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::SPECULAR)		{ specular = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::POSITION)		{ position = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::ATTENUATION)	{ att = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::RANGE)			{ range = luabind::object_cast<double>(*it); }
	}

	std::shared_ptr<PointLightINFO> obj(new PointLightINFO());
	obj->Diffuse = diffuse;
	obj->Ambient = ambient;
	obj->Specular = specular;
	obj->Position = position;
	obj->Attenuation = att;
	obj->Range = range;

	std::shared_ptr<AddObjectMessage> msg(new AddObjectMessage(obj));
	InfoCommunicator::SubmitMessage(msg);
	this->ID = obj->ID;
}

LuaMath::Vector4 LuaLight::PointLight::GetPosition()
{
	return this->GetLightInfo()->Position;
}
void LuaLight::PointLight::SetPosition(LuaMath::Vector4 vec)
{
	auto obj = this->GetLightInfo();
	obj->Position = vec;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}

double LuaLight::PointLight::GetRange()
{
	return this->GetLightInfo()->Range;
}
void LuaLight::PointLight::SetRange(double val)
{
	auto obj = this->GetLightInfo();
	obj->Range = val;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}

LuaMath::Vector4 LuaLight::PointLight::GetAttenuation()
{
	return this->GetLightInfo()->Attenuation;
}
void LuaLight::PointLight::SetAttenuation(LuaMath::Vector4 vec)
{
	auto obj = this->GetLightInfo();
	obj->Attenuation = vec;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}

std::shared_ptr<PointLightINFO> LuaLight::PointLight::GetLightInfo()
{
	std::shared_ptr<PointLightINFO> returnValue;

	auto obj = GetObjectINFO::GetObject(this->ID);
	if(obj)
	{
		returnValue = std::dynamic_pointer_cast<PointLightINFO>(obj);
		if(!returnValue){ throw std::exception("Attempted to cast an Object to PointLightINFO and failed"); }
	}
	return returnValue;
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
	];
}

//**********************************************************************//
// PointLight end
//**********************************************************************//

//**********************************************************************//
// SpotLight class
//**********************************************************************//
LuaLight::SpotLight::SpotLight(luabind::object const& table)
{
	if (luabind::type(table) != LUA_TTABLE)
		throw std::exception("Wrong paramter for SpotLight, please send in a table");

	int slot = 0;
	CHL::Vec4 diffuse;	CHL::Vec4 ambient;	CHL::Vec4 specular;
	CHL::Vec4 position; CHL::Vec4 direction; CHL::Vec4 att;
	double spot = 0.0;	double range = 0.0;

	for (luabind::iterator it(table);
		it != luabind::iterator();
		++it)
	{
		std::string key = luabind::object_cast<std::string>(it.key());

			 if (key == Keys::Light::DIFFUSE)		{ diffuse = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::AMBIENT)		{ ambient = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::SPECULAR)		{ specular = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::POSITION)		{ position = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::DIRECTION)		{ direction = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::ATTENUATION)	{ att = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::SPOT)			{ spot = luabind::object_cast<double>(*it); }
		else if (key == Keys::Light::RANGE)			{ range = luabind::object_cast<double>(*it); }
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

	std::shared_ptr<AddObjectMessage> msg(new AddObjectMessage(obj));
	InfoCommunicator::SubmitMessage(msg);
	this->ID = obj->ID;
}

LuaMath::Vector4 LuaLight::SpotLight::GetPosition()
{
	return this->GetLightInfo()->Position;
}
void LuaLight::SpotLight::SetPosition(LuaMath::Vector4 vec)
{
	auto obj = this->GetLightInfo();
	obj->Position = vec;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}

double LuaLight::SpotLight::GetRange()
{
	return this->GetLightInfo()->Range;
}
void LuaLight::SpotLight::SetRange(double val)
{
	auto obj = this->GetLightInfo();
	obj->Range = val;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}

LuaMath::Vector4 LuaLight::SpotLight::GetDirection()
{
	return this->GetLightInfo()->Direction;
}
void LuaLight::SpotLight::SetDirection(LuaMath::Vector4 vec)
{
	auto obj = this->GetLightInfo();
	obj->Direction = vec;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}

double LuaLight::SpotLight::GetSpot()
{
	return this->GetLightInfo()->Spot;
}
void LuaLight::SpotLight::SetSpot(double val)
{
	auto obj = this->GetLightInfo();
	obj->Spot = val;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}

LuaMath::Vector4 LuaLight::SpotLight::GetAttenuation()
{
	return this->GetLightInfo()->Attenuation;
}
void LuaLight::SpotLight::SetAttenuation(LuaMath::Vector4 vec)
{
	auto obj = this->GetLightInfo();
	obj->Attenuation = vec;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}

void LuaLight::SpotLight::ApplyShadow()
{
	auto obj = this->GetLightInfo();
	obj->HasShadow = true;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}
void LuaLight::SpotLight::RemoveShadow()
{
	auto obj = this->GetLightInfo();
	obj->HasShadow = false;

	std::shared_ptr<UpdateObjectMessage> msg1(new UpdateObjectMessage(this->ID, obj));
	InfoCommunicator::SubmitMessage(msg1);
}
bool LuaLight::SpotLight::GetShadowState()
{
	return this->GetLightInfo()->HasShadow;
}

std::shared_ptr<SpotLightINFO> LuaLight::SpotLight::GetLightInfo()
{
	std::shared_ptr<SpotLightINFO> returnValue;

	auto obj = GetObjectINFO::GetObject(this->ID);
	if(obj)
	{
		returnValue = std::dynamic_pointer_cast<SpotLightINFO>(obj);
		if(!returnValue){ throw std::exception("Attempted to cast an Object to SpotLightINFO and failed"); }
	}
	return returnValue;
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
			.property("ShadowState", &LuaLight::SpotLight::GetShadowState)
			.def("ApplyShadow", &LuaLight::SpotLight::ApplyShadow)
			.def("RemoveShadow", &LuaLight::SpotLight::RemoveShadow)
	];
}
//**********************************************************************//
// SpotLight end
//**********************************************************************//

