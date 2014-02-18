#include "LuaConstraint.h"
#include <PhysicsCommunicator\ConstraintConfig.h>
#include <Keys.h>

namespace LuaConstraint
{
	// ----------------------------------- Start BallSocketBodyToPoint ---------------------------
	BallSocketBodyToPoint::BallSocketBodyToPoint(luabind::object const& table)
	{
		/*std::string RigidBody;
		CML::Vec4 PivotPoint;

		if(luabind::type(table) == LUA_TTABLE)
		{
			for(luabind::iterator it(table);
				it != luabind::iterator();
				++it)
			{
				std::string key = luabind::object_cast<std::string>(it.key());

				if(key == Keys::RigidBody::POSITION)		{ Location = luabind::object_cast<LuaMath::Vector4>(*it); }
				else if(key == Keys::RigidBody::ROTATION)		{ Rotation = luabind::object_cast<LuaMath::Vector4>(*it); }
				else if(key == Keys::RigidBody::INERTIA)		{ Inertia = luabind::object_cast<LuaMath::Vector4>(*it); calculateInertia = false; }
				else if(key == Keys::RigidBody::MASS)			{ mass = luabind::object_cast<double>(*it); }
				else if(key == Keys::RigidBody::COLLISIONSHAPE)	{ collisionShape = luabind::object_cast<LuaCollisionShape::CollisionShape>(*it).ID; }
			}
		}

		this->ID = RigidBodyConfig::Create(collisionShape, Location, Rotation, (float)mass, calculateInertia, Inertia);*/
	}
	void BallSocketBodyToPoint::Release()
	{
		ConstraintConfig::Release(this->ID);
	}
	void BallSocketBodyToPoint::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<LuaConstraint::BallSocketBodyToPoint>("Constraint")
				.def_readonly("ID", &LuaConstraint::BallSocketBodyToPoint::ID)
				.def("Release", &LuaConstraint::BallSocketBodyToPoint::Release)
		];
	}
	// ----------------------------------- End BallSocketBodyToPoint ---------------------------


	void RegisterAllLuaFunction(lua_State *lua)
	{

	}
}
