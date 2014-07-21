#include "GenericLuaObject.h"

GenericLuaObject::GenericLuaObject(std::string ID) : ID(ID){}
GenericLuaObject::operator std::string()
{
	return this->ID;
}

void GenericLuaObject::RegisterAllLuaFunction(lua_State *lua)
{
	luabind::module(lua)[
		luabind::class_<GenericLuaObject>("GenericLuaObject")
			.def_readonly("ID", &GenericLuaObject::ID)
	];
}
