#include "LuaRigidBody.h"

#include <PhysicsCommunicator\RigidBodyConfig.h>
#include <Keys.h>
#include "LuaCollisionShape.h"

namespace LuaRigidBody
{
	RididBody::RididBody(luabind::object const& table)
	{
		CML::Vec4 Location;
		CML::Vec4 Rotation;
		CML::Vec4 Inertia;
		bool InertiaSet = false;
		double mass;
		std::string collisionShape;

		if(luabind::type(table) == LUA_TTABLE)
		{
			for(luabind::iterator it(table);
				it != luabind::iterator();
				++it)
			{
				std::string key = luabind::object_cast<std::string>(it.key());

					 if(key == Keys::RigidBody::POSITION)		{ Location = luabind::object_cast<LuaMath::Vector4>(*it); }
				else if(key == Keys::RigidBody::ROTATION)		{ Rotation = luabind::object_cast<LuaMath::Vector4>(*it); }
				else if(key == Keys::RigidBody::INERTIA)		{ Inertia = luabind::object_cast<LuaMath::Vector4>(*it); InertiaSet = true; }
				else if(key == Keys::RigidBody::MASS)			{ mass = luabind::object_cast<double>(*it); }
				else if(key == Keys::RigidBody::COLLISIONSHAPE)	{ collisionShape = luabind::object_cast<LuaCollisionShape::CollisionShape>(*it).ID; }
			}
		}

		this->ID = RigidBodyConfig::Create(collisionShape, Location, Rotation, (float)mass, InertiaSet, Inertia);
	}
	void RididBody::Release()
	{
		RigidBodyConfig::Release(this->ID);
	}
	void RididBody::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<LuaRigidBody::RididBody>("RididBody")
				.def(luabind::constructor<luabind::object const&>())
				.def_readonly("ID", &RididBody::ID)
				.def("Release", &RididBody::Release)
		];
	}

	void RegisterAllLuaFunction(lua_State *lua)
	{
		RididBody::Register(lua);
	}
}