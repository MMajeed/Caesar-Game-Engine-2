#ifndef __LuaRigidBody__
#define __LuaRigidBody__

#include <lua.hpp>
#include <luabind\luabind.hpp>

#include "LuaMath.h"

namespace LuaRigidBody
{
	class RididBody
	{
	public:
		RididBody();
		RididBody(luabind::object const& table);
		void ApplyTorque(LuaMath::Vector4 v);
		void ApplyCentralFroce(LuaMath::Vector4 v);
		void Release();
		std::string ID;

		static void Register(lua_State *lua);
	};

	void RegisterAllLuaFunction(lua_State *lua);
}

#endif //__LuaRigidBody__
