#include "LuaMouse.h"

#include "ScriptManager.h"
#include <Resource.h>
#include <Windows.h>
#include <Components.h>

namespace LuaMouse
{
	luabind::object Location()
	{
		POINT p;
		GetCursorPos(&p);
		int x = p.x;
		int y = p.y;
		Components::Graphic->GraphicSettingsFactory()->GetPosRelativeToClient(x, y);
		luabind::object keyState = luabind::newtable(Resource::lua);
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