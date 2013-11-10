#include "LuaLight.h"
#include <Object.h>
#include <InfoCommunicator\AddObjectMessage.h>
#include <InfoCommunicator\UpdateObjectMessage.h>
#include <InfoCommunicator\ObjectManagerOutput.h>
#include <InfoCommunicator\InfoCommunicator.h>
#include <boost/numeric/ublas/vector.hpp>
#include <Keys.h>

// Light Class
LuaMath::Vector4 LuaLight::Light::GetDiffuse()
{	
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::Light::DIFFUSE];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}
void LuaLight::Light::SetDiffuse(LuaMath::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(vec);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::Light::DIFFUSE, obj));
	InfoCommunicator::SubmitMessage(msg);
}

LuaMath::Vector4 LuaLight::Light::GetAmient()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::Light::AMBIENT];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}
void LuaLight::Light::SetAmbient(LuaMath::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(vec);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::Light::AMBIENT, obj));
	InfoCommunicator::SubmitMessage(msg);
}

LuaMath::Vector4 LuaLight::Light::GetSpecular()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::Light::SPECULAR];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}
void LuaLight::Light::SetSpecular(LuaMath::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(vec);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::Light::SPECULAR, obj));
	InfoCommunicator::SubmitMessage(msg);
}

int LuaLight::Light::GetSlot()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::Light::LIGHTSLOT];
	return GenericObject<int>::GetValue(obj);
}
void LuaLight::Light::SetSlot(int i)
{
	std::shared_ptr<Object> obj = GenericObject<int>::CreateNew(i);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::Light::LIGHTSLOT, obj));
	InfoCommunicator::SubmitMessage(msg);
}
// Light Class End

// DirectionalLight class
LuaLight::DirectionalLight::DirectionalLight(luabind::object const& table)
{
	if (luabind::type(table) != LUA_TTABLE)
		throw std::exception("Wrong paramter for DirectionalLight, please send in a table");

	int slot = 0;
	CHL::Vec4 diffuse;	CHL::Vec4 ambient;	CHL::Vec4 specular;
	CHL::Vec4 direction;

	for (luabind::iterator it(table);
		it != luabind::iterator();
		++it)
	{
		std::string key = luabind::object_cast<std::string>(it.key());

			 if (key == Keys::Light::LIGHTSLOT)		{ slot = luabind::object_cast<int>(*it); }
		else if (key == Keys::Light::DIFFUSE)		{ diffuse = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::AMBIENT)		{ ambient = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::SPECULAR)		{ specular = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::DIRECTION)		{ direction = luabind::object_cast<LuaMath::Vector4>(*it); }
	}

	std::hash_map<std::string, std::shared_ptr<Object>> mapKeys;
	mapKeys[Keys::Class] = GenericObject<std::string>::CreateNew(Keys::ClassType::Light);
	mapKeys[Keys::Light::LIGHTTYPE] = GenericObject<std::string>::CreateNew(Keys::Light::LightTypes::DIRECTIONAL);
	mapKeys[Keys::Light::LIGHTSLOT] = GenericObject<int>::CreateNew(slot);
	mapKeys[Keys::Light::DIFFUSE] = GenericObject<CHL::Vec4>::CreateNew(diffuse);
	mapKeys[Keys::Light::AMBIENT] = GenericObject<CHL::Vec4>::CreateNew(ambient);
	mapKeys[Keys::Light::SPECULAR] = GenericObject<CHL::Vec4>::CreateNew(specular);
	mapKeys[Keys::Light::DIRECTION] = GenericObject<CHL::Vec4>::CreateNew(direction);
	std::shared_ptr<AddObjectMessage> msg(new AddObjectMessage(mapKeys));

	InfoCommunicator::SubmitMessage(msg);
	this->ID = msg->ID;
}
		
LuaMath::Vector4 LuaLight::DirectionalLight::GetDirection()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::Light::DIRECTION];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}
void LuaLight::DirectionalLight::SetDirection(LuaMath::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(vec);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::Light::DIRECTION, obj));
	InfoCommunicator::SubmitMessage(msg);
}
// DirectionalLight end

// PointLight
LuaLight::PointLight::PointLight(luabind::object const& table)
{
	if (luabind::type(table) != LUA_TTABLE)
		throw std::exception("Wrong paramter for PointLight, please send in a table");

	int slot = 0;
	CHL::Vec4 diffuse;	CHL::Vec4 ambient;	CHL::Vec4 specular;	
	CHL::Vec4 position;	CHL::Vec4 att; double range = 0.0;

	for (luabind::iterator it(table);
		it != luabind::iterator();
		++it)
	{
		std::string key = luabind::object_cast<std::string>(it.key());

			 if (key == Keys::Light::LIGHTSLOT)		{ slot = luabind::object_cast<int>(*it); }
		else if (key == Keys::Light::DIFFUSE)		{ diffuse = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::AMBIENT)		{ ambient = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::SPECULAR)		{ specular = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::POSITION)		{ position = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::ATTENUATION)	{ att = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::RANGE)			{ range = luabind::object_cast<double>(*it); }
	}

	std::hash_map<std::string, std::shared_ptr<Object>> mapKeys;

	mapKeys[Keys::Class] = GenericObject<std::string>::CreateNew(Keys::ClassType::Light);
	mapKeys[Keys::Light::LIGHTTYPE] = GenericObject<std::string>::CreateNew(Keys::Light::LightTypes::POINT);
	mapKeys[Keys::Light::LIGHTSLOT] = GenericObject<int>::CreateNew(slot);
	mapKeys[Keys::Light::DIFFUSE] = GenericObject<CHL::Vec4>::CreateNew(diffuse);
	mapKeys[Keys::Light::AMBIENT] = GenericObject<CHL::Vec4>::CreateNew(ambient);
	mapKeys[Keys::Light::SPECULAR] = GenericObject<CHL::Vec4>::CreateNew(specular);
	mapKeys[Keys::Light::POSITION] = GenericObject<CHL::Vec4>::CreateNew(position);
	mapKeys[Keys::Light::RANGE] = GenericObject<double>::CreateNew(range);
	mapKeys[Keys::Light::ATTENUATION] = GenericObject<CHL::Vec4>::CreateNew(att);

	std::shared_ptr<AddObjectMessage> msg(new AddObjectMessage(mapKeys));

	InfoCommunicator::SubmitMessage(msg);

	this->ID = msg->ID;
}

LuaMath::Vector4 LuaLight::PointLight::GetPosition()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::Light::POSITION];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}
void LuaLight::PointLight::SetPosition(LuaMath::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(vec);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::Light::POSITION, obj));
	InfoCommunicator::SubmitMessage(msg);
}

double LuaLight::PointLight::GetRange()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::Light::RANGE];
	return GenericObject<double>::GetValue(obj);
}
void LuaLight::PointLight::SetRange(double val)
{
	std::shared_ptr<Object> obj = GenericObject<double>::CreateNew(val);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::Light::RANGE, obj));
	InfoCommunicator::SubmitMessage(msg);
}

LuaMath::Vector4 LuaLight::PointLight::GetAttenuation()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::Light::ATTENUATION];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}
void LuaLight::PointLight::SetAttenuation(LuaMath::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(vec);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::Light::ATTENUATION, obj));
	InfoCommunicator::SubmitMessage(msg);
}

// PointLight end

// SpotLight class
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

			 if (key == Keys::Light::LIGHTSLOT)		{ slot = luabind::object_cast<int>(*it); }
		else if (key == Keys::Light::DIFFUSE)		{ diffuse = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::AMBIENT)		{ ambient = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::SPECULAR)		{ specular = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::POSITION)		{ position = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::DIRECTION)		{ direction = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::ATTENUATION)	{ att = luabind::object_cast<LuaMath::Vector4>(*it); }
		else if (key == Keys::Light::SPOT)			{ spot = luabind::object_cast<double>(*it); }
		else if (key == Keys::Light::RANGE)			{ range = luabind::object_cast<double>(*it); }
	}
	std::hash_map<std::string, std::shared_ptr<Object>> mapKeys;

	mapKeys[Keys::Class] = GenericObject<std::string>::CreateNew(Keys::ClassType::Light);
	mapKeys[Keys::Light::LIGHTTYPE] = GenericObject<std::string>::CreateNew(Keys::Light::LightTypes::SPOT);
	mapKeys[Keys::Light::LIGHTSLOT] = GenericObject<int>::CreateNew(slot);
	mapKeys[Keys::Light::DIFFUSE] = GenericObject<CHL::Vec4>::CreateNew(diffuse);
	mapKeys[Keys::Light::AMBIENT] = GenericObject<CHL::Vec4>::CreateNew(ambient);
	mapKeys[Keys::Light::SPECULAR] = GenericObject<CHL::Vec4>::CreateNew(specular);
	mapKeys[Keys::Light::POSITION] = GenericObject<CHL::Vec4>::CreateNew(position);
	mapKeys[Keys::Light::RANGE] = GenericObject<double>::CreateNew(range);
	mapKeys[Keys::Light::DIRECTION] = GenericObject<CHL::Vec4>::CreateNew(direction);
	mapKeys[Keys::Light::SPOT] = GenericObject<double>::CreateNew(spot);
	mapKeys[Keys::Light::ATTENUATION] = GenericObject<CHL::Vec4>::CreateNew(att);
	mapKeys[Keys::Light::HASHADOW] = GenericObject<bool>::CreateNew(false);

	std::shared_ptr<AddObjectMessage> msg(new AddObjectMessage(mapKeys));

	InfoCommunicator::SubmitMessage(msg);

	this->ID = msg->ID;
}

LuaMath::Vector4 LuaLight::SpotLight::GetPosition()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::Light::POSITION];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}
void LuaLight::SpotLight::SetPosition(LuaMath::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(vec);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::Light::POSITION, obj));
	InfoCommunicator::SubmitMessage(msg);
}

double LuaLight::SpotLight::GetRange()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::Light::RANGE];
	return GenericObject<double>::GetValue(obj);
}
void LuaLight::SpotLight::SetRange(double val)
{
	std::shared_ptr<Object> obj = GenericObject<double>::CreateNew(val);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::Light::RANGE, obj));
	InfoCommunicator::SubmitMessage(msg);
}

LuaMath::Vector4 LuaLight::SpotLight::GetDirection()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::Light::DIRECTION];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}
void LuaLight::SpotLight::SetDirection(LuaMath::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(vec);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::Light::DIRECTION, obj));
	InfoCommunicator::SubmitMessage(msg);
}

double LuaLight::SpotLight::GetSpot()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::Light::SPOT];
	return GenericObject<double>::GetValue(obj);
}
void LuaLight::SpotLight::SetSpot(double val)
{
	std::shared_ptr<Object> obj = GenericObject<double>::CreateNew(val);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::Light::SPOT, obj));
	InfoCommunicator::SubmitMessage(msg);
}

LuaMath::Vector4 LuaLight::SpotLight::GetAttenuation()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::Light::ATTENUATION];
	return GenericObject<CHL::Vec4>::GetValue(obj);
}
void LuaLight::SpotLight::SetAttenuation(LuaMath::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<CHL::Vec4>::CreateNew(vec);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::Light::ATTENUATION, obj));
	InfoCommunicator::SubmitMessage(msg);
}

void LuaLight::SpotLight::ApplyShadow()
{
	std::shared_ptr<Object> obj = GenericObject<bool>::CreateNew(true);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::Light::HASHADOW, obj));
	InfoCommunicator::SubmitMessage(msg);
}
void LuaLight::SpotLight::RemoveShadow()
{
	std::shared_ptr<Object> obj = GenericObject<bool>::CreateNew(false);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::Light::HASHADOW, obj));
	InfoCommunicator::SubmitMessage(msg);
}
bool LuaLight::SpotLight::GetShadowState()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::Light::HASHADOW];
	return GenericObject<bool>::GetValue(obj);
}
// SpotLight end

void LuaLight::DirectionalLight::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::class_<LuaLight::DirectionalLight>("DirectionalLight")
		  .def(luabind::constructor<luabind::object const&>())
		  .def_readonly("ID", &LuaLight::DirectionalLight::ID)
		  .property("Slot", &LuaLight::DirectionalLight::GetSlot, &LuaLight::DirectionalLight::SetSlot)
		  .property("Diffuse", &LuaLight::DirectionalLight::GetDiffuse, &LuaLight::DirectionalLight::SetDiffuse)
		  .property("Ambient", &LuaLight::DirectionalLight::GetAmient, &LuaLight::DirectionalLight::SetAmbient)
		  .property("Specular", &LuaLight::DirectionalLight::GetSpecular, &LuaLight::DirectionalLight::SetSpecular)
		  .property("Direction", &LuaLight::DirectionalLight::GetDirection, &LuaLight::DirectionalLight::SetDirection)
	  ];
}

void LuaLight::PointLight::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::class_<LuaLight::PointLight>("PointLight")
		  .def(luabind::constructor<luabind::object const&>())
		  .def_readonly("ID", &LuaLight::PointLight::ID)
		  .property("Slot", &LuaLight::PointLight::GetSlot, &LuaLight::PointLight::SetSlot)
		  .property("Diffuse", &LuaLight::PointLight::GetDiffuse, &LuaLight::PointLight::SetDiffuse)
		  .property("Ambient", &LuaLight::PointLight::GetAmient, &LuaLight::PointLight::SetAmbient)
		  .property("Specular", &LuaLight::PointLight::GetSpecular, &LuaLight::PointLight::SetSpecular)
		  .property("Position", &LuaLight::PointLight::GetPosition, &LuaLight::PointLight::SetPosition)
		  .property("Range", &LuaLight::PointLight::GetRange, &LuaLight::PointLight::SetRange)
		  .property("Attenuation", &LuaLight::PointLight::GetAttenuation, &LuaLight::PointLight::SetAttenuation)
	  ];
}

void LuaLight::SpotLight::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::class_<LuaLight::SpotLight>("SpotLight")
		  .def(luabind::constructor<luabind::object const&>())
		  .def_readonly("ID", &LuaLight::SpotLight::ID)
		  .property("Slot", &LuaLight::SpotLight::GetSlot, &LuaLight::SpotLight::SetSlot)
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