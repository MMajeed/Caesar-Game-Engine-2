#include "LuaCollisionShape.h"

#include <PhysicsCommunicator\CollisionShapeConfig.h>

namespace LuaCollisionShape
{
	// -----------------------Start CollisionShape-------------------
	CollisionShape::CollisionShape()
	{

	}
	CollisionShape::CollisionShape(std::string id)
	{
		this->ID = id;
	}
	void CollisionShape::Release()
	{
		CollisionShapeConfig::Release(this->ID);
	}
	void CollisionShape::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<LuaCollisionShape::CollisionShape>("CollisionShape")
				.def(luabind::constructor<>())
				.def_readonly("ID", &CollisionShape::ID)
				.def("Release", &CollisionShape::Release)
		];
	}
	// -----------------------End CollisionShape-------------------

	CollisionShape CreateConvexHullShape(LuaModel::Model model)
	{
		std::string id = CollisionShapeConfig::CreateConvexHullShape(model);
		return CollisionShape(id);
	}
	CollisionShape CreateConvexTriangleShape(LuaModel::Model model)
	{
		std::string id = CollisionShapeConfig::CreateConvexTriangleMesh(model);
		return CollisionShape(id);
	}

	CollisionShape CreateBoxShape(LuaMath::Vector4 HalfExtent)
	{
		std::string id = CollisionShapeConfig::CreateBoxShape(HalfExtent.vector);
		return CollisionShape(id);
	}
	CollisionShape CreateCapsuleShape(double radius, double height)
	{
		std::string id = CollisionShapeConfig::CreateCapsuleShape(radius, height);
		return CollisionShape(id);
	}
	CollisionShape CreateConeShape(double radius, double height)
	{
		std::string id = CollisionShapeConfig::CreateConeShape(radius, height);
		return CollisionShape(id);
	}
	CollisionShape CreateCylinderShape(LuaMath::Vector4 HalfExtent)
	{
		std::string id = CollisionShapeConfig::CreateCylinderShape(HalfExtent.vector);
		return CollisionShape(id);
	}
	CollisionShape CreateSphereShape(double radius)
	{
		std::string id = CollisionShapeConfig::CreateSphereShape(radius);
		return CollisionShape(id);
	}

	void RegisterAllLuaFunction(lua_State *lua)
	{
		CollisionShape::Register(lua);

		luabind::module(lua)[
			luabind::def("CreateConvexHullShape", LuaCollisionShape::CreateConvexHullShape),
			luabind::def("CreateConvexTriangleShape", LuaCollisionShape::CreateConvexTriangleShape),
			luabind::def("CreateBoxShape", LuaCollisionShape::CreateBoxShape),
			luabind::def("CreateCapsuleShape", LuaCollisionShape::CreateCapsuleShape),
			luabind::def("CreateConeShape", LuaCollisionShape::CreateConeShape),
			luabind::def("CreateCylinderShape", LuaCollisionShape::CreateCylinderShape),
			luabind::def("CreateSphereShape", LuaCollisionShape::CreateSphereShape)
		];
	}
}