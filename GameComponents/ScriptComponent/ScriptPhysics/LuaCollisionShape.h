#ifndef __LuaCollisionShape__
#define __LuaCollisionShape__

#include <lua.hpp>
#include <luabind\luabind.hpp>
#include <string>
#include <ScriptCommon\LuaModel.h>
#include <ScriptCommon\LuaMath.h>

namespace LuaCollisionShape
{
	class CollisionShape
	{
	public:
		CollisionShape();
		CollisionShape(std::string id);
		void Release();
		std::string ID;

		static void Register(lua_State *lua);
	};

	CollisionShape CreateConvexHullShape(LuaModel::Model model);
	CollisionShape CreateConvexTriangleShape(LuaModel::Model model);

	CollisionShape CreateBoxShape(LuaMath::Vector4 HalfExtent);
	CollisionShape CreateCapsuleShape(double radius, double height);
	CollisionShape CreateConeShape(double radius, double height);
	CollisionShape CreateCylinderShape(LuaMath::Vector4 HalfExtent);
	CollisionShape CreateSphereShape(double radius);

	void RegisterAllLuaFunction(lua_State *lua);
}

#endif //__LuaCollisionShape__
