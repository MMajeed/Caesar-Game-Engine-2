#include "LuaLight.h"
#include <Object.h>
#include <InfoCommunicator\AddObjectMessage.h>
#include <InfoCommunicator\UpdateObjectMessage.h>
#include <InfoCommunicator\ObjectManagerOutput.h>
#include <InfoCommunicator\InfoCommunicator.h>
#include <boost/numeric/ublas/vector.hpp>
#include <Keys.h>

using boost::numeric::ublas::vector;

// Light Class
LuaUblas::Vector4 LuaLight::Light::GetDiffuse()
{	
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::DIFFUSE];
	return GenericObject<vector<double>>::GetValue(obj);
}
void LuaLight::Light::SetDiffuse(LuaUblas::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<vector<double>>::CreateNew(vec);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::DIFFUSE, obj));
	InfoCommunicator::SubmitMessage(msg);
}

LuaUblas::Vector4 LuaLight::Light::GetAmient()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::AMBIENT];
	return GenericObject<vector<double>>::GetValue(obj);
}
void LuaLight::Light::SetAmbient(LuaUblas::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<vector<double>>::CreateNew(vec);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::AMBIENT, obj));
	InfoCommunicator::SubmitMessage(msg);
}

LuaUblas::Vector4 LuaLight::Light::GetSpecular()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::SPECULAR];
	return GenericObject<vector<double>>::GetValue(obj);
}
void LuaLight::Light::SetSpecular(LuaUblas::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<vector<double>>::CreateNew(vec);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::SPECULAR, obj));
	InfoCommunicator::SubmitMessage(msg);
}

int LuaLight::Light::GetSlot()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::LIGHTSLOT];
	return GenericObject<int>::GetValue(obj);
}
void LuaLight::Light::SetSlot(int i)
{
	std::shared_ptr<Object> obj = GenericObject<int>::CreateNew(i);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::LIGHTSLOT, obj));
	InfoCommunicator::SubmitMessage(msg);
}
// Light Class End

// DirectionalLight class
LuaLight::DirectionalLight::DirectionalLight(int slot, LuaUblas::Vector4 diffuse, LuaUblas::Vector4 ambient, LuaUblas::Vector4 specular, LuaUblas::Vector4 direction )
{
	std::hash_map<std::string, std::shared_ptr<Object>> mapKeys;

	mapKeys[Keys::Class] = GenericObject<std::string>::CreateNew(Keys::ClassType::Light);
	mapKeys[Keys::LIGHTTYPE] = GenericObject<std::string>::CreateNew(Keys::LightType::DIRECTIONAL);
	mapKeys[Keys::LIGHTSLOT] = GenericObject<int>::CreateNew(slot);
	mapKeys[Keys::DIFFUSE] = GenericObject<vector<double>>::CreateNew(diffuse.vector);
	mapKeys[Keys::AMBIENT] = GenericObject<vector<double>>::CreateNew(ambient.vector);
	mapKeys[Keys::SPECULAR] = GenericObject<vector<double>>::CreateNew(specular.vector);
	mapKeys[Keys::DIRECTION] = GenericObject<vector<double>>::CreateNew(direction.vector);

	std::shared_ptr<AddObjectMessage> msg(new AddObjectMessage(mapKeys));

	InfoCommunicator::SubmitMessage(msg);

	msg->WaitTillProcccesed();

	this->ID = msg->ID;
}
		
LuaUblas::Vector4 LuaLight::DirectionalLight::GetDirection()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::DIRECTION];
	return GenericObject<vector<double>>::GetValue(obj);
}
void LuaLight::DirectionalLight::SetDirection(LuaUblas::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<vector<double>>::CreateNew(vec);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::DIRECTION, obj));
	InfoCommunicator::SubmitMessage(msg);
}
// DirectionalLight end

// PointLight
LuaLight::PointLight::PointLight(int slot, 
								 LuaUblas::Vector4 diffuse, LuaUblas::Vector4 ambient, LuaUblas::Vector4 specular, 
								 LuaUblas::Vector4 position, double range, LuaUblas::Vector4  att)
{
	std::hash_map<std::string, std::shared_ptr<Object>> mapKeys;

	mapKeys[Keys::Class] = GenericObject<std::string>::CreateNew(Keys::ClassType::Light);
	mapKeys[Keys::LIGHTTYPE] = GenericObject<std::string>::CreateNew(Keys::LightType::POINT);
	mapKeys[Keys::LIGHTSLOT] = GenericObject<int>::CreateNew(slot);
	mapKeys[Keys::DIFFUSE] = GenericObject<vector<double>>::CreateNew(diffuse.vector);
	mapKeys[Keys::AMBIENT] = GenericObject<vector<double>>::CreateNew(ambient.vector);
	mapKeys[Keys::SPECULAR] = GenericObject<vector<double>>::CreateNew(specular.vector);
	mapKeys[Keys::POSITION] = GenericObject<vector<double>>::CreateNew(position.vector);
	mapKeys[Keys::RANGE] = GenericObject<double>::CreateNew(range);
	mapKeys[Keys::ATTENUATION] = GenericObject<vector<double>>::CreateNew(att.vector);

	std::shared_ptr<AddObjectMessage> msg(new AddObjectMessage(mapKeys));

	InfoCommunicator::SubmitMessage(msg);

	msg->WaitTillProcccesed();

	this->ID = msg->ID;
}

LuaUblas::Vector4 LuaLight::PointLight::GetPosition()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::POSITION];
	return GenericObject<vector<double>>::GetValue(obj);
}
void LuaLight::PointLight::SetPosition(LuaUblas::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<vector<double>>::CreateNew(vec);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::POSITION, obj));
	InfoCommunicator::SubmitMessage(msg);
}

double LuaLight::PointLight::GetRange()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::RANGE];
	return GenericObject<double>::GetValue(obj);
}
void LuaLight::PointLight::SetRange(double val)
{
	std::shared_ptr<Object> obj = GenericObject<double>::CreateNew(val);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::RANGE, obj));
	InfoCommunicator::SubmitMessage(msg);
}

LuaUblas::Vector4 LuaLight::PointLight::GetAttenuation()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::ATTENUATION];
	return GenericObject<vector<double>>::GetValue(obj);
}
void LuaLight::PointLight::SetAttenuation(LuaUblas::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<vector<double>>::CreateNew(vec);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::ATTENUATION, obj));
	InfoCommunicator::SubmitMessage(msg);
}

// PointLight end

// SpotLight class
LuaLight::SpotLight::SpotLight(int slot, 
							   LuaUblas::Vector4 diffuse, LuaUblas::Vector4 ambient, LuaUblas::Vector4 specular, 
							   LuaUblas::Vector4 position, double range, LuaUblas::Vector4 Direction,  
							   double spot, LuaUblas::Vector4  att)
{
	std::hash_map<std::string, std::shared_ptr<Object>> mapKeys;

	mapKeys[Keys::Class] = GenericObject<std::string>::CreateNew(Keys::ClassType::Light);
	mapKeys[Keys::LIGHTTYPE] = GenericObject<std::string>::CreateNew(Keys::LightType::SPOT);
	mapKeys[Keys::LIGHTSLOT] = GenericObject<int>::CreateNew(slot);
	mapKeys[Keys::DIFFUSE] = GenericObject<vector<double>>::CreateNew(diffuse.vector);
	mapKeys[Keys::AMBIENT] = GenericObject<vector<double>>::CreateNew(ambient.vector);
	mapKeys[Keys::SPECULAR] = GenericObject<vector<double>>::CreateNew(specular.vector);
	mapKeys[Keys::POSITION] = GenericObject<vector<double>>::CreateNew(position.vector);
	mapKeys[Keys::RANGE] = GenericObject<double>::CreateNew(range);
	mapKeys[Keys::DIRECTION] = GenericObject<vector<double>>::CreateNew(Direction.vector);
	mapKeys[Keys::SPOT] = GenericObject<double>::CreateNew(spot);
	mapKeys[Keys::ATTENUATION] = GenericObject<vector<double>>::CreateNew(att.vector);
	mapKeys[Keys::HASHADOW] = GenericObject<bool>::CreateNew(false);

	std::shared_ptr<AddObjectMessage> msg(new AddObjectMessage(mapKeys));

	InfoCommunicator::SubmitMessage(msg);

	msg->WaitTillProcccesed();

	this->ID = msg->ID;
}

LuaUblas::Vector4 LuaLight::SpotLight::GetPosition()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::POSITION];
	return GenericObject<vector<double>>::GetValue(obj);
}
void LuaLight::SpotLight::SetPosition(LuaUblas::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<vector<double>>::CreateNew(vec);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::POSITION, obj));
	InfoCommunicator::SubmitMessage(msg);
}

double LuaLight::SpotLight::GetRange()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::RANGE];
	return GenericObject<double>::GetValue(obj);
}
void LuaLight::SpotLight::SetRange(double val)
{
	std::shared_ptr<Object> obj = GenericObject<double>::CreateNew(val);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::RANGE, obj));
	InfoCommunicator::SubmitMessage(msg);
}

LuaUblas::Vector4 LuaLight::SpotLight::GetDirection()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::DIRECTION];
	return GenericObject<vector<double>>::GetValue(obj);
}
void LuaLight::SpotLight::SetDirection(LuaUblas::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<vector<double>>::CreateNew(vec);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::DIRECTION, obj));
	InfoCommunicator::SubmitMessage(msg);
}

double LuaLight::SpotLight::GetSpot()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::SPOT];
	return GenericObject<double>::GetValue(obj);
}
void LuaLight::SpotLight::SetSpot(double val)
{
	std::shared_ptr<Object> obj = GenericObject<double>::CreateNew(val);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::SPOT, obj));
	InfoCommunicator::SubmitMessage(msg);
}

LuaUblas::Vector4 LuaLight::SpotLight::GetAttenuation()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::ATTENUATION];
	return GenericObject<vector<double>>::GetValue(obj);
}
void LuaLight::SpotLight::SetAttenuation(LuaUblas::Vector4 vec)
{
	std::shared_ptr<Object> obj = GenericObject<vector<double>>::CreateNew(vec);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::ATTENUATION, obj));
	InfoCommunicator::SubmitMessage(msg);
}

void LuaLight::SpotLight::ApplyShadow()
{
	std::shared_ptr<Object> obj = GenericObject<bool>::CreateNew(true);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::HASHADOW, obj));
	InfoCommunicator::SubmitMessage(msg);
}
void LuaLight::SpotLight::RemoveShadow()
{
	std::shared_ptr<Object> obj = GenericObject<bool>::CreateNew(false);
	std::shared_ptr<UpdateObjectMessage> msg(new UpdateObjectMessage(this->ID, Keys::HASHADOW, obj));
	InfoCommunicator::SubmitMessage(msg);
}
bool LuaLight::SpotLight::GetShadowState()
{
	auto obj = ObjectManagerOutput::GetObject(this->ID)[Keys::HASHADOW];
	return GenericObject<bool>::GetValue(obj);
}
// SpotLight end

void LuaLight::DirectionalLight::Register(lua_State *lua)
{
	luabind::module(lua) [
		luabind::class_<LuaLight::DirectionalLight>("DirectionalLight")
		  .def(luabind::constructor<int, LuaUblas::Vector4, LuaUblas::Vector4, LuaUblas::Vector4, LuaUblas::Vector4>())
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
		  .def(luabind::constructor<int, LuaUblas::Vector4, LuaUblas::Vector4, LuaUblas::Vector4, LuaUblas::Vector4, double, LuaUblas::Vector4>())
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
		  .def(luabind::constructor<int, LuaUblas::Vector4, LuaUblas::Vector4, LuaUblas::Vector4, LuaUblas::Vector4, double, LuaUblas::Vector4, double, LuaUblas::Vector4 >())
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