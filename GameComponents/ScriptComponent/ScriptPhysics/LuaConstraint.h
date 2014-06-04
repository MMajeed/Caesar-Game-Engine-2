#ifndef __LuaConstraint__
#define __LuaConstraint__

#include <lua.hpp>
#include <luabind\luabind.hpp>
#include "LuaRigidBody.h"
#include <ScriptCommon\LuaMath.h>

namespace LuaConstraint
{
	class BallSocket
	{
	public:
		BallSocket(luabind::object const& table);
		void Release();
		std::string ID;

		static void Register(lua_State *lua);
	};

	class Hinge
	{
	public:
		Hinge(luabind::object const& table);
		void Release();
		std::string ID;

		static void Register(lua_State *lua);
	};

	void RegisterAllLuaFunction(lua_State *lua);
}

#endif //__LuaConstraint__
