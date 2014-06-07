#ifndef __LuaConstraint__
#define __LuaConstraint__

#include "Linker.h"

#include <lua.hpp>
#include <luabind\luabind.hpp>
#include <GenericLuaObject.h>
#include "LuaRigidBody.h"
#include <LuaMath.h>

namespace LuaConstraint
{
	class ScriptPhysicsDLL_API BallSocket : public GenericLuaObject
	{
	public:
		BallSocket(luabind::object const& table);
		void Release();

		static void Register(lua_State *lua);
	};

	class ScriptPhysicsDLL_API Hinge : public GenericLuaObject
	{
	public:
		Hinge(luabind::object const& table);
		void Release();

		static void Register(lua_State *lua);
	};

	void RegisterAllLuaFunction(lua_State *lua);
}

#endif //__LuaConstraint__
