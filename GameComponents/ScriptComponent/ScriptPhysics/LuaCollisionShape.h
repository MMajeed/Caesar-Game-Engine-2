#ifndef __LuaCollisionShape__
#define __LuaCollisionShape__

#include "Linker.h"

#include <lua.hpp>
#include <luabind\luabind.hpp>
#include <GenericLuaObject.h>
#include <LuaModel.h>
#include <LuaMath.h>

namespace LuaCollisionShape
{
	class ScriptPhysicsDLL_API CollisionShape : public GenericLuaObject
	{
	public:
		CollisionShape();
		CollisionShape(std::string id);
		void Release();

		static void Register(lua_State *lua);
	};

	ScriptPhysicsDLL_API CollisionShape CreateConvexHullShape(LuaModel::Model model);
	ScriptPhysicsDLL_API CollisionShape CreateConvexTriangleShape(LuaModel::Model model);

	ScriptPhysicsDLL_API CollisionShape CreateBoxShape(LuaMath::Vector4 HalfExtent);
	ScriptPhysicsDLL_API CollisionShape CreateCapsuleShape(double radius, double height);
	ScriptPhysicsDLL_API CollisionShape CreateConeShape(double radius, double height);
	ScriptPhysicsDLL_API CollisionShape CreateCylinderShape(LuaMath::Vector4 HalfExtent);
	ScriptPhysicsDLL_API CollisionShape CreateSphereShape(double radius);

	void RegisterAllLuaFunction(lua_State *lua);
}

#endif //__LuaCollisionShape__
