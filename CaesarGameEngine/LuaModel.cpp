#include "LuaModel.h"

#include "LuaManager.h"
#include "Model.h"
#include <string>

void LuaModel::RegisterAllLuaFunction(lua_State *lua)
{	
	luabind::module(lua) [
		luabind::class_<Model>("Model")
		  .def(luabind::constructor<std::string>())
	  ];
}