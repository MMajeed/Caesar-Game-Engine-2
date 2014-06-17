#include "LuaMouse.h"

#include "ScriptManager.h"
#include <InputCommunicator\GetMouseStatus.h>
#include <GraphicCommunicator\GraphicSettings.h>

namespace LuaMouse
{
	luabind::object Location()
	{
		std::pair<long, long> mouseLoc = Mouse::GetLoc();
		int x = mouseLoc.first;
		int y = mouseLoc.second;
		GraphicSettings::GetPosRelativeToClient(x, y);
		luabind::object keyState = luabind::newtable(ScriptManager::GetInstance().lua);
		keyState["X"] = x;
		keyState["Y"] = y;
		return keyState;
	}

	void RegisterAllLuaFunction(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::def("MouseLocation", LuaMouse::Location)
		];
	}
};