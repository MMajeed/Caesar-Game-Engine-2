#include "LuaMouse.h"

#include "ScriptManager.h"
#include <Windows.h>
#include <GraphicCommunicator\GraphicSettings.h>

namespace LuaMouse
{
	luabind::object Location()
	{
		POINT p;
		GetCursorPos(&p);
		int x = p.x;
		int y = p.y;
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