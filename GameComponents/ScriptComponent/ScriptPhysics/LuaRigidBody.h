#ifndef __LuaRigidBody__
#define __LuaRigidBody__

#include "Linker.h"

#include <lua.hpp>
#include <luabind\luabind.hpp>
#include <GenericLuaObject.h>
#include <LuaMath.h>

namespace LuaRigidBody
{
	class ScriptPhysicsDLL_API RididBody : public GenericLuaObject
	{
	public:
		RididBody();
		RididBody(luabind::object const& table);

		void ApplyTorque(LuaMath::Vector4 v);
		void ApplyCentralFroce(LuaMath::Vector4 v);
		void SetTorque(LuaMath::Vector4 v);

		LuaMath::Vector4 GetTorque();
		LuaMath::Vector4 GetForce();
		LuaMath::Vector4 GetQuaRotation();
		LuaMath::Vector4 GetLocation();

		void Release();

		static void Register(lua_State *lua);
	};

	ScriptPhysicsDLL_API void RegisterAllLuaFunction(lua_State *lua);
}

#endif //__LuaRigidBody__
