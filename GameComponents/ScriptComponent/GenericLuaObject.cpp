#include "GenericLuaObject.h"

GenericLuaObject::GenericLuaObject(const std::string& ID) : ID(ID){}
GenericLuaObject::operator std::string()
{
	return this->GetID();
}
std::string GenericLuaObject::GetID() const
{
	return this->ID;
}

void GenericLuaObject::RegisterAllLuaFunction(lua_State *lua)
{
	luabind::module(lua)[
		luabind::class_<GenericLuaObject>("GenericLuaObject")
			.def(luabind::constructor<const std::string&>())
			.def_readonly("ID", &GenericLuaObject::ID)
	];
}
