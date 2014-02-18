#ifndef __LuaConstraint__
#define __LuaConstraint__

#include <lua.hpp>
#include <luabind\luabind.hpp>

#include "LuaMath.h"

namespace LuaConstraint
{
	class BallSocketBodyToPoint
	{
	public:
		BallSocketBodyToPoint(luabind::object const& table);
		void Release();
		std::string ID;

		static void Register(lua_State *lua);
	};

	void RegisterAllLuaFunction(lua_State *lua);
}

#endif //__LuaConstraint__
