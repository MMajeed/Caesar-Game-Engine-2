#include "GenericLuaObject.h"

void GenericLuaObject::RegisterAllLuaFunction(lua_State *lua)
{
	luabind::module(lua)[
		luabind::class_<GenericLuaObject>("GenericLuaObject")
			.def_readonly("ID", &GenericLuaObject::ID)
	];
}
