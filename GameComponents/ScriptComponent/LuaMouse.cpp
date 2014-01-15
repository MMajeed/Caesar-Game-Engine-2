#include "LuaMouse.h"

#include "LuaManager.h"
#include <InputCommunicator\GetMouseStatus.h>

namespace LuaMouse
{
	luabind::object Location()
	{
		std::pair<long, long> mouseLoc = Mouse::GetLoc();
		luabind::object keyState = luabind::newtable(LuaManager::GetInstance().lua);
		keyState["X"] = mouseLoc.first;
		keyState["Y"] = mouseLoc.second;
		return keyState;
	}

	void RegisterAllLuaFunction(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::def("MouseLocation", LuaMouse::Location)
		];
	}
};