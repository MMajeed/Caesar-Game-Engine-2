#include "LuaRigidBody.h"

#include <PhysicsCommunicator\RigidBodyConfig.h>
#include <Keys.h>
#include <MathFunctions.h>
#include "LuaCollisionShape.h"

namespace LuaRigidBody
{
	RididBody::RididBody(luabind::object const& table)
	{
		CML::Vec4 Location;
		CML::Vec4 Rotation;
		CML::Vec4 Inertia;
		bool calculateInertia = true;
		double mass = 0.0;
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
				else if(key == Keys::RigidBody::INERTIA)		{ Inertia = luabind::object_cast<LuaMath::Vector4>(*it); calculateInertia = false; }
				else if(key == Keys::RigidBody::MASS)			{ mass = luabind::object_cast<double>(*it); }
				else if(key == Keys::RigidBody::COLLISIONSHAPE)	{ collisionShape = luabind::object_cast<LuaCollisionShape::CollisionShape>(*it).ID; }
			}
		}

		this->ID = RigidBodyConfig::Create(collisionShape, Location, Rotation, (float)mass, calculateInertia, Inertia);
	}

	void RididBody::ApplyTorque(LuaMath::Vector4 v)
	{
		RigidBodyConfig::ApplyTorque(this->ID, v.vector);
	}
	void RididBody::ApplyCentralFroce(LuaMath::Vector4 v)
	{
		RigidBodyConfig::ApplyCentralFroce(this->ID, v.vector);
	}
	void RididBody::SetTorque(LuaMath::Vector4 v)
	{
		RigidBodyConfig::SetTorque(this->ID, v.vector);
	}

	LuaMath::Vector4 RididBody::GetTorque()
	{
		return RigidBodyConfig::GetTorque(this->ID);;
	}
	LuaMath::Vector4 RididBody::GetForce()
	{
		return RigidBodyConfig::GetForce(this->ID);;
	}
	LuaMath::Vector4 RididBody::GetQuaRotation()
	{
		return RigidBodyConfig::GetQuaRotation(this->ID);;
	}
	LuaMath::Vector4 RididBody::GetLocation()
	{
		return RigidBodyConfig::GetLocation(this->ID);
	}

	void RididBody::Release()
	{
		RigidBodyConfig::Release(this->ID);
	}

	void RididBody::Register(lua_State *lua)
	{
		luabind::module(lua)[
			luabind::class_<LuaRigidBody::RididBody, GenericLuaObject>("RididBody")
				.def(luabind::constructor<luabind::object const&>())
				.def("ApplyTorque", &RididBody::ApplyTorque)
				.def("ApplyCentralFroce", &RididBody::ApplyCentralFroce)
				.def("GetTorque", &RididBody::GetTorque)
				.def("GetForce", &RididBody::GetForce)
				.def("GetQuaRotation", &RididBody::GetQuaRotation)
				.def("GetLocation", &RididBody::GetLocation)
				.def("SetTorque", &RididBody::SetTorque)
				.def("Release", &RididBody::Release)
		];
	}

	void RegisterAllLuaFunction(lua_State *lua)
	{
		RididBody::Register(lua);
	}
}